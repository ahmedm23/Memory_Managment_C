//Ahmed Moalim 
// This function takes in a pointer to a block of memory. Returns the
// block of available memory. However, if p is null then this function
// returns immediately.

#include "mem.h"
#include "mem_impl.h"
#include <inttypes.h>
void insert(Block* block, Block* end);
void merge(Block* block);

// Frees a block of storage.
void freemem(void* freeptr) {
  Block* free_block;
  Block* curr;

  // checks heap to make sure its in good shape
  check_heap();
  
  curr = front;
  free_block = (Block*) freeptr;
  if (free_block == NULL)
    return;
  free_block--;

  // iterate until the end of nodes of if address is to large
  while ((curr->next != NULL) && (curr->next < free_block)) {
    curr = curr->next;
  }
  insert(free_block,curr);
  merge(free_block);
  merge(curr);

  // check heap before ending to make sure block was freed 
  check_heap();
 }

// Attaches block to the end
void insert(Block* block, Block* end) {
  block->next = end->next; // place
  end->next = block;
}

// Merge blockes if size and block position are equal to position
// of the the next block.
void merge(Block* block) {
  if(block->size + (uintptr_t) block == (uintptr_t) block->next) {
    block->size = block->size + block->next->size;
    block->next = block->next->next;
  }
}
