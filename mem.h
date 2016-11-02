//Ahmed Moalim 

#ifndef MEM_H
#define MEM_H
#include <stdio.h>
#include <stdint.h>

//Returns a pointer to a new block of storage with at least size bytes of memoy 
void* getmem(uintptr_t size);

//Returns the block of storage at location p to the pool of available free storage.
void freemem(void* p);

//Stores statistics about the current state of the free_block object
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, 
		uintptr_t* n_free_blocks);

//Prints a formatted listing to file f showing the blocks on the free list.
void print_heap();

//Checks for possible problems with the free list data structure.
void check_heap();

#endif
