all: benchmark
CC=gcc

benchmark: benchmark.o
	$(CC) benchmark.c -o benchmark.o -pthread

.PHONY: clean
clean:
	rm -f *.o
