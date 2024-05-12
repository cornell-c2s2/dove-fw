//========================================================================
// mem_array.h
//========================================================================
// Interface for allocating a memory array for storing char data

#ifndef MEM_ARRAY_H
#define MEM_ARRAY_H

//------------------------------------------------------------------------
// Allocating and freeing the memory array
//------------------------------------------------------------------------

int* mem_arr_alloc();
void mem_arr_free( int32_t* ptr );
void get_samples(int32_t* ptr, int num_samples, int kernel_length);

#endif // MEM_ARRAY_H

