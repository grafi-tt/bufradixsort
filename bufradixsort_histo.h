#ifndef BUFRADIXSORT_HISTO_H
#define BUFRADIXSORT_HISTO_H

#include "bufradixsort_common.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*
 * If it is LSB of a float, negate non-sign buckets if the sign is minus.
 */
#define HISTO_FLOAT_KERNEL(ELEM_SIZE, FLOAT_BITS) do { \
	UTYP(FLOAT_BITS) val; \
	memcpy(&val, data_cur, sizeof(val)); \
	UTYP(FLOAT_BITS) mask = ((val >> (FLOAT_BITS-1)) ? (UTYP(FLOAT_BITS))0-1 : 0) >> 1; \
	val &= mask; \
	memcpy(data_cur, &val, sizeof(val)); \
	data_cur += ELEM_SIZE; \
	histo_rst[val & (BKT-1)]++; \
} while (0);

#define HISTO_FLOAT_KERNEL_ONEARG(arg) HISTO_FLOAT_KERNEL(FST(arg), SND(arg))

#define HISTO_FLOAT_CASE_F_DO(FLOAT_BITS, ELEM_SIZE) case FLOAT_BITS: { \
	unsigned char *data_cur = data_rst + bkt_pos_base; \
	while (data_cur < data_algn) { \
		HISTO_FLOAT_KERNEL(ELEM_SIZE, FLOAT_BITS); \
	} \
	while(data_cur < data_end) { \
		ITERARG(UNROLL_HISTOGRAM, HISTO_FLOAT_KERNEL_ONEARG, (ELEM_SIZE, FLOAT_BITS)); \
	} \
} break

#define HISTO_FLOAT_CASE_F_EMP(FLOAT_BITS)

#define HISTO_FLOAT_CASE_F(FLOAT_BITS, ELEM_SIZE) \
	IF0(SUB(DIV(FLOAT_BITS, BKT_BIT), ELEM_SIZE), \
		HISTO_FLOAT_CASE_F_DO(FLOAT_BITS, ELEM_SIZE), HISTO_FLOAT_CASE_F_EMP(FLOAT_BITS))

/*
 * Otherwise, simply count histgram.
 */
#define HISTO_NONFLOAT_KERNEL(ELEM_SIZE) do { \
	unsigned char bkt = *data_cur; \
	data_cur += ELEM_SIZE; \
	histo_rst[bkt]++; \
} while (0)

#define HISTO_NONFLOAT_CASE_F(ELEM_SIZE) default: { \
	unsigned char *data_cur = data_rst + bkt_pos_base + real_pos; \
	while (data_cur < data_algn) { \
		HISTO_NONFLOAT_KERNEL(ELEM_SIZE); \
	} \
	while(data_cur < data_end) { \
		ITERARG(UNROLL_HISTOGRAM, HISTO_NONFLOAT_KERNEL, ELEM_SIZE); \
	} \
} break

/*
 * Generic part.
 */
#define HISTO_CASE_E(ELEM_SIZE_LOG) case ELEM_SIZE_LOG: { \
	switch (float_bits_if_lsb) { \
		ITERLISTARG(SUPPORTED_FLOAT_BITS_LIST_LEN, SUPPORTED_FLOAT_BITS_LIST, HISTO_FLOAT_CASE_F, POW(2, ELEM_SIZE_LOG)); \
		HISTO_NONFLOAT_CASE_F(POW(2, ELEM_SIZE_LOG)); \
	} \
} break

static void count_histo(unsigned char *data, unsigned char *data_end,
		unsigned int elem_size_log, unsigned int bkt_pos_base, unsigned int real_pos, unsigned int float_bits_if_lsb,
		size_t *histo) {
	unsigned char *data_algn = data +
		((((data_end - data) >> elem_size_log) % UNROLL_HISTOGRAM) << elem_size_log);
	unsigned int bkt;
	memset(histo, 0, sizeof(size_t[BKT]));
	{
		unsigned char *restrict data_rst = data;
		size_t *restrict histo_rst = histo;
		switch (elem_size_log) {
			ITERNUM(SUCC(ELEM_SIZE_LOG_MAX), HISTO_CASE_E);
		}
	}
	for (bkt = 0; bkt < BKT; bkt++)
		histo[bkt] <<= elem_size_log;
}

#endif /* BUFRADIXSORT_HISTO_H */
