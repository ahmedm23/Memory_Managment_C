Ahmed Moalim


The files in this folder will be used to manage memory, in the end the programs should be able to free and reallocate memory.

Description of the Free List and its functions
   A Free list object is a linked list of memory blocks allocated by malloc, with its field being the size of the 
   block plus the size of the malloced memory. The method getmem(...) is used to grab a block from the list that 
   satisfied the request. If the list contains a block with a size either equal to or slightly greater then the 
   requested size the method will return that block other wise it will malloc more memory of split a block into to
   smaller ones. freemem(...) is used to return a block to the linked list, at the exact loaction the block was at 
   prevously.

   The bench program first randomizes whether it will free or request
   memory. If it requests memory then the amount requested is randomized.
   This is all stored such that the O(1) access can be achieved. The numbers
   are then looked at and then at freemem and getmem are called accordingly.
   
No additions were made beyond the specs of the HW.

The program is most efficient at both pctget values close to 0 and 100 with an opperating time slightly varying from 0.001,
and with a Free list of length no greater then 2, However at pctget values near 50 the program operating time increases and the amount of 
blocks at range in the list range from 10-47.

StackOverflow was crucial! It helped with some format and style for the bench program. The book "The Joy of C!" also played a critical role in understandingheaders, pointers, and memory management.
