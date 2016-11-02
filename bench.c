//Ahmed Moalim 

// This program tests the capabilities of the getmem and fremem by
// randomly creating different sized blocks to either be freed or
// requested.
//
// There are seven parameters. Ntrials determines how many tests are done.
// Pctget is the percent of the total getmem/freemem calls that should
// happen during the test. Pctlarge is the percentage of "large" memory
// blocks compared to "small". Small_limit sets the largest size in bytes
// of the "small" block. Large_limit sets largest size in bytes of a
// "large" block. Random_seed is the initial seed value for the random
// number generator.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include <time.h>
#include <inttypes.h>
#include "mem_impl.h"

#define NTRIALS 10000;
#define PCTGET 60;
#define PCTLARGE 10;
#define SMALL_LIMIT 200;
#define LARGE_LIMIT 20000;

void print_stats(clock_t time);
Block* front = NULL;
uintptr_t total_freed = 0;

int main (int argc, char** argv) {
  // set of if/else statements for parameters
  unsigned int ntrials = argc > 1 ? atoi(argv[1]) : NTRIALS;
  unsigned int pctget = argc > 2 ? atoi(argv[2]) : PCTGET;
  unsigned int pctlarge = argc > 3 ? atoi(argv[3]) : PCTLARGE;
  unsigned int small_limit = argc > 4 ? atoi(argv[4]) : SMALL_LIMIT;
  unsigned int large_limit = argc > 5 ?  atoi(argv[5]) : LARGE_LIMIT;

  // random seed initialize
  srand((unsigned int)time(NULL));
  unsigned int random_seed = argc > 6 ? atoi(argv[6]) : rand();
  srand(random_seed);
  
  void* list_access[ntrials]; // Allows for instantaneous access to blocks
  int block_memory[ntrials]; // get random memory sizes
  int random_blocks[ntrials]; // List of the array of blocks above
  int i; // forloop iterator
  int size = 0; // number of blocks accounted for

  // randomize the size of the blocks and the order of free/request
  for (i = 0; i < ntrials; i++) {
    if ((rand() > (int) (RAND_MAX * (pctget/100.0))) && (size > 0)) {
      random_blocks[i] = rand()/(RAND_MAX/size--); // decrease free block
      block_memory[i] = 0; // free block
    } else {
      // request memory depending on whether it's "small" or "large" block
      if(rand() > (RAND_MAX*pctlarge)/100) {
	block_memory[i] = 1 + rand()/(RAND_MAX/(small_limit - 1));
      } else {
	block_memory[i] = 1 + rand()/(RAND_MAX/(large_limit - small_limit));
      }
      random_blocks[i] = 0;
      size++; // increase number of blocks available to be freed
      }
  }

  clock_t time = clock();
  clock_t time_total = 0;
  size = 0;
  for(i = 0; i < ntrials; i++) {
    if (block_memory[i] == 0) {
      freemem(list_access[random_blocks[i]]);
      list_access[random_blocks[i]] = list_access[--size];
    } else {
      list_access[size++] = getmem(block_memory[i]);      
    }

    // Print all the things
    if (i % (ntrials/10) == 0) {
      time = clock() - time;
      time_total = time_total + time;
      print_stats(time);
      time = clock();
    }
  }
  printf("Total time: %f\n", (float) time_total/CLOCKS_PER_SEC);
  return 0;
}

// prints prcessor time, memory size, number of freeblocks, and average
// bytes used by blocks
void print_stats(clock_t time) {
  uintptr_t total_size = 0;
  uintptr_t total_free = 0;
  uintptr_t n_free_blocks = 0;
  get_mem_stats(&total_size, &total_free, &n_free_blocks);
  printf("Processor Time: %f\t", (float) time/CLOCKS_PER_SEC);
  printf("Memory Size: %" PRIuPTR "\t", total_size);
  printf("Number of Freeblocks: %" PRIuPTR " \t", n_free_blocks);
  printf("Average bytes: %" PRIuPTR "\n", total_free/n_free_blocks);
}
