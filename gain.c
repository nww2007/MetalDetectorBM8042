#include "gain.h"
#include <avr/io.h>
#include "pin_macros.h"


void amplifire_init(void){
    OFF(GAIN);
    DRIVER(GAIN, OUT);
}

void gain_on(void){
    ON(GAIN);
}

void gain_off(void){
    OFF(GAIN);
}
