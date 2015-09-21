#ifndef BUFRADIXSORT_HISTO_H
#define BUFRADIXSORT_HISTO_H

#include "bufradixsort_config.h"
#include "bufradixsort_unroll.h"

#if CHAR_BIT == BKT_BIT

#define HISTO_KERNEL(ELEM_SIZE_LOG) do { \
	unsigned char bkt = *data_cur; \
	data_cur += 1 << ELEM_SIZE_LOG; \
	histo_rst[bkt]++; \
} while (0)

#define HISTO_CASE(ELEM_SIZE_LOG) case ELEM_SIZE_LOG: do { \
	size_t len = (dataend-data) >> ELEM_SIZE_LOG; \
	const unsigned char *dataalgn = data; \
	size_t mod = len % UNROLL_HISTOGRAM; \
	if (mod) dataalgn += mod << ELEM_SIZE_LOG; \
	while (data_cur < dataalgn) { \
		HISTO_KERNEL(ELEM_SIZE_LOG); \
	} \
	while(data_cur < dataend) { \
		ITERARG(UNROLL_HISTOGRAM, HISTO_KERNEL, ELEM_SIZE_LOG); \
		data += UNROLL_HISTOGRAM << ELEM_SIZE_LOG; \
	} \
} while(0)

static inline void count_histo(const unsigned char *data, const unsigned char *dataend,
		unsigned int elem_size_log, unsigned int bkt_pos, size_t *histo) {
	size_t *restrict histo_rst = histo; \
	const unsigned char *restrict data_cur = data+bkt_pos; \
	switch (elem_size_log) {
		EVAL(ITERNUM(ELEM_SIZE_LOG_MAX, HISTO_CASE));
	}
}


#else

#error "todo"

#endif

#endif /* BUFRADIXSORT_HISTO_H */
