#include "defs.h"
#include "csr.h"

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

// UART LIBRARY STUFF; should mention by default we pop in documentation
void UART_pop(){
  uart_ev_pending_write(0x2);
  return;
}

char UART_read(){
  while(uart_rxempty_read() == 1);
  UART_pop();
  return reg_uart_data;
}

void UART_write(char character){
  while(uart_txfull_read() == 1);
  reg_uart_data = character;
  // Mention delay in documentations
  delay(1000000);
}

char* UART_readline(){
  char* received_array = 0;
  char received_int;
  int count = 0;
  received_array[count++] = 0;
  while ((received_int = UART_read()) != '\n'){
    received_array[count++] = received_int;
    received_array[0]++;
    // UART_pop();
  }

  received_array[count++] = received_int;
  // UART_pop();
  return received_array;

}

void UART_sendline(char* yourmom, int8_t size){
  char* data[4] = {51,49,50};
  for(int i = 0; i < size; i++) {   
    UART_write(data[i]);
  }

  // send \n to tell particle we are done
  UART_write('\n');
}


void main()
{
  int i;
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

  // UART pins
  reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;       // UART Tx
  reg_mprj_io_5 = GPIO_MODE_MGMT_STD_INPUT_NOPULL; // UART Rx

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
  
  // Enable uart
  reg_uart_enable = 1;
  reg_mprj_datah = 0;
  reg_mprj_datal = 0;

  uint32_t* received = {51,49,50};
  while(1)
  {
    // // For transcieving 
    // for(i='A'; i<='Z'; i++)
    // {
    //   while(uart_txfull_read==1) /* do nothing */ ;
    //   uart_rxtx_write(i);
    //   delay(1000000);
    // } 

    // For recieving and sending back
    // received = UART_readline();
    /*
    int i = 0;
    uint32_t byte = received[i];
    while (byte != -1) {
      UART_write(byte);
      byte = received[++i];
    }
    */
    UART_sendline(received, 3);

    // delay(1000000);
    

  }

}