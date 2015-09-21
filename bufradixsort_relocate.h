#ifndef BUFRADIXSORT_RELOCATE_H
#define BUFRADIXSORT_RELOCATE_H

#define TYPE uint32_t
#define TYPE_SIZE_LOG 2
#define TYPE_SIZE 4

#include <stdint.h>
#include <string.h>
#if EXT_UNIQID(SSE2) == EXT_UNIQID(EXT_STREAM)
#include <emmintrin.h>
#include <smmintrin.h>
#endif
#include "bufradixsort_config.h"
#include "bufradixsort_unroll.h"

#define COPYBUF              COPYBUF_HELPER1(EXT_STREAM)
#define COPYBUF_HELPER1(ext) COPYBUF_HELPER2(ext)
#define COPYBUF_HELPER2(ext) COPYBUF_EXT_##ext

#define COPYBUF_EXT_NONE() \
	memcpy(ASSUME_ALIGNED(copy_point, BUFFER_SIZE), ASSUME_ALIGNED(buf_point, BUFFER_SIZE), BUFFER_SIZE)

#define COPYBUF_EXT_SSE2() \
	ITERNUM(DIV(16, BUFFER_SIZE), COPYBUF_EXT_SSE2_KERNEL)
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
		EVAL(COPYBUF());
		return first_buf_bkt;
	}
}

#define RELOCATE_KERNEL() do { \
	unsigned int bkt = *data_cur; \
	data_cur += 1 << TYPE_SIZE_LOG; \
	TYPE val = *(TYPE*)data; \
	data += 1 << TYPE_SIZE_LOG; \
	unsigned char *buf_point = buf_points[bkt]; \
	*(TYPE*)buf_point = val; \
	buf_point += 1 << TYPE_SIZE_LOG; \
	if (((uintptr_t)buf_point & (BUFFER_SIZE-1)) == 0) { \
		buf_point -= BUFFER_SIZE; \
		first_buf_bkt = relocate_buf_full(first_buf_bkt, buf_point, bkt, copy_points, invalid_elems_offset); \
	} \
	buf_points[bkt] = buf_point; \
} while(0)

static inline void relocate_data(const unsigned char *data, const unsigned char *data_end, unsigned char *dest,
		int bkt_pos, const size_t *histo, unsigned char **copy_points) {
	unsigned char ALIGNED(BUFFER_SIZE) buf[BKT][BUFFER_SIZE];
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
				unsigned char *strt_point = copy_points[bkt];
				unsigned char *ends_point = strt_point + (histo[bkt] << TYPE_SIZE_LOG);
				if (ends_point >= dest_algn_up) {
					if (strt_point < dest_algn_up) {
						first_buf_bkt = bkt;
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
		size_t len = (data_end - data) >> TYPE_SIZE_LOG;
		const unsigned char *data_end_algn = data_end - (len % UNROLL_RELOCATE << TYPE_SIZE_LOG);
		const unsigned char *data_cur = data + bkt_pos;
		while (data < data_end_algn) {
			PREFETCH(data+128, 0, 0);
			EVAL(ITER(UNROLL_RELOCATE, RELOCATE_KERNEL));
		}
		while (data < data_end) EVAL(RELOCATE_KERNEL());
	}

#pragma omp barrier
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
