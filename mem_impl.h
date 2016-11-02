#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM 8000 // Amount of memory to malloc when free_list cannot satisfy a request

//Implements a new data structer "Block"
typedef struct block {
  uintptr_t size;
  struct block *next;
} Block;

extern uintptr_t total_freed; // Total amount of memory Freed.
extern Block* front; // Front of the free list.

#endif
