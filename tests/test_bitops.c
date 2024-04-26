//========================================================================
// test_bitops.c
//========================================================================
// Testing of bit manipulation functions

#include "bitops.h"

#include <assert.h>
#include <stdio.h>

void test_get_bit() {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Basic tests
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( get_bit( 0b01010101, 2 ) == 1 );
    assert( get_bit( 0b01010101, 3 ) == 0 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Test getting the MSB
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( get_bit( 0xdeadbeef, 31 ) == 1 );
    assert( get_bit( 0x00fedcba, 31 ) == 0 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Test getting the LSB
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( get_bit( 0xdeadbeef, 0 ) == 1 );
    assert( get_bit( 0x00fedcba, 0 ) == 0 );
}

void test_set_bit() {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Basic tests
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( set_bit( 0b01010101, 2 ) == 0b01010101 );
    assert( set_bit( 0b01010101, 3 ) == 0b01011101 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Test setting the MSB
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( set_bit( 0xdeadbeef, 31 ) == 0xdeadbeef );
    assert( set_bit( 0x00fedcba, 31 ) == 0x80fedcba );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Test setting the LSB
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( set_bit( 0xdeadbeef, 0 ) == 0xdeadbeef );
    assert( set_bit( 0x00fedcba, 0 ) == 0x00fedcbb );
}

void test_reset_bit() {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Basic tests
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( reset_bit( 0b01010101, 2 ) == 0b01010001 );
    assert( reset_bit( 0b01010101, 3 ) == 0b01010101 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Test resetting the MSB
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( reset_bit( 0xdeadbeef, 31 ) == 0x5eadbeef );
    assert( reset_bit( 0x00fedcba, 31 ) == 0x00fedcba );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Test resetting the LSB
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    assert( reset_bit( 0xdeadbeef, 0 ) == 0xdeadbeee );
    assert( reset_bit( 0x00fedcba, 0 ) == 0x00fedcba );
}

int main( void ) {

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Run the tests
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    test_get_bit();
    test_set_bit();
    test_reset_bit();

    printf( "All tests passed!\n" );
    return 0;
}