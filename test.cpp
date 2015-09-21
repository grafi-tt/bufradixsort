#include <sys/time.h>

#include "bufradixsort.h"

#include <stdint.h>
#include <cstdlib>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#define LEN 20000000

static uint32_t sdata[LEN];
static uint32_t swork1[LEN];
static uint32_t swork2[LEN];

static inline double dt(struct timeval &ts2, struct timeval &ts1) {
	return ts2.tv_sec-ts1.tv_sec + (double)(ts2.tv_usec-ts1.tv_usec)/1000000;
}

int main() {
	struct timeval ts1, ts2;

	uint32_t *data = sdata;
	uint32_t *work1 = swork1;
	uint32_t *work2 = swork2;

	std::srand(LEN+314);
	for (int round=0; round<2; round++) {
			for (size_t i = 0; i < LEN; i++) {
				data[i] = std::rand();
			}

			std::copy(data, data+LEN, work1);
			gettimeofday(&ts1, NULL);
			unsigned char elem_order[] = {BUFRADIX_KEY | 0, BUFRADIX_KEY | 1, BUFRADIX_KEY | 2, BUFRADIX_KEY | 3};
			bufradixsort(work1, work2, LEN, sizeof(uint32_t), elem_order);
			gettimeofday(&ts2, NULL);
			std::cout << "bufradixsort" << dt(ts2, ts1) << std::endl;

			gettimeofday(&ts1, NULL);
			std::sort(data, data+LEN);
			gettimeofday(&ts2, NULL);
			std::cout << "std::sort" << dt(ts2, ts1) << std::endl;

			for (size_t i = 0; i < LEN; i++) {
				if (work1[i] != data[i]) {
					std::cout << "bufradix sort fails" << std::endl;
				}
			}
	}

	/*
	std::cout << std::hex;
	std::cout << "RESULT bufradixsort" << std::endl;
	for (int i = 0; i < LEN; i++) {
		std::cout << std::setfill('0') << std::setw(8) << work1[i] << std::endl;
	}
	std::cout << "RESULT std::sort" << std::endl;
	for (int i = 0; i < LEN; i++) {
		std::cout << std::setfill('0') << std::setw(8) << data[i] << std::endl;
	}
	*/

	return 0;
}
