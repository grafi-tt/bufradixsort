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

/* COPYMASKBUF */
#define COPYMASKBUF CAT(COPYMASKBUF_EXT_, EXT_STREAM)
#define COPYMASKBUF_EXT_NONE() do { \
	unsigned int i; \
	for (i = 0; i < BUFFER_SIZE; i++) \
		ASSUME_ALIGNED(copy_point_rst, BUFFER_SIZE)[i] = \
			ASSUME_ALIGNED(buf_point_rst, BUFFER_SIZE)[i] ^ ASSUME_ALIGNED(float_mask_rst, BUFFER_SIZE)[i]; \
} while (0)
#define COPYMASKBUF_EXT_SSE2() do { \
	unsigned int i; \
	for (i = 0; i < BUFFER_SIZE/16; i++) \
		_mm_stream_si128((__m128i*)copy_point_rst+i, \
				_mm_xor_si128(_mm_load_si128((__m128i*)buf_point_rst+i), _mm_load_si128((__m128i*)float_mask_rst+i))); \
} while(0)

#if defined(__GNUC__)
#pragma GCC optimize("tree-vectorize")
#pragma GCC optimize("unroll-loops")
#endif
static int relocate_float_buf_full(unsigned int first_buf_bkt, unsigned char *restrict buf_point_rst, unsigned int bkt,
		unsigned char *restrict *restrict copy_points_rst, unsigned int invalid_elems_offset,
		const unsigned char *restrict float_mask_rst) {
	unsigned char *copy_point_rst = copy_points_rst[bkt];
	copy_points_rst[bkt] = copy_point_rst + BUFFER_SIZE;
	if (UNLIKELY(bkt == first_buf_bkt)) {
		unsigned int i;
		for (i = invalid_elems_offset; i < BUFFER_SIZE; i++)
			copy_point_rst[i] = buf_point_rst[i] ^ float_mask_rst[i];
		return BKT;
	} else {
		COPYMASKBUF();
		return first_buf_bkt;
	}
}

#define RELOCATE_FLOAT_KERNEL(ELEM_SIZE) do { \
	unsigned int bkt = *data_cur; \
	data_cur += ELEM_SIZE; \
	SIZEUTYP(ELEM_SIZE) val; \
	memcpy(&val, data_rst, sizeof(val)); \
	data_rst += ELEM_SIZE; \
	unsigned char *buf_point_rst = buf_points_rst[bkt]; \
	memcpy(buf_point_rst, &val, sizeof(val)); \
	buf_point_rst += ELEM_SIZE; \
	if (((uintptr_t)buf_point_rst & (BUFFER_SIZE-1)) == 0) { \
		buf_point_rst -= BUFFER_SIZE; \
		if (bkt < BKT>>1) \
			first_buf_bkt = relocate_buf_full(first_buf_bkt, buf_point_rst, bkt, \
					copy_points_rst, invalid_elems_offset); \
		else \
			first_buf_bkt = relocate_float_buf_full(first_buf_bkt, buf_point_rst, bkt, \
					copy_points_rst, invalid_elems_offset, float_mask_rst); \
	} \
	buf_points_rst[bkt] = buf_point_rst; \
} while (0)

#define RELOCATE_FLOAT_IF_F_DO(ELEM_SIZE) do { \
	const unsigned char *data_cur = data_rst + bkt_pos_base + real_pos; \
	while (data_rst < data_algn) { \
		RELOCATE_FLOAT_KERNEL(ELEM_SIZE); \
	} \
	while (data_rst < data_end) { \
		PREFETCH(data_rst+128, 0, 0); \
		ITERARG(UNROLL_RELOCATE, RELOCATE_FLOAT_KERNEL, ELEM_SIZE); \
	} \
} while (0)

#define RELOCATE_FLOAT_IF_F(ELEM_SIZE) \
	IF0(SUB(DIV(INDEX(0, SUPPORTED_FLOAT_BITS_LIST_LEN, SUPPORTED_FLOAT_BITS_LIST), BKT_BIT), ELEM_SIZE), \
			RELOCATE_FLOAT_IF_F_DO(ELEM_SIZE), ;)

/*
 * Otherwise, simply relocate.
 */
#define COPYBUF CAT(COPYBUF_EXT_, EXT_STREAM)
#define COPYBUF_EXT_NONE() \
	memcpy(ASSUME_ALIGNED(copy_point_rst, BUFFER_SIZE), ASSUME_ALIGNED(buf_point_rst, BUFFER_SIZE), BUFFER_SIZE)
#define COPYBUF_EXT_SSE2() \
	ITERNUM(DIV(BUFFER_SIZE, 16), COPYBUF_EXT_SSE2_KERNEL)
#define COPYBUF_EXT_SSE2_KERNEL(n) \
	_mm_stream_si128((__m128i*)copy_point_rst+n, _mm_load_si128((__m128i*)buf_point_rst+n))

