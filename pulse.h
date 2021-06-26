#ifndef PULSE_H
#define PULSE_H

#include "pin_macros.h"

enum{PULSE_US = 200,
     DELAY_B_US = 12,
//      DELAY_B_US = 1,
     DELAY_C_US = 8,
//      DELAY_C_US = 1,
     DELAY_D_US = 50
//      DELAY_D_US = 1
    };

#define PULSE D,5,L // Q0 
#define DO_PULSE(p_w) ON(PULSE);       \
                      delay(US(p_w));  \
                      OFF(PULSE);

void pulse_init(void);

#endif
