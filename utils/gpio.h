//========================================================================
// gpio.h
//========================================================================
// Functions for blinking GPIOs

#ifndef GPIO_H
#define GPIO_H

void gpio_high( int gpio );
void gpio_low ( int gpio );
void gpio_toggle( int gpio );

void gpio_set ( int gpio, int is_high );

#endif // GPIO_H