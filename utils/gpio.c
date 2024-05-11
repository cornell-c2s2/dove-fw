//========================================================================
// gpio.c
//========================================================================
// Definitions for blinking GPIOs

#include "defs.h"
#include "bitops.h"

void gpio_high( int gpio ) {
    if( gpio > 31 ){
        reg_mprj_datah = set_bit( reg_mprj_datah, gpio - 32 );
    } else {
        reg_mprj_datal = set_bit( reg_mprj_datal, gpio );
    }
}

void gpio_low( int gpio ) {
    if( gpio > 31 ){
        reg_mprj_datah = reset_bit( reg_mprj_datah, gpio - 32 );
    } else {
        reg_mprj_datal = reset_bit( reg_mprj_datal, gpio );
    }
}

void gpio_toggle( int gpio ) {
    if( gpio > 31 ){
        int curr_state = get_bit( reg_mprj_datah, gpio - 32 );
        if( curr_state ){
            reg_mprj_datah = reset_bit( reg_mprj_datah, gpio - 32 );
        } else {
            reg_mprj_datah = set_bit( reg_mprj_datah, gpio - 32 );
        }
        
    } else {
        int curr_state = get_bit( reg_mprj_datal, gpio );
        if( curr_state ){
            reg_mprj_datal = reset_bit( reg_mprj_datal, gpio );
        } else {
            reg_mprj_datal = set_bit( reg_mprj_datal, gpio );
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