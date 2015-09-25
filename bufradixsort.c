#include "bufradixsort.h"
#include "bufradixsort_common.h"
#include "bufradixsort_histo.h"
#include "bufradixsort_relocate.h"

#include <limits.h>
#include <stdint.h>
#include <string.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#if BUFRADIXSORT_DEBUG
#include <stdio.h>
#include <sys/time.h>
#endif

static unsigned int correct_position(unsigned int bits, unsigned int pos) {
	unsigned int i = 0;
	switch (bits) {
#define CORRECT_POSITION_CASE(BITS) case BITS: { \
	UTYP(BITS) tester = 0; \
	unsigned char *tester_ptr = (unsigned char*)&tester; \
	for (i = 0; i < BITS / CHAR_BIT; i++) \
		tester |= (UTYP(BITS))i << (CHAR_BIT*i); \
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
#ifdef _OPENMP
	size_t acc_histo[BKT];
	memset(acc_histo, 0, sizeof(size_t[BKT]));
#endif
	if (check_elem_size(elem_layout, &elem_size_log)) return;

#ifdef _OPENMP
#pragma omp parallel
#endif
	{
#ifdef _OPENMP
		int tnum = omp_get_num_threads();
		int tid = omp_get_thread_num();
		int t;
#endif

		size_t histo[BKT];
		unsigned char *copy_points[BKT];

		unsigned char *from, *from_end;
		size_t from_offset;
		unsigned char *dest = work;

		unsigned int bkt;
		size_t acc;

		unsigned int order = 0, sort_times = 0;
		unsigned int bkt_pos_base;

#if BUFRADIXSORT_DEBUG
		struct timeval ts1, ts2;
#define DEBUG_TIME1() gettimeofday(&ts1, NULL)
#define DEBUG_TIME2() gettimeofday(&ts2, NULL)
#ifdef _OPENMP
#define DEBUG_PRINT(str) printf(str": thread %u seconds %f\n", tid, \
		ts2.tv_sec-ts1.tv_sec + (double)(ts2.tv_usec-ts1.tv_usec)/1000000)
#else /* _OPENMP */
#define DEBUG_PRINT(str) printf(str": seconds %f\n", \
		ts2.tv_sec-ts1.tv_sec + (double)(ts2.tv_usec-ts1.tv_usec)/1000000)
#endif /* _OPENMP */

#else /* BUFRADIXSORT_DEBUG */
#define DEBUG_TIME1()
#define DEBUG_TIME2()
#define DEBUG_PRINT(str)

#endif /* BUFRADIXSORT_DEBUG */

#ifdef _OPENMP
		{
			size_t quo = elem_cnt / tnum;
			int mod = elem_cnt % tnum;
			from_offset = (tid * quo + (tid < mod ? tid : mod)) << elem_size_log;
			from = data + from_offset;
			from_end = from + ((quo + (tid < mod)) << elem_size_log);
		}
#else
		from_offset = 0;
		from = data;
		from_end = from + (elem_cnt << elem_size_log);
#endif

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
				unsigned int real_pos = correct_position(l.bits,  pos);
				unsigned int bkt_fix_sign =
					(pos+1 == l.bits / BKT_BIT && (l.type == BUFRADIX_LAYOUT_INT || l.type == BUFRADIX_LAYOUT_FLOAT)) ?
						1u << (BKT_BIT-1) : 0;
				unsigned int float_bits_if_lsb =
					(pos == 0 && l.type == BUFRADIX_LAYOUT_FLOAT) ? l.bits : 0;
				unsigned int float_bits_if_msb =
					(pos+1 == l.bits / BKT_BIT && l.type == BUFRADIX_LAYOUT_FLOAT) ? l.bits : 0;

				DEBUG_TIME1();
				count_histo(from, from_end, elem_size_log, bkt_pos_base, real_pos, float_bits_if_lsb, histo);
				DEBUG_TIME2();
#ifdef _OPENMP
#pragma omp critical
#endif
				DEBUG_PRINT("histo");

#ifdef _OPENMP
#pragma omp critical
				for (bkt = 0, acc = 0; bkt < BKT; bkt++) {
					acc += histo[bkt^bkt_fix_sign];
					acc_histo[bkt^bkt_fix_sign] += acc;
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
#else
				for (bkt = 0, acc = 0; bkt < BKT; bkt++) {
					copy_points[bkt^bkt_fix_sign] = dest + acc;
					acc += histo[bkt^bkt_fix_sign];
				}
#endif

				DEBUG_TIME1();
				relocate_data(from, from_end, dest,
						elem_size_log, bkt_pos_base, real_pos, float_bits_if_msb, bkt_fix_sign, histo, copy_points);
				DEBUG_TIME2();
#ifdef _OPENMP
#pragma omp critical
#endif
				DEBUG_PRINT("relocate");

#ifdef _OPENMP
#pragma omp single
				memset(acc_histo, 0, sizeof(size_t[BKT])); /* here is the only safe position to clear acc_histo */
#endif

				{
					size_t mylen = from_end - from;
					from_end = from - from_offset;
					from = dest + from_offset;
					dest = from_end;
					from_end = from + mylen;
				}
#ifdef _OPENMP
#pragma omp barrier
#endif
			}
		}
		if (sort_times % 2)
			memcpy(dest + from_offset, from, from_end - from);
	}
}
