CFLAGS=-Wall -Wextra -O2 -mtune=native -march=native

BUFRADIXSORTFILES=bufradixsort.c bufradixsort.h bufradixsort_common.h bufradixsort_config.h bufradixsort_config_verify.h bufradixsort_pp.h bufradixsort_pp_primrec.h bufradixsort_histo.h bufradixsort_relocate.h

all: test

test: test.o bufradixsort.o
	g++ -fopenmp $^ -o $@

test.o: test.cpp bufradixsort.h
	g++ $(CFLAGS) -fopenmp -std=c++11 -c test.cpp -o $@ -g

bufradixsortdebug.o: $(BUFRADIXSORTFILES)
	gcc $(CFLAGS) -fopenmp -std=c99 -c bufradixsort.c -o $@ -g -DBUFRADIXSORT_DEBUG

bufradixsort.o: $(BUFRADIXSORTFILES)
	gcc $(CFLAGS) -fopenmp -std=c99 -c bufradixsort.c -o $@

.PHONY clean:
	rm -f *.o bench test

#bench: bench.o bufradixsort.o bufradixsort_nofuse.o bufradixsort_nofuse_nostream.o SFMT.o
#	g++ -fopenmp $^ -o $@

#bench.o: bench.cpp mapsort.hpp bufradixsort.h
#	g++ $(CFLAGS) $(SFMTFLAGS) -fopenmp -c bench.cpp -o $@
