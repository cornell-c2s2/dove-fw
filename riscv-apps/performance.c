#include "defs.h"

// Define vector size, we limit it cause of RISCV memory
const int vectorSize = 512;

void delay(const int d)
{

    /* Configure timer for a single-shot countdown */
	reg_timer0_config = 0;
	reg_timer0_data = d;
    reg_timer0_config = 1;

    // Loop, waiting for value to reach zero
   reg_timer0_update = 1;  // latch current value
   while (reg_timer0_value > 0) {
           reg_timer0_update = 1;
   }

}

// void putchar(char c)
// {
// 	if (c == '\n')
// 		putchar('\r');
//     while (reg_uart_txfull == 1);
// 	reg_uart_data = c;
// }

// void print(const char *p)
// {
// 	while (*p)
// 		putchar(*(p++));
// }

#include <stdio.h>
#include <string.h>
#include <limits.h>

void addVectors(uint8_t a[], uint8_t b[]) {
    for (int i = 0; i < vectorSize; i++) {
        a[i] = a[i] + b[i];
    }
}


void int_to_binary(int n, char* binary_str, size_t size) {
    int num_bits = sizeof(int) * CHAR_BIT; // Total bits in an integer

    // Check if the provided buffer is large enough
    if (size < num_bits + 1) { // +1 for the null terminator
        if (size > 0) {
            binary_str[0] = '\0'; // Set to empty string if not enough space
        }
        return;
    }

    unsigned int mask = 1U << (num_bits - 1); // Mask to extract bits
    for (int i = 0; i < num_bits; i++) {
        binary_str[i] = (n & mask) ? '1' : '0';
        mask >>= 1;
    }
    binary_str[num_bits] = '\0'; // Null terminator
}

void main()
{
	int i, j, k;

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
    reg_mprj_io_9  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_8  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_7  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_6  = GPIO_MODE_MGMT_STD_OUTPUT;
//    reg_mprj_io_6  = 0x1fff;
    reg_mprj_io_5  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

    /* Lowest 5 GPIOs need to be set this way in order to	*/
    /* access the housekeeping SPI at run-time.  Do not change	*/
    /* them unless absolutely necessary.			*/

    reg_mprj_io_4  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_3  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_2  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_1  = GPIO_MODE_MGMT_STD_OUTPUT;

    // Initiate the serial transfer
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
//
//    /* GPIO 0 is turned off to prevent toggling the debug pin;	*/
//    /* For debug, make this an output and drive it externally	*/
//    /* to ground.						*/
//
//    reg_mprj_io_0  = GPIO_MODE_MGMT_STD_ANALOG;

//    gpio_program();
//    gpio_program_local();

//    reg_uart_enable = 1;

//    print("Hello World !!");
//    putchar('x');
    // Vector addition:
    
    // Create two example vectors as arrays of size 512
    uint8_t vecA[vectorSize];
    uint8_t vecB[vectorSize];
    
    for (int i = 0; i < vectorSize; i++) {
        vecA[i] = 1;
        vecB[i] = 2;
    }

    // int_to_binary(cycles_taken,32);

    reg_gpio_out = 0; // ON
    while(1) {
        reg_gpio_out = 0; // OFF
        reg_mprj_datal = 0xffffffff;
        delay(10000);
        addVectors(vecA,vecB);
        reg_mprj_datal = 0x00000000;
        reg_gpio_out = 1; // OFF
        reg_gpio_out = 1; // OFF
        for (int i = 0; i < vectorSize; i++) {
        vecA[i] = 1;
        vecB[i] = 2;
        }
    }
    // reg_mprj_datal = 0x00000000;
    //    }
    


    }
