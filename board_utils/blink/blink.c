#include "../board_utils/defs.h"
#include "../include/src.h"
#include "../../include/fake.h"
#include "../../include/bird_2.h"
#include "../../include/bird_1.h"

#ifndef RISCV_BOARD
    #include <stdio.h>
    #include <stdlib.h>
#endif
int num_samples = 10;
int kernel_length = 10; 
// #include "../local_defs.h"
// #include "../stub.c"

// #include "../config_io.h"
// #include "../defs_mpw-two-mfix.h"

// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

// void gpio_program();
// void gpio_program_local() {
//
//     reg_mprj_io_37 = 0x1801;
//     reg_mprj_io_36 = 0x0c00;
//     reg_mprj_io_35 = 0x0600;
//     reg_mprj_io_34 = 0x0300;
//     reg_mprj_io_33 = 0x0180;
//     reg_mprj_io_32 = 0x01c0;
//     reg_mprj_io_31 = 0x00c0;
//     reg_mprj_io_30 = 0x0060;
//     reg_mprj_io_29 = 0x0030;
//     reg_mprj_io_28 = 0x0018;
//     reg_mprj_io_27 = 0x000c;
//     reg_mprj_io_26 = 0x0006;
//     reg_mprj_io_25 = 0x1003;
//     reg_mprj_io_24 = 0x1801;
//     reg_mprj_io_23 = 0x0c00;
//     reg_mprj_io_22 = 0x0600;
//     reg_mprj_io_21 = 0x0300;
//     reg_mprj_io_20 = 0x0180;
//     reg_mprj_io_19 = 0x0000;
//     reg_mprj_io_18 = 0x0007;
//     reg_mprj_io_17 = 0x1fbf;
//     reg_mprj_io_16 = 0x1f7f;
//     reg_mprj_io_15 = 0x1eff;
//     reg_mprj_io_14 = 0x1dff;
//     reg_mprj_io_13 = 0x1bff;
//     reg_mprj_io_12 = 0x17ff;
//     reg_mprj_io_11 = 0x0fff;
//     reg_mprj_io_10 = 0x1ffc;
//     reg_mprj_io_9  = 0x1ff8;
//     reg_mprj_io_8  = 0x1ff1;
//     reg_mprj_io_7  = 0x1fe1;
//     reg_mprj_io_6  = 0x1fe0;
//     reg_mprj_io_5  = 0x1f81;
//     reg_mprj_io_4  = 0x1f01;
//     reg_mprj_io_3  = 0x1e01;
//     reg_mprj_io_2  = 0x1c01;
//     reg_mprj_io_1  = 0x1c00;>
//     reg_mprj_io_0  = 0x100b;
//
//     // Initiate the serial transfer
//     reg_mprj_xfer = 1;
//     while (reg_mprj_xfer == 1);
//
//     reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
//     reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
//     reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
//     reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
//     reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
//     reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
//     reg_mprj_io_31 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_30 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_29 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_28 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_27 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_26 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_25 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_24 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_23 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_22 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_21 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_20 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_19 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_18 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_17 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_16 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_15 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_14 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_13 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;>
//     reg_mprj_io_12 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_11 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_10 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_7  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_6  = GPIO_MODE_MGMT_STD_OUTPUT;
//     reg_mprj_io_5  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//
//     reg_mprj_io_4  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_3  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_2  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
//     reg_mprj_io_1  = GPIO_MODE_MGMT_STD_OUTPUT;
//
//     reg_mprj_io_0  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
////    reg_mprj_io_0  = GPIO_MODE_MGMT_STD_ANALOG;
//
//
//}

void delay(const int d)
{

    /* Configure timer for a single-shot countdown */
    reg_timer0_config = 0;
    reg_timer0_data = d;
    reg_timer0_config = 1;

    // Loop, waiting for value to reach zero
    reg_timer0_update = 1; // latch current value
    while (reg_timer0_value > 0)
    {
        reg_timer0_update = 1;
    }
}

// void putchar(char c)
// {
//     if (c == '\n')
//         putchar('\r');
//     while (reg_uart_txfull == 1)
//         ;
//     reg_uart_data = c;
// }

// void print(const char *p)
// {
//     while (*p)
//         putchar(*(p++));
// }

// For now literally copy and paste from the include file, TODO: fix makefile to include these
int get_bit( int src, int n ) {
    return ( src >> n ) & 0x1;
}

//------------------------------------------------------------------------
// Writing
//------------------------------------------------------------------------

int set_bit( int src, int n ) {
    return src | ( 0x1 << n );
}

int reset_bit( int src, int n ) {
    return src & ~( 0x1 << n );
}


