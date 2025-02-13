#ifndef INT_RING_BUFFER_H
#define INT_RING_BUFFER_H

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

IntRingBuffer create_int_ring(uint8_t size);

void ring_buffer_put(IntRingBuffer *buffer, int16_t value);

int16_t ring_buffer_get(IntRingBuffer *buffer);

#endif // RING_BUFFER_H