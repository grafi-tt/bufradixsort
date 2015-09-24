#include "bufradixsort.h"

#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>

template<class A>
static void print3(A data, A work1, A work2, size_t len) {
	std::cout << std::hex;
	std::cout << "INPUT" << std::endl;
	for (size_t i = 0; i < len; i++) {
		std::cout << std::setfill('0') << std::setw(16) << data[i] << std::endl;
	}
	std::cout << "RESULT bufradixsort" << std::endl;
	for (size_t i = 0; i < len; i++) {
		std::cout << std::setfill('0') << std::setw(16) << work1[i] << std::endl;
	}
	std::cout << "RESULT std::sort" << std::endl;
	for (size_t i = 0; i < len; i++) {
		std::cout << std::setfill('0') << std::setw(16) << work2[i] << std::endl;
	}
}

static bool test_uint32(std::mt19937 gen, bool verbose) {
	std::cout << "uint32 test" << std::endl;

	size_t len = 20000;
	std::vector<uint32_t> data(len);
	std::vector<uint32_t> work1(len);
	std::vector<uint32_t> work2(len);
	for (size_t i = 0; i < len; i++)
		data[i] = gen();

	std::copy(data.begin(), data.end(), work1.begin());
	bufradix_layout_t elem_layout[] = {{0, BUFRADIX_LAYOUT_UINT, 32}, {0, BUFRADIX_LAYOUT_END, 0}};
	bufradixsort(work1.data(), work2.data(), len, elem_layout);
	std::copy(data.begin(), data.end(), work2.begin());
	std::sort(work2.begin(), work2.end());

	bool result = !std::equal(work1.begin(), work1.end(), work2.begin());
	if (result && verbose) print3(data, work1, work2, len);
	return result;
}

static bool test_int32(std::mt19937 gen, bool verbose) {
	std::cout << "int32 test" << std::endl;

	size_t len = 20000;
	std::vector<int32_t> data(len);
	std::vector<int32_t> work1(len);
	std::vector<int32_t> work2(len);
	for (size_t i = 0; i < len; i++)
		data[i] = gen();

	std::copy(data.begin(), data.end(), work1.begin());
	bufradix_layout_t elem_layout[] = {{0, BUFRADIX_LAYOUT_INT, 32}, {0, BUFRADIX_LAYOUT_END, 0}};
	bufradixsort(work1.data(), work2.data(), len, elem_layout);
	std::copy(data.begin(), data.end(), work2.begin());
	std::sort(work2.begin(), work2.end());

	bool result = !std::equal(work1.begin(), work1.end(), work2.begin());
	if (result && verbose) print3(data, work1, work2, len);
	return result;
}

static bool(*tests[])(std::mt19937, bool) = {
	test_uint32,
	test_int32,
	NULL
};

int main() {
	std::mt19937 gen(3145);

	for (auto test_p = tests; *test_p; test_p++) {
		if ((*test_p)(gen, false)) {
			std::cout << "fail" << std::endl;
		}
	}

	return 0;
}
