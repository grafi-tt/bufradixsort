#ifndef BUFRADIXSORT_RELOCATE_H
#define BUFRADIXSORT_RELOCATE_H

#include "bufradixsort_common.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#if EXT_UNIQID(SSE2) == EXT_UNIQID(EXT_STREAM)
#include <emmintrin.h>
#include <smmintrin.h>
#endif

/*
 * If it is MSB of a float, negate non-sign buckets if the sign is minus.
 */
#define RELOCATE_FLOAT_KERNEL(ELEM_SIZE_LOG) do { \
	unsigned int bkt = *data_cur; \
	data_cur += 1 << ELEM_SIZE_LOG; \
	LOGUTYP(ELEM_SIZE_LOG) val = *(LOGUTYP(ELEM_SIZE_LOG)*)data; \
	data += 1 << ELEM_SIZE_LOG; \
	unsigned char *buf_point = buf_points[bkt]; \
	*(LOGUTYP(ELEM_SIZE_LOG)*)buf_point = val; \
	buf_point += 1 << ELEM_SIZE_LOG; \
	if (((uintptr_t)buf_point & (BUFFER_SIZE-1)) == 0) { \
		buf_point -= BUFFER_SIZE; \
		first_buf_bkt = relocate_buf_full(first_buf_bkt, buf_point, bkt, copy_points, invalid_elems_offset); \
	} \
	buf_points[bkt] = buf_point; \
} while(0)

#define RELOCATE_FLOAT_CASE_F_DO(FLOAT_BITS, ELEM_SIZE_LOG) case FLOAT_BITS: { \
	const unsigned char *restrict data_cur = data + bkt_pos_base + real_pos; \
	LOGUTYP(ELEM_SIZE_LOG) float_fix = \
		(((LOGUTYP(ELEM_SIZE_LOG))1 << (FLOAT_BITS-1))-1) << (((1 << ELEM_SIZE_LOG) - bkt_pos_base) * BKT_BIT); \
	LOGUTYP(ELEM_SIZE_LOG_MAX) float_fixes = float_fix; \
	int i; \
	for (i = ELEM_SIZE_LOG; i < ELEM_SIZE_LOG_MAX; i++) \
		float_fixes |= float_fixes << ((1 << i) * BKT_BIT); \
	while (data < data_algn) { \
		RELOCATE_FLOAT_KERNEL(ELEM_SIZE_LOG); \
	} \
	while (data < data_end) { \
		PREFETCH(data+128, 0, 0); \
		ITERARG(UNROLL_RELOCATE, RELOCATE_FLOAT_KERNEL, ELEM_SIZE_LOG); \
	} \
} break

#define RELOCATE_FLOAT_CASE_F_EMP(FLOAT_BITS) case FLOAT_BITS:

#define RELOCATE_FLOAT_CASE_F(FLOAT_BITS, ELEM_SIZE_LOG) \
	IF0(SUB(DIV(FLOAT_BITS, BKT_BIT), POW(2, ELEM_SIZE_LOG)), \
		RELOCATE_FLOAT_CASE_F_DO(FLOAT_BITS, ELEM_SIZE_LOG), RELOCATE_FLOAT_CASE_F_EMP(FLOAT_BITS))

/*
 * Otherwise, simply relocate.
 */
#define COPYBUF              COPYBUF_HELPER1(EXT_STREAM)
#define COPYBUF_HELPER1(ext) COPYBUF_HELPER2(ext)
#define COPYBUF_HELPER2(ext) COPYBUF_EXT_##ext

#define COPYBUF_EXT_NONE() \
	memcpy(ASSUME_ALIGNED(copy_point, BUFFER_SIZE), ASSUME_ALIGNED(buf_point, BUFFER_SIZE), BUFFER_SIZE)

#define COPYBUF_EXT_SSE2() \
	ITERNUM(DIV(BUFFER_SIZE, 16), COPYBUF_EXT_SSE2_KERNEL)
#define COPYBUF_EXT_SSE2_KERNEL(n) \
	_mm_stream_si128((__m128i*)copy_point+n, _mm_load_si128((__m128i*)buf_point+n))

static NOINLINE int relocate_buf_full(unsigned int first_buf_bkt, unsigned char *buf_point, unsigned int bkt,
		unsigned char **copy_points, unsigned int invalid_elems_offset) {
	unsigned char *copy_point = copy_points[bkt];
	copy_points[bkt] = copy_point + BUFFER_SIZE;
	if (UNLIKELY(bkt == first_buf_bkt)) {
		unsigned char *copy_end_point = copy_point + BUFFER_SIZE;
		buf_point += invalid_elems_offset;
		copy_point += invalid_elems_offset;
		while (copy_point < copy_end_point)
			*copy_point++ = *buf_point++;
		return BKT;
	} else {
		COPYBUF();
		return first_buf_bkt;
	}
}

#define RELOCATE_NONFLOAT_KERNEL(ELEM_SIZE_LOG) do { \
	unsigned int bkt = *data_cur; \
	data_cur += 1 << ELEM_SIZE_LOG; \
	LOGUTYP(ELEM_SIZE_LOG) val = *(LOGUTYP(ELEM_SIZE_LOG)*)data; \
	data += 1 << ELEM_SIZE_LOG; \
	unsigned char *buf_point = buf_points[bkt]; \
	*(LOGUTYP(ELEM_SIZE_LOG)*)buf_point = val; \
	buf_point += 1 << ELEM_SIZE_LOG; \
	if (((uintptr_t)buf_point & (BUFFER_SIZE-1)) == 0) { \
		buf_point -= BUFFER_SIZE; \
		first_buf_bkt = relocate_buf_full(first_buf_bkt, buf_point, bkt, copy_points, invalid_elems_offset); \
	} \
	buf_points[bkt] = buf_point; \
} while(0)

