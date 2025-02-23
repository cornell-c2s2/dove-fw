//========================================================================
// blink.c
//========================================================================
// Basic blinking code to test our build system

#include "defs.h"
#define output_0_rdy       (*(volatile uint32_t*)0x30000000) // input xbar
#define output_0           (*(volatile uint32_t*)0x30000004)
#define output_1_rdy       (*(volatile uint32_t*)0x30000008) // classifier xbar
#define output_1           (*(volatile uint32_t*)0x3000000c)
#define output_2_rdy       (*(volatile uint32_t*)0x30000010) // output xbar
#define output_2           (*(volatile uint32_t*)0x30000014)

#define input_0_val      (*(volatile uint32_t*)0x30000018) // input xbar
#define input_0          (*(volatile uint32_t*)0x3000001c)
#define input_1_val      (*(volatile uint32_t*)0x30000020) // classifier xbar
#define input_1          (*(volatile uint32_t*)0x30000024)
#define input_2_val      (*(volatile uint32_t*)0x30000028) // output xbar
#define input_2          (*(volatile uint32_t*)0x3000002c)

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

void wb_test_loopback_inXbar_clsXbar(){
    while (input_0_val != 1) {
        // wait
        blink(1);
    }
    int input = input_0;
    blink(0);
    blink(1);
    blink(0);
    while (output_1_rdy != 1) {
        //wait
        blink(1);
    }
    output_1 = input;
}

void wb_test_loopback_inXbar_outXbar(){
    while (input_0_val != 1) {
        // wait
    }
    int input = input_0;
    while (output_2_rdy != 1) {
        //wait
    }
    output_2 = input;
}

void wb_test_loopback_clsXbar_inXbar(){
    while (input_1_val != 1) {
        // wait
    }
    int input = input_1;
    while (output_0_rdy != 1) {
        //wait
    }
    output_0 = input;
}

void wb_test_loopback_clsXbar_outXbar(){
    while (input_1_val != 1) {
        // wait
    }
    int input = input_1;
    while (output_2_rdy != 1) {
        //wait
    }
    output_2 = input;
}

void wb_test_loopback_outXbar_inXbar(){
    while (input_2_val != 2) {
        // wait
    }
    int input = input_2;
    while (output_0_rdy != 1) {
        //wait
    }
    output_0 = input;
}

void wb_test_loopback_outXbar_clsXbar(){
    while (input_2_val != 1) {
        // wait
    }
    int input = input_2;
    while (output_1_rdy != 1) {
        //wait
    }
    output_1 = input;
}

int main()
{
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
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_9 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_8 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_7 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;

    /* Lowest 5 GPIOs need to be set this way in order to	*/
    /* access the housekeeping SPI at run-time.  Do not change	*/
    /* them unless absolutely necessary.			*/

    reg_mprj_io_4 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_3 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_2 = GPIO_MODE_MGMT_STD_INPUT_NOPULL;
    reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;

    // Initiate the serial transfer
    reg_wb_enable = 1;

    // Select one of the below functions to call when doing wb physical testing
    wb_test_loopback_inXbar_clsXbar();
    // wb_test_loopback_inXbar_outXbar();
    // wb_test_loopback_clsXbar_inXbar();
    // wb_test_loopback_clsXbar_outXbar();
    // wb_test_loopback_outXbar_inXbar();
    // wb_test_loopback_outXbar_clsXbar();

}