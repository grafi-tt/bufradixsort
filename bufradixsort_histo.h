#ifndef BUFRADIXSORT_HISTO_H
#define BUFRADIXSORT_HISTO_H

#include "bufradixsort_config.h"
#include "bufradixsort_pp.h"

#include <stddef.h>

#define HISTO_KERNEL(ELEM_SIZE_LOG) do { \
	unsigned char bkt = *data_cur; \
	data_cur += 1 << ELEM_SIZE_LOG; \
	histo_rst[bkt]++; \
} while (0)

#define HISTO_CASE(ELEM_SIZE_LOG) case ELEM_SIZE_LOG: { \
	while (data_cur < data_algn) { \
		HISTO_KERNEL(ELEM_SIZE_LOG); \
	} \
	while(data_cur < data_end) { \
		ITERARG(UNROLL_HISTOGRAM, HISTO_KERNEL, ELEM_SIZE_LOG); \
		data += UNROLL_HISTOGRAM << ELEM_SIZE_LOG; \
	} \
} break

static void count_histo(const unsigned char *data, const unsigned char *data_end,
		unsigned int elem_size_log, unsigned int bkt_pos, size_t *histo) {
	size_t *restrict histo_rst = histo;
	const unsigned char *data_algn = data +
		((((data_end - data) >> elem_size_log) % UNROLL_HISTOGRAM) << elem_size_log);
	const unsigned char *restrict data_cur = data + bkt_pos;
	switch (elem_size_log) {
		ITERNUM(ELEM_SIZE_LOG_MAX, HISTO_CASE);
	}
}

#endif /* BUFRADIXSORT_HISTO_H */
