#include "bufradixsort.h"
#include "bufradixsort_config.h"
#include "bufradixsort_pp.h"
#include "bufradixsort_histo.h"
#include "bufradixsort_relocate.h"

#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <omp.h>

#ifdef BUFRADIXSORT_DEBUG
#include <stdio.h>
#include <sys/time.h>
#endif

#define BKT (1<<BKT_BIT)

#ifdef BUFRADIXSORT_DEBUG
static double dt(struct timeval ts2, struct timeval ts1) {
	return ts2.tv_sec-ts1.tv_sec + (double)(ts2.tv_usec-ts1.tv_usec)/1000000;
}
#endif

static unsigned int correct_position(unsigned int bits, unsigned int pos) {
	unsigned int i = 0;
	switch (bits) {
#define CORRECT_POSITION_CASE(BITS) case BITS: { \
	uint##BITS##_t tester = 0; \
	unsigned char *tester_ptr = (unsigned char*)&tester; \
	for (i = 0; i < BITS / CHAR_BIT; i++) \
		tester |= (uint##BITS##_t)i << (CHAR_BIT*i); \
	for (i = 0; *tester_ptr != pos; tester_ptr++, i++); \
} break
		ITERLIST(SUPPORTED_INT_BITS_LIST_LEN, SUPPORTED_INT_BITS_LIST, CORRECT_POSITION_CASE);
	}
	return i;
}

static int check_elem_size(const bufradix_layout_t *elem_layout, unsigned int *elem_size_log_p) {
	unsigned int elem_size = 0, elem_size_tmp, elem_size_log;
	bufradix_layout_t l;
	while ((l = *elem_layout++).type != BUFRADIX_LAYOUT_END) {
		if (l.type == BUFRADIX_LAYOUT_FLOAT) {
			int ok = 0;
#define CHECK_FLOAT_BITS_KERNEL(n) ok = ok || l.bits == n
			ITERLIST(SUPPORTED_FLOAT_BITS_LIST_LEN, SUPPORTED_FLOAT_BITS_LIST, CHECK_FLOAT_BITS_KERNEL);
			if (!ok) return -1;
		}
		if (l.bits % BKT_BIT) return -2;
		elem_size += l.bits / BKT_BIT;
	}
	for (elem_size_log = (unsigned int)0 - (unsigned int)1, elem_size_tmp = elem_size;
			elem_size_tmp;
			elem_size_log += 1, elem_size_tmp >>= 1);
	if ((unsigned int)1 << elem_size_log != elem_size) return -3;
	if (elem_size_log > ELEM_SIZE_LOG_MAX) return -4; /* elem_size_log is UINT_MAX if elem_size is 0 */
	*elem_size_log_p = elem_size_log;
	return 0;
}

void bufradixsort(void *data, void *work, size_t elem_cnt, const bufradix_layout_t *elem_layout) {
	unsigned int elem_size_log;
	size_t acc_histo[BKT];
	memset(acc_histo, 0, sizeof(size_t[BKT]));
	if (check_elem_size(elem_layout, &elem_size_log)) return;

#pragma omp parallel
	{
		int tnum = omp_get_num_threads();
		int tid = omp_get_thread_num();
		int t;

		size_t histo[BKT];
		unsigned char *copy_points[BKT];

		unsigned char *from = data;
		unsigned char *from_end = data;
		size_t from_offset = 0;
		unsigned char *dest = work;

		unsigned int bkt;
		size_t acc;

		unsigned int order = 0, sort_times = 0;
		unsigned int bkt_pos_base;
#ifdef BUFRADIXSORT_DEBUG
		struct timeval ts1, ts2;
#endif

		{
			size_t quo = elem_cnt / tnum;
			int mod = elem_cnt % tnum;
			from_offset = (tid * quo + (tid < mod ? tid : mod)) << elem_size_log;
			from = data + from_offset;
			from_end = from + ((quo + (tid < mod)) << elem_size_log);
		}

		while (1) {
			const bufradix_layout_t *elem_layout_tmp = elem_layout;
			bufradix_layout_t l;
			unsigned int pos;

			bkt_pos_base = 0;
			while ((l = *elem_layout_tmp++).type != BUFRADIX_LAYOUT_END && l.order != order)
				bkt_pos_base += l.bits / BKT_BIT;
			if (l.type == BUFRADIX_LAYOUT_END) break;
			if (l.type == BUFRADIX_LAYOUT_IGNORE) continue;
			order++, sort_times += l.bits / BKT_BIT;

			for (pos = 0; pos < l.bits / BKT_BIT; pos++) {
				unsigned int bkt_pos = bkt_pos_base + correct_position(l.bits,  pos);

#ifdef BUFRADIXSORT_DEBUG
				gettimeofday(&ts1, NULL);
#endif
				count_histo(from, from_end, elem_size_log, bkt_pos, histo);
#ifdef BUFRADIXSORT_DEBUG
				gettimeofday(&ts2, NULL);
#pragma omp critical
				printf("histo: bkt_pos %d thread %d seconds %f\n", bkt_pos, omp_get_thread_num(), dt(ts2, ts1));
#endif

#pragma omp critical
				for (bkt = 0, acc = 0; bkt < BKT; bkt++) {
					acc += histo[bkt];
					acc_histo[bkt] += acc;
				}
				for (t = tnum-1; t >= 0; t--) {
#pragma omp barrier
					if (t == tid) {
						for (bkt = 0; bkt < BKT; bkt++) {
							acc_histo[bkt] -= histo[bkt];
							copy_points[bkt] = dest + acc_histo[bkt];
						}
					}
				}

#ifdef BUFRADIXSORT_DEBUG
				gettimeofday(&ts1, NULL);
#endif
				relocate_data(from, from_end, dest, elem_size_log, bkt_pos, histo, copy_points);
#ifdef BUFRADIXSORT_DEBUG
				gettimeofday(&ts2, NULL);
#pragma omp critical
				printf("relocate: bkt_pos %d thread %d seconds %f\n", bkt_pos, omp_get_thread_num(), dt(ts2, ts1));
#endif

#pragma omp single
				memset(acc_histo, 0, sizeof(size_t[BKT])); /* here is the only safe position to clear acc_histo */

				{
					size_t mylen = from_end - from;
					from_end = from - from_offset;
					from = dest + from_offset;
					dest = from_end;
					from_end = from + mylen;
				}
#pragma omp barrier
			}
		}
		if (sort_times % 2)
			memcpy(dest + from_offset, from, from_end - from);
	}
}
