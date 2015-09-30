#include "bufradixsort.h"

#include <cstdint>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <utility>

typedef std::chrono::high_resolution_clock::duration duration_t;

static std::pair<duration_t, duration_t> test_uint32(std::mt19937 gen) {
	std::cout << "uint32 test" << std::endl;

	size_t len = 200000000;
	std::vector<uint32_t> data(len);
	std::vector<uint32_t> work1(len);
	std::vector<uint32_t> work2(len);
	for (size_t i = 0; i < len; i++)
		data[i] = gen();

	std::copy(data.begin(), data.end(), work1.begin());
	bufradix_layout_t elem_layout[] = {{0, BUFRADIX_LAYOUT_UINT, 32}, {0, BUFRADIX_LAYOUT_END, 0}};

	auto t1s = std::chrono::high_resolution_clock::now();
	bufradixsort(work1.data(), work2.data(), len, elem_layout);
	auto t1e = std::chrono::high_resolution_clock::now();
	auto d1 = t1e - t1s;

	auto t2s = std::chrono::high_resolution_clock::now();
	std::sort(data.begin(), data.end());
	auto t2e = std::chrono::high_resolution_clock::now();
	auto d2 = t2e - t2s;

	return std::make_pair(d1, d2);
}

static std::pair<duration_t, duration_t>(*tests[])(std::mt19937) = {
	test_uint32,
	NULL
};

int main() {
	std::mt19937 gen(3145);

	for (auto test_p = tests; *test_p; test_p++) {
		auto dp = (*test_p)(gen);
		std::cout << "bufradixsort " << std::chrono::duration_cast<std::chrono::milliseconds>(dp.first).count() << std::endl;
		std::cout << "std::sort " << std::chrono::duration_cast<std::chrono::milliseconds>(dp.second).count() << std::endl;;
	}

	return 0;
}
