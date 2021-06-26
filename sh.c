#include "sh.h"
#include <avr/io.h>
#include "pin_macros.h"


void sh_init(void){
    OFF(SH);
    DRIVER(SH, OUT);
}


void sh_on(void){
    ON(SH);
}


void sh_off(void){
    OFF(SH);
}
