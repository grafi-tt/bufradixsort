/* header */
#include "bufradixsort.h"
#include "bufradixsort_config.h"
#include "bufradixsort_histo.h"
#include "bufradixsort_relocate.h"

#include <omp.h>
#include <stdlib.h>
#include <string.h>
#ifdef BUFRADIXSORT_DEBUG
#include <stdio.h>
#include <sys/time.h>
#endif

#include <alloca.h>

#ifdef BUFRADIXSORT_DEBUG
static inline double dt(struct timeval ts2, struct timeval ts1) {
	return ts2.tv_sec-ts1.tv_sec + (double)(ts2.tv_usec-ts1.tv_usec)/1000000;
}
#endif

void bufradixsort(void *data, void *work, size_t elem_cnt, unsigned int elem_size, unsigned char *elem_order) {
	unsigned int elem_size_log;
	size_t (*all_histo)[BKT] = NULL;

	{
		elem_size_log = 0; elem_size_log--;
		size_t elem_size_tmp;
		for (elem_size_tmp = elem_size; elem_size_tmp; elem_size_log += 1, elem_size_tmp >>= 1);
		/* elem_size_log is SIZE_T_MAX if elem_size is 0 */
		if (elem_size_log > ELEM_SIZE_LOG_MAX || (unsigned int)1 << elem_size_log != elem_size) return;
	}

#pragma omp parallel
	{
		unsigned int tnum = omp_get_num_threads();
		unsigned int tid = omp_get_thread_num();

		size_t histo[BKT];
		unsigned char *copy_points[BKT];

		unsigned char *from = data;
		unsigned char *from_end = data;
		size_t from_offset = 0;
		unsigned char *dest = work;

		unsigned int t, bkt;
		size_t acc;

		unsigned int round, real_round = 0;
#ifdef BUFRADIXSORT_DEBUG
		struct timeval ts1, ts2;
#endif

		void *space = alloca(tnum*(sizeof(size_t[BKT])));
#pragma omp master
		all_histo = space;
#pragma omp barrier

		{
			unsigned int quo = elem_cnt / tnum;
			unsigned int mod = elem_cnt % tnum;
			from_offset = (tid * quo + (tid < mod ? tid : mod)) << elem_size_log;
			from = data + from_offset;
			from_end = from + ((quo + (tid < mod)) << elem_size_log);
//#pragma omp critical
			//printf("hoge %d %ld\n", tid, from_offset);
		}

		for (round = 0; round < elem_size; round++) {
			unsigned int bkt_type = elem_order[round] & ~BUFRADIX_BKT_POS_MASK;
			if (bkt_type == BUFRADIX_IGN) continue;
			real_round++;

			unsigned int bkt_pos = elem_order[round] & BUFRADIX_BKT_POS_MASK;
#ifdef BUFRADIXSORT_DEBUG
			gettimeofday(&ts1, NULL);
#endif
			memset(histo, 0, sizeof(size_t[BKT]));
			count_histo(from, from_end, elem_size_log, bkt_pos, histo);
#ifdef BUFRADIXSORT_DEBUG
			gettimeofday(&ts2, NULL);
#pragma omp critical
			printf("histo: bkt_pos %d thread %d seconds %f\n", bkt_pos, omp_get_thread_num(), dt(ts2, ts1));
#endif

#pragma omp critical
			for (bkt = 0; bkt < BKT; bkt++) {
				printf("histo %d %u %lu\n", tid, bkt, histo[bkt]);
			}
			memcpy(all_histo[tid], histo, sizeof(size_t[BKT]));

#pragma omp barrier
			for (bkt = 0; bkt < BKT; bkt++)
				copy_points[bkt] = dest;
			for (t = 0; t < tid; t++) {
				for (bkt = 0, acc = 0; bkt < BKT; bkt++) {
					acc += all_histo[t][bkt];
					copy_points[bkt] += acc << elem_size_log;
				}
			}
			for ( ; t < tnum; t++) {
				for (bkt = 0, acc = 0; bkt < BKT; bkt++) {
					copy_points[bkt] += acc << elem_size_log;
					acc += all_histo[t][bkt];
				}
			}
#pragma omp critical
			for (bkt = 0; bkt < BKT; bkt++) {
				printf("cp %d %u %lu\n", tid, bkt, copy_points[bkt]-dest);
			}

#ifdef BUFRADIXSORT_DEBUG
			gettimeofday(&ts1, NULL);
#endif
			relocate_data(from, from_end, dest, bkt_pos, histo, copy_points);
#ifdef BUFRADIXSORT_DEBUG
			gettimeofday(&ts2, NULL);
#pragma omp critical
			printf("relocate: bkt_pos %d thread %d seconds %f\n", bkt_pos, omp_get_thread_num(), dt(ts2, ts1));
#endif

			{
				size_t mylen = from_end - from;
				from_end = from - from_offset;
				from = dest + from_offset;
				dest = from_end;
				from_end = from + mylen;
			}
#pragma omp barrier
		}
		if (real_round % 2)
			memcpy(dest + from_offset, from, from_end - from);
	}
}
