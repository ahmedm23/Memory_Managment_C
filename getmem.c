//Ahmed Moalim 
#include "mem.h"
#include "mem_impl.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#define MAX_BYTES 144 //Max amount of bytes that a block can be over for a request

//Function definitions
void init_free_list();
Block* split(Block *block, uintptr_t size);

//Returns a block from the free list satisfying the size passed in
void *getmem(uintptr_t size) {
   size = 16 * ( 1 + (size-1) /16);
   size += sizeof(Block); //Increments Size by size of block and rounds up to the nearest multiple of 16

   if(front == NULL)
      init_free_list();
   
   check_heap();
   Block *curr = front;
   Block *mem;
   while(curr->next != NULL) {
      if(size <= curr->next->size ) {
         if(size + MAX_BYTES <= curr->next->size) {
	    return split(curr->next, size) + 1;   
	 }

         mem = curr->next + 1;
	 curr->next = curr->next->next;
	 check_heap();
         return mem;
      }
      curr = curr->next;
   }

   curr->next = malloc(MEM + size);
   curr = curr->next;
   
   if (curr == NULL) {
      fprintf(stderr, "getmem: malloc failed\n");
      exit(1);
   }

   curr->size = MEM + size;
   total_freed += MEM + size;
   curr->next = NULL;
   check_heap();
   return split(curr, size) + 1;
}   

//Initializes the front Block struct
void init_free_list() {
   front = malloc(sizeof(Block));

   if (front == NULL) {
      fprintf(stderr, "init_free_list: malloc failed\n");
      exit(1);
   }

   front->size = 0;
   front->next = NULL;
}

//Splits a block into to smaller blocks, one being the size passed in
Block* split(Block *block, uintptr_t size) {
   Block *requested_Block;//Block for the requested size;
   block->size -= (size);

   requested_Block = (Block*) (((uintptr_t) block) + block->size);
   requested_Block->next = NULL;
   requested_Block->size = size;
   
   return requested_Block;
}

