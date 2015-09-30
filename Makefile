CFLAGS=-Wall -Wextra -O2 -fgcse-after-reload -mtune=native -march=native

BUFRADIXSORTFILES=bufradixsort.c bufradixsort.h bufradixsort_common.h bufradixsort_config.h bufradixsort_config_verify.h bufradixsort_pp.h bufradixsort_pp_primrec.h bufradixsort_histo.h bufradixsort_relocate.h

all: test bench

bench: bench.o bufradixsort.o
	g++ -fopenmp $^ -o $@

bench.o: bench.cpp bufradixsort.h
	g++ -std=c++11 $(CFLAGS) -fopenmp -c bench.cpp -o $@

test: test.o bufradixsort.o
	g++ -fopenmp $^ -o $@

test.o: test.cpp bufradixsort.h
	g++ -std=c++11 $(CFLAGS) -fopenmp -c test.cpp -o $@ -g

bufradixsortdebug.o: $(BUFRADIXSORTFILES)
	gcc -std=c99 $(CFLAGS) -fopenmp -c bufradixsort.c -o $@ -g -DBUFRADIXSORT_DEBUG

bufradixsort.o: $(BUFRADIXSORTFILES)
	gcc -std=c99 $(CFLAGS) -fopenmp -c bufradixsort.c -o $@

.PHONY clean:
	rm -f *.o bench test
