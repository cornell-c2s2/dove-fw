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
#else // Can print
#include "stdio.h"
#include "stdlib.h"
#endif
// define number of samples wanted for data and kernel
int num_samples = 120;
int kernel_length = 30;

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

void blink(int on)
{
    if (on)
    {
        reg_gpio_out = 0; // ON
        reg_mprj_datah = 0x0000003f;
        reg_mprj_datal = 0xffffffff;

        delay(8000000);
    }
    else
    {

        reg_gpio_out = 1; // OFF
        reg_mprj_datal = 0x00000000;
        reg_mprj_datah = 0x00000000;

        delay(8000000);
    }
}

int main()
{
    // Allocate memory, about 2kb
    // Entries 0 to num_samples - 1 contain data with noise (AKA actual data)
    // Entries num_samples to kernel_length - 1 contain the template signal to match with
    // Entries kernel_length to num_samples + kernel_length - 1 contain the result of the matched filter
    // It is the duty of the caller to make sure there is enough space in the ptr.
    int *ptr = mem_arr_alloc();

    // put samples in ptr
    get_samples(ptr, num_samples, kernel_length);

    // Note: unsigned chars goes from 0 to 255, signed goes from -127 to 127
    //  We will used signed chars to get real data from bird_1.h and bird_2.h


    int filtered_size = num_samples + kernel_length - 1;
    // Starting index for putting matched filter results
    int start = num_samples + kernel_length;
    // If the value passes the threshold then we say a Scrubjay is detected
    int threshold = 0;

   
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
    
    //    reg_mprj_io_6  = 0x1fff;
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
    
    // If on board blink
    int index = 0;

    reg_gpio_out = 0; // ON
    reg_mprj_datah = 0x0000003f;
    // Use matched filter
    new_matched_filter(ptr, num_samples, kernel_length);
    reg_gpio_out = 1; // OFF
    reg_mprj_datah = 0x00000000;
    for (int i = 0; i < 20; i++)
    {
        if (i > 0){
            index = index + 12;
        }
        for (int j = 0; j < 12; j++){
            blink(ptr[start + (index+j)] > threshold);

            delay(8000000);
        }
    }
#else
        // Use matched filter
    new_matched_filter(ptr, num_samples, kernel_length);
    // If not on board we print values!
    for (int i = 0; i < filtered_size; i++)
    {

        int num = ptr[start + i];
        if (num > threshold)
        {
            // Only print entries that pass threshold
            printf("entry at %d has a value is %d\n", (start + i), num);
        }
    }
#endif
    // no dangling pointers
    mem_arr_free(ptr);
    return 0;
}