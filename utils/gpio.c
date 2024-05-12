//========================================================================
// gpio.c
//========================================================================
// Definitions for blinking GPIOs

#include "defs.h"
#include "bitops.h"

int curr_datal = 0;
int curr_datah = 0;

void gpio_high( int gpio ) {
    if( gpio > 31 ){
        curr_datah = set_bit( curr_datah, gpio - 32 );
        reg_mprj_datah = curr_datah;
    } else {
        curr_datal = set_bit( curr_datal, gpio );
        reg_mprj_datal = curr_datal;
    }
}

void gpio_low( int gpio ) {
    if( gpio > 31 ){
        curr_datah = reset_bit( curr_datah, gpio - 32 );
        reg_mprj_datah = curr_datah;
    } else {
        curr_datal = reset_bit( curr_datal, gpio );
        reg_mprj_datal = curr_datal;
    }
}

void gpio_toggle( int gpio ) {
    if( gpio > 31 ){
        int curr_state = get_bit( curr_datah, gpio - 32 );
        if( curr_state ){
            curr_datah = reset_bit( curr_datah, gpio - 32 );
            reg_mprj_datah = curr_datah;
        } else {
            curr_datah = set_bit( curr_datah, gpio - 32 );
            reg_mprj_datah = curr_datah;
        }
        
    } else {
        int curr_state = get_bit( curr_datal, gpio );
        if( curr_state ){
            curr_datal = reset_bit( curr_datal, gpio );
            reg_mprj_datal = curr_datal;
        } else {
            curr_datal = set_bit( curr_datal, gpio );
            reg_mprj_datal = curr_datal;
        }
    }
}

void gpio_set( int gpio, int is_high ){
    if( is_high ){
        gpio_high( gpio );
    } else {
        gpio_low( gpio );
    }
}