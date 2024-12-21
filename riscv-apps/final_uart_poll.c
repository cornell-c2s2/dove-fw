//========================================================================
// final_uart_poll.c
//========================================================================
// Send IMU data from Particle Board to RISC-V and send data back

#include "defs.h"
#include "csr.h"
#include "ring_buffer.h"
#include "arith.h"
#include "stdio.h"

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

// Struct associating character array and it's size
typedef struct {
  char* data;
  uint8_t size;
} chararray_t;

// UART LIBRARY STUFF

/**
 * Pop the first ASCII symbol of the UART received queue
 * 
 * UART_readChar() function would keeping reading the same symbol unless this function is called
 */
void UART_popChar()
{
  uart_ev_pending_write(0x2);
  return;
}

/**
 * While receiving ASCII symbol, return it
 * 
 * Return the first ASCII symbol of the UART received queue
 * 
 * RX mode must be enabled
 */
char UART_readChar()
{
  while(uart_rxempty_read() == 1);
  UART_popChar();
  return reg_uart_data;
}

/**
 * Send ASCII char through UART
 * 
 * TX mode must be enabled
 */
void UART_sendChar(char character)
{
  while(uart_txfull_read() == 1);
  reg_uart_data = character;
}

/**
 * Read full line msg and return it
 */
chararray_t UART_readLine(char* received_array)
{
  char received_char;
  int count = 0;
  while ((received_char = UART_readChar()) != '\n') {
    received_array[count++] = received_char;
  }

  chararray_t received = {received_array, count};
  return received;
}

/**
 * Send a full line message through UART
 */
void UART_sendLine(chararray_t chararray)
{
  for(int i = 0; i < chararray.size; i++) { 
    UART_sendChar(chararray.data[i]);
  }

  // send \n to tell particle we are done
  UART_sendChar('\n');
}

/**
 * Convert a character array to an integer
 */
void chararray_to_int(chararray_t array, uart_int* uart_num)
{
  int16_t acc = 0;
  
  bool neg = (array.data[0] == '-');

  // start at 1st index if negative else 0th
  int count = neg ? 1 : 0;

  for (int i = count; i < array.size; i++) {
    // mul old values by 10 to get new vals
    acc = mul(acc,10);
    acc += array.data[i] - '0';
  }

  if (neg) {
    acc = -acc;
  }

  // edit reference
  uart_num->num = acc;
  uart_num->size = array.size;
}

/**
 * Convert an integer to a character array
 */
void int_to_chararray(uart_int* uart_num, chararray_t* ret, char* arr) 
{
  int num = uart_num->num; // Preserve original value
  bool neg = num < 0;

  // Handle sign
  int index = 0;
  if (neg) {
    arr[index++] = '-';
    num = -num; // Work with absolute value for conversion
  }

  // Extract digits into a temporary buffer (reverse order)
  int temp[10]; // Maximum 10 digits for a 32-bit integer
  int digit_count = 0;
  do {
    temp[digit_count++] = rem(num, 10);
    num = div(num, 10);
  } while (num > 0);

  // Build the result string
  for (int i = 0; i < digit_count; i++) {
    arr[index++] = temp[digit_count - i - 1] + '0';
  }

  // Set final size and data
  ret->data = arr;
  ret->size = index;
}

// void send_ring_buffer(RingBuffer ring_buffer){
//   int count = 0;
//   // char line = {'D','u','m','p','i','n','g', ' ', 'b','u','f','f','e','r'};
//   // chararray_t msg = {line, 14};
//   // UART_sendLine(msg);
//   while (count < ring_buffer.buffer_size){
//     uart_int uart_num = ring_buffer_get(&ring_buffer);

//     // Nothing left
//     if (uart_num.size == 0) {
//       break;
//     }

//     char* int_length[uart_num.size];
//     chararray_t processed_recieved = int_to_chararray(&uart_num, int_length);
//     UART_sendLine(processed_recieved);
//     count += 1;
//   }
// }

void main()
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
  
  // Initialize ring buffer
  RingBuffer ring_buffer = create_ring(156);
  
  while(1)
  {
      // BASIC TEST:
      // char test[6];
      // UART_sendLine(UART_readLine(test));

      // INT TO CHAR TEST:
      // uart_int uart_num = {9254, 4};
      // char mem[6];
      // chararray_t arr;
      // int_to_chararray(&uart_num, &arr, mem);
      // UART_sendLine(arr);

      // CHAR TO INT TEST:
      // char memory[] = {'-','6','9','1'};
      // chararray_t value = {memory, 4};
      // uart_int uart_num;
      // chararray_to_int(value, &uart_num);
      // char mem2[uart_num.size];
      // chararray_t arr;
      // int_to_chararray(&uart_num,&arr, mem2);
      // UART_sendLine(arr);

      // Ring Buffer Test:
      char memory[] = {'-','6','9','1'};
      chararray_t value = {memory, 4};
      uart_int uart_num;

      // num 2
      char memory2[] = {'1','0','9','1','5'};
      chararray_t value2 = {memory2, 5};
      uart_int uart_num2;

      // Convert and put into buffer
      chararray_to_int(value, &uart_num);
      chararray_to_int(value2, &uart_num2);
      ring_buffer_put(&ring_buffer, uart_num);
      ring_buffer_put(&ring_buffer, uart_num2);

      // Immediately take out:
      uart_num = ring_buffer_get(&ring_buffer);
      char mem[uart_num.size];
      chararray_t arr;
      int_to_chararray(&uart_num,&arr, mem);
      UART_sendLine(arr);

      // Take out second num
      uart_num2 = ring_buffer_get(&ring_buffer);
      char mem2[uart_num2.size];
      chararray_t arr2;
      int_to_chararray(&uart_num2,&arr2, mem2);
      UART_sendLine(arr2);

      // Put num in ring buffer
      // char arr[6];
      // chararray_t received = UART_readLine(arr); // Read input as a chararray

      // // Convert to uart_int
      // uart_int uart_num;
      // chararray_to_int(received, &uart_num);

      // // Allocate a sufficiently large buffer for the output
      // char converted[6]; // Buffer size should accommodate potential sign and digits
      // chararray_t result;

      // // Convert back to chararray
      // int_to_chararray(&uart_num, &result, converted);

      // // Send the resulting chararray
      // UART_sendLine(result);


      // ring_buffer_put(&ring_buffer,uart_num);

      // // get same num from ring buffer
      // uart_int uart_num2 = ring_buffer_get(&ring_buffer);
      // char size2[uart_num2.size];

      // chararray_t buffer_recieved;

      // int_to_chararray(&uart_num2, &buffer_recieved, arr);
      // if (uart_num.num == uart_num2.num & uart_num.size == uart_num2.size){
      //   UART_sendLine(buffer_recieved);
      // }
  }

}