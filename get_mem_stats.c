//Ahmed Moalim 
#include "mem.h"
#include "mem_impl.h"

//tore statistics about the current state of the memory manager in the three, 
//integer variables whose addresses are given as arguments.
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks) {
   Block *curr = front->next; // Refrence to the Start of the Free List 
   uintptr_t free; // The total Amount of storage in bytes that is currently stored
   uintptr_t blocks; // The total amount of blocks in the Free List
   
   while(curr != NULL) {
      free += curr->size;
      blocks++;
      curr = curr->next;
   }

   *n_free_blocks = blocks;
   *total_free = free;
   *total_size = total_freed;
}
