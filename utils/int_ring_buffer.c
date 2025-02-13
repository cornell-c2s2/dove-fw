#include <stdint.h>
#include "defs.h"
#include "csr.h"
#include "arith.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int16_t *ring_buffer;
  uint8_t head;
  uint8_t tail;
  uint8_t buffer_size;
} IntRingBuffer;

IntRingBuffer create_int_ring(uint8_t size)
{
  int16_t ring_buffer[size];
  uint8_t head = 0;
  uint8_t tail = 0;

  IntRingBuffer buffer = {ring_buffer, head, tail, size};
  return buffer;
}

// add a 16-bit int to the ring buffer
void ring_buffer_put(IntRingBuffer *buffer, int16_t value)
{
  uint8_t next_head = rem((buffer->head + 1), buffer->buffer_size);

  // If buffer is full, overwrite oldest data
  if (next_head == buffer->tail)
  {
    buffer->tail = rem((buffer->tail + 1), buffer->buffer_size);
  }

  buffer->ring_buffer[buffer->head] = value;
  buffer->head = next_head;
}

// Get a 16-bit value from the ring buffer (throws an error if not available)
int16_t ring_buffer_get(IntRingBuffer *buffer)
{
  if (buffer->head == buffer->tail)
  {
    fprintf(stderr, "Cannot read from empty ring buffer.\n");
    exit(EXIT_FAILURE);
  }
  int16_t value = buffer->ring_buffer[buffer->tail];
  buffer->tail = rem((buffer->tail + 1), buffer->buffer_size);
  return value;
}