#if defined(__GNUC__)
#pragma GCC optimize("tree-vectorize")
#pragma GCC optimize("unroll-loops")
#endif
static int relocate_buf_full(unsigned int first_buf_bkt, unsigned char *restrict buf_point_rst, unsigned int bkt,
		unsigned char *restrict *restrict copy_points_rst, unsigned int invalid_elems_offset) {
	unsigned char *copy_point_rst = copy_points_rst[bkt];
	copy_points_rst[bkt] = copy_point_rst + BUFFER_SIZE;
	if (UNLIKELY(bkt == first_buf_bkt)) {
		unsigned int i;
		for (i = invalid_elems_offset; i < BUFFER_SIZE; i++)
			copy_point_rst[i] = buf_point_rst[i];
		return BKT;
	} else {
		COPYBUF();
		return first_buf_bkt;
	}
}

#define RELOCATE_NONFLOAT_KERNEL(ELEM_SIZE) do { \
	unsigned int bkt = *data_cur; \
	data_cur += ELEM_SIZE; \
	SIZEUTYP(ELEM_SIZE) val; \
	memcpy(&val, (SIZEUTYP(ELEM_SIZE)*)data_rst, sizeof(val)); \
	data_rst += ELEM_SIZE; \
	unsigned char *restrict buf_point_rst = buf_points_rst[bkt]; \
	memcpy((SIZEUTYP(ELEM_SIZE)*)buf_point_rst, &val, sizeof(val)); \
	buf_point_rst += ELEM_SIZE; \
	if (((uintptr_t)buf_point_rst & (BUFFER_SIZE-1)) == 0) { \
		buf_point_rst -= BUFFER_SIZE; \
		first_buf_bkt = relocate_buf_full(first_buf_bkt, buf_point_rst, bkt, copy_points_rst, invalid_elems_offset); \
	} \
	buf_points_rst[bkt] = buf_point_rst; \
} while(0)

#define RELOCATE_NONFLOAT_IF_F(ELEM_SIZE) do { \
	const unsigned char *data_cur = data_rst + bkt_pos_base + real_pos; \
	while (data_rst < data_algn) { \
		RELOCATE_NONFLOAT_KERNEL(ELEM_SIZE); \
	} \
	while (data_rst < data_end) { \
		PREFETCH(data_rst+128, 0, 0); \
		ITERARG(UNROLL_RELOCATE, RELOCATE_NONFLOAT_KERNEL, ELEM_SIZE); \
	} \
} while (0)

/*
 * Generic part.
 */
#define RELOCATE_CASE_E(ELEM_SIZE_LOG) case ELEM_SIZE_LOG: { \
	if (float_bits_if_msb) { \
		RELOCATE_FLOAT_IF_F(POW(2, ELEM_SIZE_LOG)); \
	} else { \
		RELOCATE_NONFLOAT_IF_F(POW(2, ELEM_SIZE_LOG)); \
	} \
} break

static void relocate_data(const unsigned char *data, const unsigned char *data_end, unsigned char *dest,
		unsigned int elem_size_log, unsigned int bkt_pos_base, unsigned int real_pos, unsigned int float_bits_if_msb,
		unsigned int bkt_fix_sign, const size_t *histo, unsigned char **copy_points) {
#ifdef ALIGNED
	unsigned char ALIGNED(BUFFER_SIZE) buf[BKT][BUFFER_SIZE];
	unsigned char ALIGNED(BUFFER_SIZE) float_mask[BUFFER_SIZE];
#else
	unsigned char buf_space[BKT*(BUFFER_SIZE+2)];
	unsigned char (*buf)[BUFFER_SIZE] =
		(unsigned char(*)[BUFFER_SIZE])(buf_space + (-(uintptr_t)buf_space & (BUFFER_SIZE-1)));
	unsigned char (*float_mask)[BUFFER_SIZE] = buf+BKT;
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
	 * Set up float mask.
	 */
	memset(float_mask, 0, BUFFER_SIZE);
	if (float_bits_if_msb) {
		unsigned int i, j;
		for (i = 0; i < BUFFER_SIZE; i += 1 << elem_size_log)
			for (j = 0; j < float_bits_if_msb/BKT_BIT-1; j++)
				if (j != real_pos)
					float_mask[i + bkt_pos_base + j] = BKT-1;
	}

	/*
	 * Run kernel.
	 */
	{
		const unsigned char *restrict data_rst = data;
		unsigned char *restrict *restrict buf_points_rst = buf_points;
		unsigned char *restrict *restrict copy_points_rst = copy_points;
		const unsigned char *data_algn = data +
			((((data_end - data) >> elem_size_log) % UNROLL_RELOCATE) << elem_size_log);
		const unsigned char *restrict float_mask_rst = float_mask;
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
