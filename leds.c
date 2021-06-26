#include <avr/io.h>
#include "leds.h"
#include "pin_macros.h"

void leds_init(void){
    DRIVER(LED1, OUT);
    DRIVER(LED2, OUT);
    DRIVER(LED3, OUT);
    DRIVER(LED4, OUT);
    DRIVER(LED5, OUT);
    DRIVER(LED6, OUT);
}

void leds_set_value(uint8_t value){
    switch(value){
    case 0:
        OFF(LED1);
        OFF(LED2);
        OFF(LED3);
        OFF(LED4);
        OFF(LED5);
        OFF(LED6);
        break;
    case 1:
        ON(LED1);
        OFF(LED2);
        OFF(LED3);
        OFF(LED4);
        OFF(LED5);
        OFF(LED6);
        break;
    case 2:
        OFF(LED1);
        ON(LED2);
        OFF(LED3);
        OFF(LED4);
        OFF(LED5);
        OFF(LED6);
        break;
    case 3:
        OFF(LED1);
        OFF(LED2);
        ON(LED3);
        OFF(LED4);
        OFF(LED5);
        OFF(LED6);
        break;
    case 4:
        OFF(LED1);
        OFF(LED2);
        OFF(LED3);
        ON(LED4);
        OFF(LED5);
        OFF(LED6);
        break;
    case 5:
        OFF(LED1);
        OFF(LED2);
        OFF(LED3);
        OFF(LED4);
        ON(LED5);
        OFF(LED6);
        break;
    case 6:
        OFF(LED1);
        OFF(LED2);
        OFF(LED3);
        OFF(LED4);
        OFF(LED5);
        ON(LED6);
        break;
    default:
        OFF(LED1);
        OFF(LED2);
        OFF(LED3);
        OFF(LED4);
        OFF(LED5);
        ON(LED6);
        break;
    }
}
