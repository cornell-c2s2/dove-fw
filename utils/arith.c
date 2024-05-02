//========================================================================
// arith.c
//========================================================================
// Implementation of basic arithmetic functions

#include "arith.h"
#include "bitops.h"

//------------------------------------------------------------------------
// Multiplication
//------------------------------------------------------------------------

int mul( int src1, int src2 ) {

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

    int opa;
    int opb;

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

    int acc = 0;

    while( opb > 0 ){
        if( get_bit( opb, 0 ) ) {
            acc += opa;
        }

        opa = ( opa << 1 );
        opb = ( opb >> 1 );
    }

    return acc;
}

unsigned int mulu( unsigned int src1, unsigned int src2 ) {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Iterate over smaller positive operand (opb) for efficiency
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    unsigned int opa;
    unsigned int opb;

    if( src1 < src2 ) {
        opa = src2;
        opb = src1;
    } else {
        opa = src1;
        opb = src2;
    }

    unsigned int acc = 0;

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

int div( int numerator, int denominator ) {

    if( denominator == 0 ){ return 0; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Make sure that the result is the correct sign
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    int flip_result = 0;

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

    int opa = numerator;
    int opb = denominator;
    int shift_amt = 1;

    while( ( opb << 1 ) <= opa ){
        opb       = ( opb       << 1 );
        shift_amt = ( shift_amt << 1 );
    }

    int acc = 0;
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

unsigned int divu( unsigned int numerator, unsigned int denominator ) {

    if( denominator == 0 ){ return 0; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Perform iterative division by shifting
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    unsigned int opa = numerator;
    unsigned int opb = denominator;
    int shift_amt = 1;

    while( ( opb << 1 ) <= opa ){
        opb       = ( opb       << 1 );
        shift_amt = ( shift_amt << 1 );
    }

    unsigned int acc = 0;
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

int rem( int numerator, int denominator ) {
    if( denominator == 0 ){ return numerator; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Make sure that the result is the correct sign
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    int flip_result = 0;

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

    int opa = numerator;
    int opb = denominator;
    int shift_amt = 1;

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

unsigned int remu( unsigned int numerator, unsigned int denominator ) {
    if( denominator == 0 ){ return numerator; }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Perform iterative division by shifting
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    unsigned int opa = numerator;
    unsigned int opb = denominator;
    int shift_amt = 1;

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