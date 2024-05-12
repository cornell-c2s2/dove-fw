//========================================================================
// filter-blink.c
//========================================================================
// Blinking code to visualize the matched filter

#include "defs.h"
#include "src.h"
#include "mem_array.h"
#include "csr.h"

#ifdef RISCV_BOARD
#include "SPI_Lib_C2S2.h"
#include "gpio.h"
#else // Can print
#include "stdio.h"
#include "stdlib.h"
#endif

// Define number of samples wanted for data and kernel
int num_samples = 50;
int kernel_length = 30;

int main()
{
    // Allocate memory, about 2kb
    // Entries 0 to num_samples - 1 contain data with noise (AKA actual data)
    // Entries num_samples to kernel_length - 1 contain the template signal to match with
    // Entries kernel_length to num_samples + kernel_length - 1 contain the result of the matched filter
    // It is the duty of the caller to make sure there is enough space in the ptr.
    int32_t *ptr = mem_arr_alloc();

    // put samples in ptr
    get_samples(ptr, num_samples, kernel_length);

    // Note: unsigned chars goes from 0 to 255, signed goes from -127 to 127
    //  We will used signed chars to get real data from bird_1.h and bird_2.h


    int filtered_size = num_samples + kernel_length - 1;
    // Starting index for putting matched filter results
    int start = num_samples + kernel_length;
    // If the value passes the threshold then we say a Scrubjay is detected
    int32_t threshold = 0;

#ifdef RISCV_BOARD
    // Configure GPIO's

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
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_9 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_8 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_7 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_OUTPUT;

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
        {};
    
    // If on the board, indicate calculations have started
    reg_gpio_out = 0; // ON

    // Set all GPIO's to low
    for( int i = 0; i < 20; i++ ){
        gpio_low( i + 6 );
    }
#endif

    // Run the filter
    new_matched_filter(ptr, num_samples, kernel_length);

#ifdef RISCV_BOARD
    reg_mprj_datal = 0;
    int base_index = 0;
    for (int i = 0; i < 20; i++)
    {
        // Keep track of whether we've exceeded the threshold
        int over_threshold = 0;

        for (int j = 0; j < 5; j++){
            if( start + (base_index + j) > 170 ){}
            else if(ptr[start + (base_index + j)] > threshold){
                over_threshold = 1;
            }
        }
        gpio_set( i + 6, over_threshold );
        base_index += 5;
    }

    // Indicate that calculations are finished
    reg_gpio_out = 1; // OFF
#else
    // If not on board we print values!
    int base_index = 0;
    for (int i = 0; i < 20; i++)
    {
        // Keep track of whether we've exceeded the threshold
        int over_threshold = 0;

        for (int j = 0; j < 5; j++){
            if( start + (base_index + j) > 170 ){}
            else if(ptr[start + (base_index + j)] > threshold){
                over_threshold = 1;
            }
        }
        printf( "GPIO %d would be %d\n", (i + 6), over_threshold );
        base_index += 5;
    }
#endif
    // no dangling pointers
    mem_arr_free(ptr);
    return 0;
}