//========================================================================
// arith.h
//========================================================================
// Interface for basic arithmetic functions

#ifndef ARITH_H
#define ARITH_H

#include <stdint.h>

//------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------
// O( log( min( src1, src2 ) ) )

int32_t  mul ( int32_t  src1, int32_t  src2 );
uint32_t mulu( uint32_t src1, uint32_t src2 );

//------------------------------------------------------------------------
// Division
//------------------------------------------------------------------------
// We perform floor division; any fractional result is rounded down. If
// the denominator is 0, returns 0.
//
// O( log( max( src1, src2 ) ) )

int32_t  div ( int32_t  numerator, int32_t  denominator );
uint32_t divu( uint32_t numerator, uint32_t denominator );

//------------------------------------------------------------------------
// Remainder
//------------------------------------------------------------------------
// The remainder of floor division. If the denominator is 0, returns the
// numerator
//
// O( log( max( src1, src2 ) ) )

int32_t  rem ( int32_t  numerator, int32_t  denominator );
uint32_t remu( uint32_t numerator, uint32_t denominator );

int16_t rem_16( int16_t numerator, int16_t denominator );

#endif // ARITH_H
