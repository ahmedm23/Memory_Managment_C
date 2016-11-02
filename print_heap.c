//Ahmed Moalim 

// This function prints to the specified file past in.
// It prints the address of the blocks and size fo the block
// on the same line

#include "mem_impl.h"
#include "mem.h"
#include <stdio.h>
#include <inttypes.h>

// Prints to file f, the list of free blocks.
void print_heap() {
  Block* curr; // initialize
  
  curr = (Block*) front->next; // get first block
  while(curr != NULL) {
    printf("Block address: %" PRIuPTR "\t", (uintptr_t) curr);
    printf("Block size: %" PRIuPTR "\n", curr->size);
    curr = curr->next; // iterate step
  }
}
