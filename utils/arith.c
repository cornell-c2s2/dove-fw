//========================================================================
// arith.c
//========================================================================
// Implementation of basic arithmetic functions

#include "arith.h"
#include "bitops.h"
#include <stdint.h>

//------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------

int32_t mul( int32_t src1, int32_t src2 ) {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Invert operands to make positive, if necessary
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    if( ( src1 < 0 ) & ( src2 < 0 ) ) {
        src1 = -src1;
        src2 = -src2;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Iterate over smaller positive operand (opb) for efficiency
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int32_t opa;
    int32_t opb;

    if( src1 < 0 ) {
        opa = src1;
        opb = src2;
    } else if( src2 < 0 ) {
        opa = src2;
        opb = src1;
    } else if( src1 < src2 ) {
        opa = src2;
        opb = src1;
    } else {
        opa = src1;
        opb = src2;
    }

    int32_t acc = 0;

    while( opb > 0 ){
        if( get_bit( opb, 0 ) ) {
            acc += opa;
        }

        opa = ( opa << 1 );
        opb = ( opb >> 1 );
    }

    return acc;
}

uint32_t mulu( uint32_t src1, uint32_t src2 ) {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Iterate over smaller positive operand (opb) for efficiency
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    uint32_t opa;
    uint32_t opb;

    if( src1 < src2 ) {
        opa = src2;
        opb = src1;
    } else {
        opa = src1;
        opb = src2;
    }

    uint32_t acc = 0;

    while( opb > 0 ){
        if( get_bit( opb, 0 ) ) {
            acc += opa;
        }

        opa = ( opa << 1 );
        opb = ( opb >> 1 );
    }

    return acc;
}

//------------------------------------------------------------------------
// Division
//------------------------------------------------------------------------

int32_t div( int32_t numerator, int32_t denominator ) {

    if( denominator == 0 ){ return 0; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Make sure that the result is the correct sign
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    int32_t flip_result = 0;

    if( numerator < 0 ){
        numerator = -numerator;
        flip_result = !flip_result;
    }

    if( denominator < 0 ){
        denominator = -denominator;
        flip_result = !flip_result;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Perform iterative division by shifting
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // This is similar to iterative division by subtraction, but uses
    // shifting to get logarithmic complexity

    int32_t opa = numerator;
    int32_t opb = denominator;
    int32_t shift_amt = 1;

    while( ( opb << 1 ) <= opa ){
        opb       = ( opb       << 1 );
        shift_amt = ( shift_amt << 1 );
    }

    int32_t acc = 0;
    while( ( opb > 0 ) & ( shift_amt > 0 ) ){
        if( opb <= opa ){
            acc += shift_amt;
            opa -= opb;
        }

        opb       = ( opb       >> 1 );
        shift_amt = ( shift_amt >> 1 );
    }

    return ( flip_result ) ? -acc : acc;
}

uint32_t divu( uint32_t numerator, uint32_t denominator ) {

    if( denominator == 0 ){ return 0; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Perform iterative division by shifting
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    uint32_t opa = numerator;
    uint32_t opb = denominator;
    int32_t shift_amt = 1;

    while( ( opb << 1 ) <= opa ){
        opb       = ( opb       << 1 );
        shift_amt = ( shift_amt << 1 );
    }

    uint32_t acc = 0;
    while( ( opb > 0 ) & ( shift_amt > 0 ) ){
        if( opb <= opa ){
            acc += shift_amt;
            opa -= opb;
        }

        opb       = ( opb       >> 1 );
        shift_amt = ( shift_amt >> 1 );
    }

    return acc;
}

//------------------------------------------------------------------------
// Remainder
//------------------------------------------------------------------------

int32_t rem( int32_t numerator, int32_t denominator ) {
    if( denominator == 0 ){ return numerator; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Make sure that the result is the correct sign
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    int32_t flip_result = 0;

    if( numerator < 0 ){
        numerator = -numerator;
        flip_result = !flip_result;
    }

    if( denominator < 0 ){
        denominator = -denominator;
        flip_result = !flip_result;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Perform iterative division by shifting
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    int32_t opa = numerator;
    int32_t opb = denominator;
    int32_t shift_amt = 1;

    while( ( opb << 1 ) <= opa ){
        opb       = ( opb       << 1 );
        shift_amt = ( shift_amt << 1 );
    }

    while( ( opb > 0 ) & ( shift_amt > 0 ) ){
        if( opb <= opa ){
            opa -= opb;
        }

        opb       = ( opb       >> 1 );
        shift_amt = ( shift_amt >> 1 );
    }

    return ( flip_result ) ? -opa : opa;
}

uint32_t remu( uint32_t numerator, uint32_t denominator ) {
    if( denominator == 0 ){ return numerator; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Perform iterative division by shifting
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    uint32_t opa = numerator;
    uint32_t opb = denominator;
    int32_t shift_amt = 1;

    while( ( opb << 1 ) <= opa ){
        opb       = ( opb       << 1 );
        shift_amt = ( shift_amt << 1 );
    }

    while( ( opb > 0 ) & ( shift_amt > 0 ) ){
        if( opb <= opa ){
            opa -= opb;
        }

        opb       = ( opb       >> 1 );
        shift_amt = ( shift_amt >> 1 );
    }

    return opa;
}