#ifndef BUFRADIXSORT_RELOCATE_H
#define BUFRADIXSORT_RELOCATE_H

#define BUF DIV(4, BUFRADIXSORT_BUFFER_SIZE)
#define TYPE uint32_t

#include "bufradixsort_relocate_casewnd.h"

#include <stdint.h>
#include <string.h>

static inline void relocate_data(const unsigned char *vdata, const unsigned char *vdata_end, unsigned char *vdest,
		int bkt_pos, const size_t *histo, unsigned char **vcopy_points) {
	const TYPE *data = (const TYPE*)vdata;
	const TYPE *data_end = (const TYPE*)vdata_end;
	TYPE *dest = (TYPE*)vdest;
	TYPE **copy_points = (TYPE**)vcopy_points;

	TYPE ALIGNED(sizeof(TYPE[BUF])) buf[BKT][BUF];
	TYPE *buf_points[BKT];
	//unsigned int first_buf_bkt = BKT;
	unsigned int bkt;

	/*
	 * Set up buf_points and copy_points (aligned), that is displays of the buffers and the dest resp.
	 * Copypoints are aligned by the number of elements of a buffer.
	 */
	for (bkt = 0; bkt < BKT; bkt++) {
		TYPE *copy_point = copy_points[bkt];
		TYPE *copy_point_algn = (void*)((uintptr_t)copy_point & -BUF*sizeof(TYPE));
		int buf_offset = copy_point-copy_point_algn;
		copy_points[bkt] = copy_point-buf_offset;
		buf_points[bkt] = buf[bkt]+buf_offset;
	}

	/*
	 * Buffers must be 0-initialized in order to mitigate with extra histogram counts by fixing 0-bkt.
	 */
	memset(buf, 0, sizeof(TYPE[BKT][BUF]));

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
		TYPE *ends_point_algn = (void*)((uintptr_t)ends_point & -BUF*sizeof(TYPE));
		TYPE *strt_point_algn = (void*)((uintptr_t)strt_point & -BUF*sizeof(TYPE));
		TYPE *copy_point;
		TYPE *buf_point;

		if (strt_point_algn == ends_point_algn) {
			copy_point = strt_point;
			buf_point = buf[bkt]+(strt_point-strt_point_algn);
		} else {
			copy_point = ends_point_algn;
			buf_point = buf[bkt];
		}
		while (copy_point < ends_point) {
			TYPE cp = *buf_point++;
			*copy_point++ = cp;
		}
	}
}

#endif /* BUFRADIXSORT_RELOCATE_H */
