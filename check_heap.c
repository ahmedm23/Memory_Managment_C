//Ahmed Moalim
#include "mem.h"
#include "mem_impl.h"
#include <assert.h>

//Checks for possible problems in the free list
void check_heap() {
   if(front->next == NULL)
      return;
	        
   int min_block_size = 32;
   Block *curr = front->next;
		        
   if(curr->next == NULL)
      assert(curr->size >= min_block_size); // Checks if the size of the individual block is less then minumum value
			    
   while(curr->next != NULL) {
      assert(curr->size >= min_block_size); // Checks if the size of the individual block is less then minumum value
      assert(curr->size + (uintptr_t) curr < (uintptr_t) curr->next); // Checks if the adresses of the blocks are in proper order
      assert((uintptr_t) curr < (uintptr_t) curr->next); // Checks if Blocks overlap or touch 

      curr = curr->next;     
   }

}
