#ifndef BUFRADIXSORT_RELOCATE_H
#define BUFRADIXSORT_RELOCATE_H

#define BUF DIV(4, BUFFER_SIZE)
#define TYPE uint32_t

#include "bufradixsort_relocate_casewnd.h"

#include <stdint.h>
#include <string.h>

static NOINLINE void trick_head(TYPE *copy_point, TYPE *buf_point, unsigned int invalid_elems_cnt) {
	TYPE *copy_end_point = copy_point+BUF;
	buf_point += invalid_elems_cnt;
	copy_point += invalid_elems_cnt;
	while (copy_point < copy_end_point)
		*copy_point++ = *buf_point++;
}

static inline void relocate_data(const unsigned char *vdata, const unsigned char *vdata_end, unsigned char *vdest,
		int bkt_pos, const size_t *histo, unsigned char **vcopy_points) {
	const TYPE *data = (const TYPE*)vdata;
	const TYPE *data_end = (const TYPE*)vdata_end;
	TYPE *dest = (TYPE*)vdest;
	TYPE **copy_points = (TYPE**)vcopy_points;

	TYPE ALIGNED(BUFFER_SIZE) buf[BKT][BUF];
	TYPE *buf_points[BKT];
	unsigned int first_buf_bkt = BKT;
	unsigned int invalid_elems_cnt = 0;
	unsigned int bkt;

	/*
	 * If current thread is sorting to the first area of destination,
	 * even temporalily writing to the preceeding position should be considered as dangerous,
	 * since they could be used by other parts of the program or be protected by segment.
	 * So we must detect writing to the first position.
	 */
	{
		TYPE* dest_algn = (void*)((uintptr_t)dest & -BUFFER_SIZE);
		if (dest != dest_algn) {
			TYPE* dest_algn_up = dest_algn+BUF;
			for (bkt = 0; bkt < BKT; bkt++) {
				TYPE *strt_point = copy_points[bkt];
				TYPE *ends_point = strt_point+histo[bkt];
				if (ends_point >= dest_algn_up) {
					if (strt_point < dest_algn_up) {
						first_buf_bkt = bkt;
						invalid_elems_cnt = strt_point-dest_algn;
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
		TYPE *copy_point = copy_points[bkt];
		TYPE *copy_point_algn = (void*)((uintptr_t)copy_point & -BUFFER_SIZE);
		int buf_offset = copy_point-copy_point_algn;
		copy_points[bkt] = copy_point-buf_offset;
		buf_points[bkt] = buf[bkt]+buf_offset;
	}

	/*
	 * Buffers must be 0-initialized in order to mitigate with extra histogram counts by fixing 0-bkt.
	 */
	memset(buf, 0, BKT*BUFFER_SIZE);

	switch (bkt_pos) {
#define WND 0
		RELOCATE_CASEWND;
#undef WND
#define WND 1
		RELOCATE_CASEWND;
#undef WND
#define WND 2
		RELOCATE_CASEWND;
#undef WND
#define WND 3
		RELOCATE_CASEWND;
#undef WND
	}

#pragma omp barrier
	for (bkt = 0; bkt < BKT; bkt++) {
		TYPE *ends_point = copy_points[bkt]+((buf_points[bkt]-buf[bkt]));
		TYPE *strt_point = ends_point-histo[bkt];
		TYPE *ends_point_algn = (void*)((uintptr_t)ends_point & -BUFFER_SIZE);
		TYPE *strt_point_algn = (void*)((uintptr_t)strt_point & -BUFFER_SIZE);
		TYPE *copy_point;
		TYPE *buf_point;

		if (strt_point_algn == ends_point_algn) {
			copy_point = strt_point;
			buf_point = buf[bkt]+(strt_point-strt_point_algn);
		} else {
			copy_point = ends_point_algn;
			buf_point = buf[bkt];
		}
		while (copy_point < ends_point)
			*copy_point++ = *buf_point++;
	}
}

#endif /* BUFRADIXSORT_RELOCATE_H */
