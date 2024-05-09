#include "defs.h"
#include "csr.h"

void write_spi(char c)
{
    reg_spimaster_wdata = (unsigned long) c;
//    reg_spimaster_wdata = c;
//    spi_master_control_length_write = 8 bits; 15:8
//    spi_master_control_start_write = 1; 0:0
//    reg_spimaster_control = 0x0800;
    reg_spimaster_control = 0x0801;
}

char read_spi()
{
//    reg_spimaster_wdata = 0;
//    spi_master_control_length_write(8 bits);
//    spi_master_control_start_write(1);
//    reg_spimaster_control = 0x0800;
//    spi_write(0x00);
//    reg_spimaster_rdata = 0x00;
//    reg_spimaster_control = 0x0801;
    write_spi(0x00);
    while (reg_spimaster_status != 1);
    return reg_spimaster_rdata;
}





void array_read_spi(char* ptr, int size){ // size is num of samples to be collected
    //int data[size];
        for (int i = 0; i < size; i++) {
        ptr[i] = read_spi(); 
    } 
}



void run_spi(char* ptr, int size)
{
    int i;
    uint32_t value;

    reg_mprj_datal = 0;

    // For SPI operation, GPIO 1 should be an input, and GPIOs 2 to 4
    // should be outputs.

    reg_mprj_io_34  = GPIO_MODE_MGMT_STD_INPUT_NOPULL;	// SDI
    reg_mprj_io_35  = GPIO_MODE_MGMT_STD_BIDIRECTIONAL;	// SDO
    reg_mprj_io_33  = GPIO_MODE_MGMT_STD_OUTPUT;	// CSB
    reg_mprj_io_32  = GPIO_MODE_MGMT_STD_OUTPUT;	// SCK

    // Configure upper 16 bits of user GPIO for generating testbench
    // checkpoints.

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

    // Configure next 8 bits for writing the SPI value read on GPIO
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_9  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_8  = GPIO_MODE_MGMT_STD_OUTPUT;


    /* Apply configuration */
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);


    reg_mprj_datal = 0;
    reg_spi_enable = 1;


    // For SPI operation, GPIO 1 should be an input, and GPIOs 2 to 4
    // should be outputs.

    // Start test
    reg_mprj_datal = 0xA0400000;

    // Enable SPI master
    // SPI master configuration bits:
    // bits 7-0:	Clock prescaler value (default 2)
    // bit  8:		MSB/LSB first (0 = MSB first, 1 = LSB first)
    // bit  9:		CSB sense (0 = inverted, 1 = noninverted)
    // bit 10:		SCK sense (0 = noninverted, 1 = inverted)
    // bit 11:		mode (0 = read/write opposite edges, 1 = same edges)
    // bit 12:		stream (1 = CSB ends transmission)
    // bit 13:		enable (1 = enabled)
    // bit 14:		IRQ enable (1 = enabled)
    // bit 15:		(unused)


    reg_spimaster_cs = 0x1001;  // sel=0, manual CS

    void array_read_spi(char* ptr, int size); //Array Read, insert your own pointer and pointer size

    reg_spimaster_cs = 0x0000;  // release CS
    reg_spimaster_cs = 0x10001;  // sel=0, manual CS

    // End test
    reg_mprj_datal = 0xA0900000;
}