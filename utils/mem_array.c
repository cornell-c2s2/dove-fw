//========================================================================
// mem_array.c
//========================================================================

#include "bird_1.h"
#include "bird_2.h"
#ifndef RISCV_BOARD
#include <stdlib.h>
#else
#include "SPI_Lib_C2S2.h"
#endif

int *mem_arr_alloc()
{

    // If we're on the board, use SRAM
#ifdef RISCV_BOARD
    return (int *)0x01000000;

    // Otherwise, use malloc
#else
    return (int *)malloc(2048);
#endif
}

// puts samples in ptr
void get_samples(int *ptr, int num_samples, int kernel_length)
{
#ifdef RISCV_BOARD
    // Get sample from bird files

    // bird_2 has noise
    for (int i = 0; i < num_samples; i++)
    {
        ptr[i] = samples[75000 + i];
    }

    // bird_1 has no noise
    for (int i = 0; i < kernel_length; i++)
    {
        ptr[num_samples + i] = samples2[100000 + i];
    }
#else
    // Get sample from bird files

    // bird_2 has noise
    for (int i = 0; i < num_samples; i++)
    {
        ptr[i] = samples2[75000 + i];
    }

    // bird_1 has no noise
    for (int i = 0; i < kernel_length; i++)
    {
        ptr[num_samples + i] = samples[100000 + i];
    }
#endif
}

void mem_arr_free(int *ptr)
{

    // If we're on the board, no need to do anything

    // Otherwise, use free
#ifndef RISCV_BOARD
    free(ptr);
#endif
}