#define RELOCATE_NONFLOAT_CASE_F(ELEM_SIZE_LOG) default: { \
	const unsigned char *restrict data_cur = data + bkt_pos_base + real_pos; \
	while (data < data_algn) { \
		RELOCATE_NONFLOAT_KERNEL(ELEM_SIZE_LOG); \
	} \
	while (data < data_end) { \
		PREFETCH(data+128, 0, 0); \
		ITERARG(UNROLL_RELOCATE, RELOCATE_NONFLOAT_KERNEL, ELEM_SIZE_LOG); \
	} \
} break

/*
 * Generic part.
 */
#define RELOCATE_CASE_E(ELEM_SIZE_LOG) case ELEM_SIZE_LOG: { \
	switch (float_bits_if_msb) { \
		ITERLISTARG(SUPPORTED_FLOAT_BITS_LIST_LEN, SUPPORTED_FLOAT_BITS_LIST, RELOCATE_FLOAT_CASE_F, ELEM_SIZE_LOG); \
		RELOCATE_NONFLOAT_CASE_F(ELEM_SIZE_LOG); \
	} \
}

static void relocate_data(const unsigned char *data, const unsigned char *data_end, unsigned char *dest,
		unsigned int elem_size_log, unsigned int bkt_pos_base, unsigned int real_pos, unsigned int float_bits_if_msb,
		unsigned int bkt_fix_sign, const size_t *histo, unsigned char **copy_points) {
#ifdef ALIGNED
	unsigned char ALIGNED(BUFFER_SIZE) buf[BKT][BUFFER_SIZE];
#else
	unsigned char buf_space[BKT*(BUFFER_SIZE+1)];
	unsigned char (*buf)[BUFFER_SIZE] =
		(unsigned char(*)[BUFFER_SIZE])(buf_space + (-(uintptr_t)buf_space & (BUFFER_SIZE-1)));
#endif
	unsigned char *buf_points[BKT];
	unsigned int first_buf_bkt = BKT;
	unsigned int invalid_elems_offset = 0;
	unsigned int bkt;

	/*
	 * If current thread is sorting to the first area of destination,
	 * even temporalily writing to the preceeding position should be considered as dangerous,
	 * since they could be used by other parts of the program or be protected by segment.
	 * So we must detect writing to the first position.
	 */
	{
		unsigned char *dest_algn = (void*)((uintptr_t)dest & -BUFFER_SIZE);
		if (dest != dest_algn) {
			unsigned char *dest_algn_up = dest_algn + BUFFER_SIZE;
			for (bkt = 0; bkt < BKT; bkt++) {
				unsigned char *strt_point = copy_points[bkt^bkt_fix_sign];
				unsigned char *ends_point = strt_point + histo[bkt^bkt_fix_sign];
				if (ends_point >= dest_algn_up) {
					if (strt_point < dest_algn_up) {
						first_buf_bkt = bkt^bkt_fix_sign;
						invalid_elems_offset = strt_point - dest_algn;
					}
					break;
				}
			}
		}
	}

	/*
	 * Set up buf_points and copy_points (aligned), that is displays of the buffers and the dest resp.
	 * Copypoints are aligned by the number of elements of a buffer.
	 */
	for (bkt = 0; bkt < BKT; bkt++) {
		unsigned char *copy_point = copy_points[bkt];
		unsigned char *copy_point_algn = (void*)((uintptr_t)copy_point & -BUFFER_SIZE);
		int buf_offset = copy_point - copy_point_algn;
		copy_points[bkt] = copy_point - buf_offset;
		buf_points[bkt] = buf[bkt] + buf_offset;
	}

	/*
	 * Buffers must be 0-initialized in order to mitigate with extra histogram counts by fixing 0-bkt.
	 */
	memset(buf, 0, BKT*BUFFER_SIZE);

	/*
	 * Run kernel.
	 */
	{
		const unsigned char *data_algn = data +
			((((data_end - data) >> elem_size_log) % UNROLL_RELOCATE) << elem_size_log);
		switch (elem_size_log) {
			ITERNUM(SUCC(ELEM_SIZE_LOG_MAX), RELOCATE_CASE_E);
		}
	}

#ifdef _OPENMP
#pragma omp barrier
#endif
	for (bkt = 0; bkt < BKT; bkt++) {
		unsigned char *ends_point = copy_points[bkt] + (buf_points[bkt] - buf[bkt]);
		unsigned char *strt_point = ends_point - histo[bkt];
		unsigned char *ends_point_algn = (void*)((uintptr_t)ends_point & -BUFFER_SIZE);
		unsigned char *strt_point_algn = (void*)((uintptr_t)strt_point & -BUFFER_SIZE);
		unsigned char *copy_point;
		unsigned char *buf_point;

		if (strt_point_algn == ends_point_algn) {
			copy_point = strt_point;
			buf_point = buf[bkt] + (strt_point - strt_point_algn);
		} else {
			copy_point = ends_point_algn;
			buf_point = buf[bkt];
		}
		while (copy_point < ends_point)
			*copy_point++ = *buf_point++;
	}
}

#endif /* BUFRADIXSORT_RELOCATE_H */
