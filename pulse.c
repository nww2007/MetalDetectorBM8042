#include "pulse.h"
#include <avr/io.h>
#include "pin_macros.h"


void pulse_init(void){
    OFF(PULSE);
    DRIVER(PULSE, OUT);
}
