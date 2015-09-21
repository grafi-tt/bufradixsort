#ifndef BUFRADIXSORT_RELOCATE_CASEWND_H
#define BUFRADIXSORT_RELOCATE_CASEWND_H

#include <stdlib.h>
#if BUFRADIXSORT_USE_SIMD_RELOCATE
#include <emmintrin.h>
#include <smmintrin.h>
#endif
#if EXT_UNIQID(SSE2) == EXT_UNIQID(EXT_STREAM)
#include <emmintrin.h>
#include <smmintrin.h>
#endif
#include "bufradixsort_config.h"
#include "bufradixsort_unroll.h"

#define COPYBUF              COPYBUF_HELPER1(EXT_STREAM)
#define COPYBUF_HELPER1(ext) COPYBUF_HELPER2(ext)
#define COPYBUF_HELPER2(ext) COPYBUF_EXT_##ext

#define COPYBUF_EXT_NONE(copy_point, buf_point) \
	memcpy(copy_point, buf_point, BUFFER_SIZE)

#define COPYBUF_EXT_SSE2(copy_point, buf_point) \
	ITERNUMARG(DIV(16, BUFFER_SIZE), COPYBUF_EXT_SSE2_KERNEL, (copy_point, buf_point))
#define COPYBUF_EXT_SSE2_KERNEL(n, args) COPYBUF_EXT_SSE2_KERNEL_HELPER1(n, COPYBUF_EXT_SSE2_KERNEL_SPLIT args)
#define COPYBUF_EXT_SSE2_KERNEL_SPLIT(a, b) a, b
#define COPYBUF_EXT_SSE2_KERNEL_HELPER1(n, argsx) COPYBUF_EXT_SSE2_KERNEL_HELPER2(n, argsx)
#define COPYBUF_EXT_SSE2_KERNEL_HELPER2(n, copy_point, buf_point) \
	_mm_stream_si128((__m128i*)copy_point+n, _mm_load_si128((__m128i*)buf_point+n)) \

#define RELOCATE_IF_BUF_FULL() do { \
	if (((uintptr_t)buf_point & (BUFFER_SIZE-1)) == 0) { \
		buf_point -= BUF; \
		TYPE *copy_point = copy_points[bkt]; \
		copy_points[bkt] = copy_point+BUF; \
		if (UNLIKELY(bkt == first_buf_bkt)) { \
			trick_head(copy_point, buf_point, invalid_elems_cnt); \
			first_buf_bkt = BKT; \
		} else { \
			COPYBUF(copy_point, buf_point); \
		} \
	} \
} while(0)

#define RELOCATE_NOSIMD_KERNEL() do { \
	TYPE val = *data++; \
	unsigned int bkt = val >> WND * BKT_BIT & (BKT-1); \
	TYPE *buf_point = buf_points[bkt]; \
	*buf_point = val; \
	buf_point += 1; \
	RELOCATE_IF_BUF_FULL(); \
	buf_points[bkt] = buf_point; \
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
	RELOCATE_IF_BUF_FULL(); \
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
		const TYPE *data_end_algn = (data_end-4)-(len-4)%UNROLL_RELOCATE; \
		while (data < data_algn) EVAL(RELOCATE_NOSIMD_KERNEL()); \
		__m128i xmm_mask = _mm_set1_epi32(BKT-1); \
		__m128i xmmb = _mm_load_si128((__m128i*)data); \
		__m128i xmmv = xmmb; \
		if (WND != 0) xmmb = _mm_bsrli_si128(xmmb, WND); \
		xmmb = _mm_and_si128(xmmb, xmm_mask); \
		while (data < data_end_algn) { \
			PREFETCH(data+32, 0, 0); \
			EVAL(ITER(DIV(4, UNROLL_RELOCATE), RELOCATE_SIMD_KERNEL)); \
		} \
	} \
	while (data < data_end) EVAL(RELOCATE_NOSIMD_KERNEL()); \
}

#define RELOCATE_NOSIMD_RUN_KERNEL { \
	size_t len = data_end-data; \
	const TYPE *data_end_algn = data_end-len%UNROLL_RELOCATE; \
	while (data < data_end_algn) { \
		PREFETCH(data+32, 0, 0); \
		EVAL(ITER(UNROLL_RELOCATE, RELOCATE_NOSIMD_KERNEL)); \
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
