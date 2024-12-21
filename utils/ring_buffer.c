#include <stdint.h>
#include "defs.h"
#include "csr.h"
#include "arith.h"

typedef struct {
  int16_t num;
  int8_t size; 
} uart_int;


typedef struct {
  uart_int* ring_buffer;
  uint8_t head;
  uint8_t tail;
  uint8_t buffer_size;
} RingBuffer;

RingBuffer create_ring(uint8_t size) {
  uart_int ring_buffer[size];
  uint8_t head = 0; // Index for writing new data
  uint8_t tail = 0; // Index for reading stored data
  uint8_t buffer_size = size;

  RingBuffer buffer = {ring_buffer,head,tail, buffer_size};
  return buffer;
}


// Add a byte to the ring buffer
void ring_buffer_put(RingBuffer* buffer, uart_int c) {
  uint8_t next_head = rem((buffer->head + 1), buffer->buffer_size);
  // If buffer is full, overwrite the oldest data
  if (next_head == buffer->tail) {
    buffer->tail = rem((buffer->tail + 1), buffer->buffer_size);
  }
  buffer->ring_buffer[buffer->head] = c;
  buffer->head = next_head;
}

// Get a byte from the ring buffer (if available)
uart_int ring_buffer_get(RingBuffer* buffer) {
  if (buffer->head == buffer->tail) {
    // Buffer is empty
    uart_int invalid = {0, 0};
    return invalid;
  }
  uart_int c = buffer->ring_buffer[buffer->tail];
  buffer->tail = rem((buffer->tail + 1), buffer->buffer_size);
  return c;
}