int mul( int src1, int src2 ) {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Invert operands to make positive, if necessary
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( ( src1 < 0 ) & ( src2 < 0 ) ) {
        src1 = -src1;
        src2 = -src2;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Iterate over smaller positive operand (opb) for efficiency
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int opa;
    int opb;

    if( src1 < 0 ) {
        opa = src1;
        opb = src2;
    } else if( src2 < 0 ) {
        opa = src2;
        opb = src1;
    } else if( src1 < src2 ) {
        opa = src2;
        opb = src1;
    } else {
        opa = src1;
        opb = src2;
    }

    int acc = 0;

    while( opb > 0 ){
        if( get_bit( opb, 0 ) ) {
            acc += opa;
        }

        opa = ( opa << 1 );
        opb = ( opb >> 1 );
    }

    return acc;
}
void matched_filter(char *input_signal, int signal_length, char *filter_kernel, int kernel_length, char *filtered_signal)
{
  // Allocate memory for the filtered signal
  // N + M - 1
  int filtered_length = signal_length + kernel_length - 1;

  for (int i = 0; i < filtered_length; ++i)
  {
    filtered_signal[i] = 0.0;

    for (int j = 0; j < kernel_length; ++j)
    {
      if (i >= j && i - j < signal_length)
      {
        filtered_signal[i] += mul (input_signal[i - j], filter_kernel[kernel_length - 1 - j]);
      }
    }
  }
}

void blink(bool on)
{
    if (on) {
    reg_gpio_out = 0; // ON
    reg_mprj_datah = 0x0000003f;
    reg_mprj_datal = 0xffffffff;

    delay(8000000);
    } else {

    reg_gpio_out = 1; // OFF
    reg_mprj_datal = 0x00000000;
    reg_mprj_datah = 0x00000000;

    delay(8000000);
    }
}


// puts samples in ptr
void get_samples(char* ptr, int num_samples, int kernel_length) {
    #ifdef RISCV_BOARD
        // Use Kene's function
        // get_data(ptr,num_samples)
    #else 
        //Get sample from bird files

        // bird_2 has noise
        for (int i = 0; i < num_samples; i++){
            ptr[i] = samples[75000 + i];
        }

        // bird_1 has no noise
        for (int i = 0; i < kernel_length; i++){
            ptr[num_samples + i] = samples2[100000 + i];
        }
    #endif 
}

void new_matched_filter(char *filtered_signal,int signal_length, int kernel_length)
{
  // Get length of the output signal: N + M - 1
  int filtered_length = signal_length + kernel_length - 1;

  // Starting index for putting matched filter results
  int start = signal_length + kernel_length;

  for (int i = 0; i < filtered_length; ++i)
  {
    for (int j = 0; j < kernel_length; ++j)
    {
      if (i >= j && i - j < signal_length)
      {
        filtered_signal[start + i] += mul (filtered_signal[i - j], filtered_signal[signal_length + (kernel_length - 1 - j)]);
      }
    }
  }
}

char* mem_arr_alloc() {

    // If we're on the board, use SRAM
#ifdef RISCV_BOARD
    return ( char* ) 0x01000000;

    // Otherwise, use malloc
#else
    return ( char* ) malloc( 2048 );
#endif
}

 
int main()
{
    // Allocate memory, about 2kb
    // Entries 0 to num_samples - 1 contain data with noise (AKA actual data)
    // Entries num_samples to kernel_length - 1 contain the template signal to match with
    // Entries kernel_length to num_samples + kernel_length - 2 contain the result of the matched filter
    // It is the duty of the caller to make sure there is enough space in the ptr. 
    char *ptr = mem_arr_alloc();


    //put samples in ptr
    get_samples(pointer, num_samples, kernel_length); 

    //Note: unsigned chars goes from 0 to 255, signed goes from -127 to 127
    // We will used signed chars to get real data from bird_1.h and bird_2.h

    // Use matched filter
    new_matched_filter(pointer,num_samples,kernel_length);
    // matched_filter(fake_samples, fake_size, kernel_samples, kernel_size, filtered);

    char filtered_size = num_samples + kernel_length - 1;
    // Starting index for putting matched filter results
    int start = num_samples + kernel_length;


    // int i, j, k;
    #ifdef RISCV_BOARD
        reg_gpio_mode1 = 1;
        reg_gpio_mode0 = 0;
        reg_gpio_ien = 1;
        reg_gpio_oe = 1;

        reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
        reg_mprj_io_31 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_30 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_29 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_28 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_27 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_26 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_25 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_24 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_23 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_22 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_21 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_20 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_19 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_18 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_17 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_16 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_15 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_14 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_13 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_12 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_11 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_10 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_9 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_8 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_7 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
        //    reg_mprj_io_6  = 0x1fff;
        reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

        /* Lowest 5 GPIOs need to be set this way in order to	*/
        /* access the housekeeping SPI at run-time.  Do not change	*/
        /* them unless absolutely necessary.			*/

        reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
        reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;

        // Initiate the serial transfer
        reg_mprj_xfer = 1;
        while (reg_mprj_xfer == 1)
            ;
        //
        //    /* GPIO 0 is turned off to prevent toggling the debug pin;	*/
        //    /* For debug, make this an output and drive it externally	*/
        //    /* to ground.						*/
        //__muls
        //    reg_mprj_io_0  = GPIO_MODE_MGMT_STD_ANALOG;

        //    gpio_program();
        //    gpio_program_local();

        //    reg_uart_enable = 1;

        //    print("Hello World !!");
        //    putchar('x');

        // Main code
        // while (1)
        // {

        // reg_gpio_out = 1; // OFF
        // reg_mprj_datal = 0x00000080;
        // reg_mprj_datah = 0x00000000;

        // delay(5000000);

        // reg_gpio_out = 0; // ON
        // reg_mprj_datah = 0x0000003f;
        // reg_mprj_datal = 0xffffff7f;

        // delay(5000000);
        // }

        // If on board blink
        for (int i = 0; i < filtered_size; i++)
        {
        
            blink(pointer[start + i] != 0);
            
            delay(8000000);
        }
        return 0;
    #else  
        // If not on board we print values!
        for (int i = 0; i < filtered_size; i++)
        {
            int num = pointer[start + i];
            if (num != 0) {
                printf("The value at entry %d is %d\n", start+i,num);
            }
        }
        return 0;
    #endif
}
