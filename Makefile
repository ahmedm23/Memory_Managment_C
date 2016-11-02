#The compiler to use
CC = gcc
#The options passed to the compiler
CFLAGS = -Wall -std=c11

bench: bench.o getmem.o get_mem_stats.o freemem.o print_heap.o check_heap.o
	$(CC) $(CFLAGS) -o $@ $^

bench.o: bench.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c $<

getmem.o: getmem.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c $<

get_mem_stats.o: get_mem_stats.c mem_impl.h mem.h
	$(CC) $(CFLAGS) -c $<

freemem.o: freemem.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c $<

check_heap.o: check_heap.c  mem_impl.h mem.h
	$(CC) $(CFLAGS) -c $<

print_heap.o: print_heap.c mem.h mem_impl.h
	$(CC) $(CFLAGS) -c $<
		          
output:  
	./bench 
		        
dest:        
	make clean;
	git log --pretty=format:"%h - %an, %ar : %s" > git.log;
	tar -c -f hw5.tar *.h *.c git.log Makefile README.md

    
all: bench

clean: 
	rm  *.o bench  	
