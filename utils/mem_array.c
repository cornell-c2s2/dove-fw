//========================================================================
// mem_array.c
//========================================================================

#include "bird_1.h"
#include "bird_2.h"
#ifndef RISCV_BOARD
#include <stdlib.h>
#else
#include "SPI_Lib_C2S2.h"
#include "defs.h"
#endif

#ifdef RISCV_BOARD
int mem_arr[170];
#endif

int32_t *mem_arr_alloc()
{

    // If we're on the board, use pre-allocated array
#ifdef RISCV_BOARD
    // return &(reg_rw_block1);
    return mem_arr;

    // Otherwise, use malloc
#else
    return (int32_t *)malloc(2048);
#endif
}

// puts samples in ptr
void get_samples(int32_t *ptr, int num_samples, int kernel_length)
{
    // Get sample from bird files

    // bird_2 has noise
    for (int i = 0; i < num_samples; i++)
    {
        ptr[i] = samples2[i];
    }

    // bird_1 has no noise
    for (int i = 0; i < kernel_length; i++)
    {
        ptr[num_samples + i] = samples[i];
    }
}

void mem_arr_free(int32_t *ptr)
{

    // If we're on the board, no need to do anything

    // Otherwise, use free
#ifndef RISCV_BOARD
    free(ptr);
#endif
}