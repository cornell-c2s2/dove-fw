//========================================================================
// arith.h
//========================================================================
// Interface for basic arithmetic functions

#ifndef ARITH_H
#define ARITH_H

//------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------
// O( log( min( src1, src2 ) ) )

int          mul ( int          src1, int          src2 );
unsigned int mulu( unsigned int src1, unsigned int src2 );

//------------------------------------------------------------------------
// Division
//------------------------------------------------------------------------
// We perform floor division; any fractional result is rounded down. If
// the denominator is 0, returns 0.
//
// O( log( max( src1, src2 ) ) )

int          div ( int          numerator, int          denominator );
unsigned int divu( unsigned int numerator, unsigned int denominator );

//------------------------------------------------------------------------
// Remainder
//------------------------------------------------------------------------
// The remainder of floor division. If the denominator is 0, returns the
// numerator
//
// O( log( max( src1, src2 ) ) )

int          rem ( int          numerator, int          denominator );
unsigned int remu( unsigned int numerator, unsigned int denominator );

#endif // ARITH_H
