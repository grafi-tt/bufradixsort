#ifndef BUFRADIXSORT_HISTO_H
#define BUFRADIXSORT_HISTO_H

#include "bufradixsort_common.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*
 * If it is LSB of a float, negate non-sign buckets if the sign is minus.
 */
#define HISTO_FLOAT_KERNEL(ELEM_SIZE_LOG, FLOAT_BITS) do { \
	UTYP(FLOAT_BITS) v = *(UTYP(FLOAT_BITS)*)data_cur; \
	UTYP(FLOAT_BITS) mask = ((v >> (FLOAT_BITS-1)) ? (UTYP(FLOAT_BITS))0-1 : 0) >> 1; \
	v &= mask; \
	*(UTYP(FLOAT_BITS)*)data_cur = v; \
	data_cur += 1 << ELEM_SIZE_LOG; \
	histo_rst[v & (BKT-1)]++; \
} while (0);

#define HISTO_FLOAT_KERNEL_ONEARG(arg) HISTO_FLOAT_KERNEL(FST(arg), SND(arg))

#define HISTO_FLOAT_CASE_F_DO(FLOAT_BITS, ELEM_SIZE_LOG) case FLOAT_BITS: { \
	const unsigned char *restrict data_cur = data + bkt_pos_base; \
	while (data_cur < data_algn) { \
		HISTO_FLOAT_KERNEL(ELEM_SIZE_LOG, FLOAT_BITS); \
	} \
	while(data_cur < data_end) { \
		ITERARG(UNROLL_HISTOGRAM, HISTO_FLOAT_KERNEL_ONEARG, (ELEM_SIZE_LOG, FLOAT_BITS)); \
	} \
} break

#define HISTO_FLOAT_CASE_F_EMP(FLOAT_BITS) case FLOAT_BITS:

#define HISTO_FLOAT_CASE_F(FLOAT_BITS, ELEM_SIZE_LOG) \
	IF0(SUB(DIV(FLOAT_BITS, BKT_BIT), POW(2, ELEM_SIZE_LOG)), \
		HISTO_FLOAT_CASE_F_DO(FLOAT_BITS, ELEM_SIZE_LOG), HISTO_FLOAT_CASE_F_EMP(FLOAT_BITS))

/*
 * Otherwise, simply count histgram.
 */
#define HISTO_NONFLOAT_KERNEL(ELEM_SIZE_LOG) do { \
	unsigned char bkt = *data_cur; \
	data_cur += 1 << ELEM_SIZE_LOG; \
	histo_rst[bkt]++; \
} while (0)

#define HISTO_NONFLOAT_CASE_F(ELEM_SIZE_LOG) default: { \
	const unsigned char *restrict data_cur = data + bkt_pos_base + real_pos; \
	while (data_cur < data_algn) { \
		HISTO_NONFLOAT_KERNEL(ELEM_SIZE_LOG); \
	} \
	while(data_cur < data_end) { \
		ITERARG(UNROLL_HISTOGRAM, HISTO_NONFLOAT_KERNEL, ELEM_SIZE_LOG); \
	} \
} break

/*
 * Generic part.
 */
#define HISTO_CASE_E(ELEM_SIZE_LOG) case ELEM_SIZE_LOG: { \
	switch (float_bits_if_lsb) { \
		ITERLISTARG(SUPPORTED_FLOAT_BITS_LIST_LEN, SUPPORTED_FLOAT_BITS_LIST, HISTO_FLOAT_CASE_F, ELEM_SIZE_LOG); \
		HISTO_NONFLOAT_CASE_F(ELEM_SIZE_LOG); \
	} \
}

static void count_histo(unsigned char *data, unsigned char *data_end,
		unsigned int elem_size_log, unsigned int bkt_pos_base, unsigned int real_pos, unsigned int float_bits_if_lsb,
		size_t *histo) {
	size_t *restrict histo_rst = histo;
	const unsigned char *data_algn = data +
		((((data_end - data) >> elem_size_log) % UNROLL_HISTOGRAM) << elem_size_log);
	unsigned int bkt;
	memset(histo, 0, sizeof(size_t[BKT]));
	switch (elem_size_log) {
		ITERNUM(SUCC(ELEM_SIZE_LOG_MAX), HISTO_CASE_E);
	}
	for (bkt = 0; bkt < BKT; bkt++)
		histo[bkt] <<= elem_size_log;
}

#endif /* BUFRADIXSORT_HISTO_H */
