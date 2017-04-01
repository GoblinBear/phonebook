CC = gcc
CFLAGS_common = -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = main
all: $(EXEC)

SRCS_common = main.c

main: phonebook_orig.o phonebook_tiny.o phonebook_hash.o module.h
	$(CC) $(CFLAGS_common) -o $@ $(SRCS_common) $^

phonebook_orig.o: phonebook_orig.c phonebook_orig.h module.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) -o $@ -c $<

phonebook_tiny.o: phonebook_tiny.c phonebook_tiny.h module.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) -o $@ -c $<

phonebook_hash.o: phonebook_hash.c phonebook_hash.h module.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) -o $@ -c $<

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./main 0 && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./main 0
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./main 1
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./main 2

output.txt: cache-test calculate
	./calculate orig.txt tiny.txt hash.txt

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt tiny.txt output.txt hash.txt runtime.png
