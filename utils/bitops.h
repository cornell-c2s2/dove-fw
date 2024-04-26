//========================================================================
// bitops.h
//========================================================================
// Interface for various functions for interacting with bits of values

#ifndef BITOPS_H
#define BITOPS_H

//------------------------------------------------------------------------
// Reading
//------------------------------------------------------------------------

// Returns the nth bit of src (1 or 0) -> LSB is 0
// Ex. get_bit( 0x00001000, 12 ) -> 1
int get_bit( int src, int n );

//------------------------------------------------------------------------
// Writing
//------------------------------------------------------------------------

// Evaluates to src, but with the nth bit set high (1)
int set_bit( int src, int n );

// Evaluates to src, but with the nth bit reset low (0)
int reset_bit( int src, int n );

#endif // BITOPS_H