#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include "defs.h"
#include "csr.h"
#include "arith.h"

// TODO DOCUMENT (ARNAV)
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

RingBuffer create_ring(uint8_t size);

void ring_buffer_put(RingBuffer* buffer, uart_int c);

uart_int ring_buffer_get(RingBuffer* buffer);

#endif // RING_BUFFER_H    