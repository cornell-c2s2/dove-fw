//========================================================================
// mem_array.c
//========================================================================

#ifndef RISCV_BOARD
#include <stdlib.h>
#endif

char* mem_arr_alloc() {

    // If we're on the board, use SRAM
#ifdef RISCV_BOARD
    return ( char* ) 0x01000000;

    // Otherwise, use malloc
#else
    return ( char* ) malloc( 2048 );
#endif
}

void  mem_arr_free( char* ptr ) {

    // If we're on the board, no need to do anything

    // Otherwise, use free
#ifndef RISCV_BOARD
    free( ptr );
#endif
}