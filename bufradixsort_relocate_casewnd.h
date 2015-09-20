#ifndef BUFRADIXSORT_RELOCATE_CASEWND_H
#define BUFRADIXSORT_RELOCATE_CASEWND_H

#include "bufradixsort_config.h"
#include "bufradixsort_unroll.h"

#if BUFRADIXSORT_USE_SIMD_RELOCATE
#include <emmintrin.h>
#include <smmintrin.h>
#endif

#define NEXTHISTO_COPYBUF_NOSIMD_KERNEL() do { \
	TYPE cp = *buf_point_tmp++; \
	*copy_point++ = cp; \
} while(0)

#define RELOCATE_NOSIMD_KERNEL() do { \
	TYPE val = *data++; \
	unsigned int bkt = val >> WND * BKT_BIT & (BKT-1); \
	TYPE *buf_point = buf_points[bkt]; \
	*buf_point = val; \
	buf_point += 1; \
	if (((uintptr_t)buf_point & sizeof(TYPE)*(BUF-1)) == 0) { \
		buf_point -= BUF; \
		TYPE *buf_point_tmp = buf_point; \
		TYPE *copy_point = copy_points[bkt]; \
		copy_points[bkt] = copy_point+BUF; \
		ITER(BUF, NEXTHISTO_COPYBUF_NOSIMD_KERNEL); \
	} \
	buf_points[bkt] = buf_point; \
} while(0)

#define NEXTHISTO_COPYBUF_SIMD_KERNEL() do { \
	__m128i xmmcp = _mm_load_si128((__m128i*)buf_point_tmp); \
	_mm_stream_si128((__m128i*)copy_point, xmmcp); \
	buf_point_tmp += 4; \
	copy_point += 4; \
} while(0)

#define RELOCATE_SIMD_INNER_KERNEL(islast) do { \
	__asm__ __volatile__(" " : "+x" (xmm_mask)); \
	bkt = _mm_cvtsi128_si32(xmmb); \
	if (!islast) { \
		xmmb = _mm_bsrli_si128(xmmb, 4); \
	} else { \
		xmmb = _mm_load_si128((__m128i*)data); \
	} \
	TYPE *buf_point = buf_points[bkt]; \
	*buf_point = _mm_cvtsi128_si32(xmmv); \
	buf_point += 1; \
	if (!islast) { \
		xmmv = _mm_bsrli_si128(xmmv, 4); \
	} else { \
		xmmv = xmmb; \
		if (WND != 0) xmmb = _mm_bsrli_si128(xmmb, WND); \
		xmmb = _mm_and_si128(xmmb, xmm_mask); \
	} \
	if (((uintptr_t)buf_point & sizeof(TYPE)*(BUF-1)) == 0) { \
		buf_point -= BUF; \
		TYPE *buf_point_tmp = buf_point; \
		TYPE *copy_point = copy_points[bkt]; \
		copy_points[bkt] = copy_point+BUF; \
		ITER(DIV(4, BUF), NEXTHISTO_COPYBUF_SIMD_KERNEL); \
	} \
	buf_points[bkt] = buf_point; \
} while(0)

#define RELOCATE_SIMD_KERNEL() do { \
	unsigned int bkt; \
	data += 4; \
	RELOCATE_SIMD_INNER_KERNEL(0); \
	RELOCATE_SIMD_INNER_KERNEL(0); \
	RELOCATE_SIMD_INNER_KERNEL(0); \
	RELOCATE_SIMD_INNER_KERNEL(1); \
} while(0)

#define RELOCATE_SIMD_RUN_KERNEL { \
	size_t len = data_end-data; \
	size_t algn = 4-(uintptr_t)data/sizeof(TYPE)%4; \
	if (algn == 4) algn = 0; \
	if ((len -= algn) > 4) { \
		const TYPE *data_algn = data+algn; \
		const TYPE *data_end_algn = (data_end-4)-(len-4)%BUFRADIXSORT_UNROLL_COUNT_RELOCATE; \
		while (data < data_algn) EVAL(RELOCATE_NOSIMD_KERNEL()); \
		__m128i xmm_mask = _mm_set1_epi32(BKT-1); \
		__m128i xmmb = _mm_load_si128((__m128i*)data); \
		__m128i xmmv = xmmb; \
		if (WND != 0) xmmb = _mm_bsrli_si128(xmmb, WND); \
		xmmb = _mm_and_si128(xmmb, xmm_mask); \
		while (data < data_end_algn) { \
			PREFETCH(data+32, 0, 0); \
			EVAL(ITER(DIV(4, BUFRADIXSORT_UNROLL_COUNT_RELOCATE), RELOCATE_SIMD_KERNEL)); \
		} \
	} \
	while (data < data_end) EVAL(RELOCATE_NOSIMD_KERNEL()); \
}

#define RELOCATE_NOSIMD_RUN_KERNEL { \
	size_t len = data_end-data; \
	const TYPE *data_end_algn = data_end-len%BUFRADIXSORT_UNROLL_COUNT_RELOCATE; \
	while (data < data_end_algn) { \
		PREFETCH(data+32, 0, 0); \
		EVAL(ITER(BUFRADIXSORT_UNROLL_COUNT_RELOCATE, RELOCATE_NOSIMD_KERNEL)); \
	} \
	while (data < data_end) EVAL(RELOCATE_NOSIMD_KERNEL()); \
}

#if BUFRADIXSORT_USE_SIMD_RELOCATE
#define RELOCATE_RUN_KERNEL RELOCATE_SIMD_RUN_KERNEL
#else
#define RELOCATE_RUN_KERNEL RELOCATE_NOSIMD_RUN_KERNEL
#endif

#define RELOCATE_CASEWND case WND: RELOCATE_RUN_KERNEL break;

#endif /* BUFRADIXSORT_RELOCATE_CASEWND_H */
