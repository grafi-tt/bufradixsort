#ifndef BUFRADIXSORT_CONFIG_H
#define BUFRADIXSORT_CONFIG_H

/* extensions */
#if defined(__INTEL_COMPILER)

#define ALIGNED(multiple) __attribute__((aligned(multiple)))
#define ASSUME_ALIGNED(ptr, multiple) __assume_aligned(ptr, multiple)
#define NOINLINE __attribute__((noinline))
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define PREFETCH(ptr, rw, loc) __builtin_prefetch(ptr, rw, loc)

#elif defined(__GNUC__)

#define ALIGNED(multiple) __attribute__((aligned(multiple)))
#define ASSUME_ALIGNED(ptr, multiple) __builtin_assume_aligned(ptr, multiple)
#define NOINLINE __attribute__((noinline))
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define PREFETCH(ptr, rw, loc) __builtin_prefetch(ptr, rw, loc)

#else

#define ASSUME_ALIGNED(ptr, multiple) (ptr)
#define NOINLINE
#define LIKELY(x) x
#define UNLIKELY(x) x
#define PREFETCH(ptr, rw, loc)

#endif

#define EXT_UNIQID_NONE __LINE__
#define EXT_UNIQID_SSE2 __LINE__
#define EXT_UNIQID_ALTIVEC __LINE__
#define EXT_UNIQID_NEON __LINE__
#define EXT_UNIQID(ext) EXT_UNIQID_HELPER(ext)
#define EXT_UNIQID_HELPER(ext) EXT_UNIQID_##ext

/* optimization parameters */
#ifndef BUFRADIXSORT_USE_SIMD_RELOCATE
#define BUFRADIXSORT_USE_SIMD_RELOCATE 0
#endif
#ifndef EXT_STREAM
#define EXT_STREAM SSE2
#endif
#ifndef UNROLL_HISTOGRAM
#define UNROLL_HISTOGRAM 8
#endif
#ifndef UNROLL_RELOCATE
#define UNROLL_RELOCATE 8
#endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

#define BKT_BIT 8
#define ELEM_SIZE_LOG_MAX 3

#define SUPPORTED_INT_BITS_LIST_LEN 4
#define SUPPORTED_INT_BITS_LIST (8, 16, 32, 64)

#define SUPPORTED_FLOAT_BITS_LIST_LEN 2
#define SUPPORTED_FLOAT_BITS_LIST (32, 64)

#endif /* BUFRADIXSORT_CONFIG_H */
