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

#define ALIGNED(multiple)
#define ASSUME_ALIGNED(ptr, multiple) (ptr)
#define NOINLINE
#define LIKELY(x) x
#define UNLIKELY(x) x
#define PREFETCH(ptr, rw, loc)

#endif

/* optimization parameters */
#ifndef BUFRADIXSORT_FUSE_RELOCATE_HISTOGRAM
#define BUFRADIXSORT_FUSE_RELOCATE_HISTOGRAM 1
#endif
#ifndef BUFRADIXSORT_USE_SIMD_RELOCATE
#define BUFRADIXSORT_USE_SIMD_RELOCATE 0
#endif
#ifndef BUFRADIXSORT_USE_STREAM_RELOCATE_IFSIMD
#define BUFRADIXSORT_USE_STREAM_RELOCATE_IFSIMD 1
#endif
#ifndef UNROLL_HISTOGRAM
#define UNROLL_HISTOGRAM 8
#endif
#ifndef BUFRADIXSORT_UNROLL_COUNT_RELOCATE
#define BUFRADIXSORT_UNROLL_COUNT_RELOCATE 8
#endif
#ifndef BUFRADIXSORT_BUFFER_SIZE
#define BUFRADIXSORT_BUFFER_SIZE 16
#endif

#define BKT_BIT 8
#define ELEM_SIZE_LOG_MAX 3

#define BKT (1<<BKT_BIT)

#endif /* BUFRADIXSORT_CONFIG_H */
