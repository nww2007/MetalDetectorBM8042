#ifndef LEDS
#define LEDS

#include <avr/io.h>

#define LED6 C,5,H
#define LED5 C,4,H
#define LED4 C,3,H
#define LED3 C,2,H
#define LED2 C,1,H
#define LED1 C,0,H

void leds_init(void);
void leds_set_value(uint8_t);

#endif
