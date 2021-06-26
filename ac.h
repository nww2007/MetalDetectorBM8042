#ifndef AC_H
#define AC_H

#include <avr/io.h>

// Настраиваем аналоговый компаратор
// Сбрасываем бит прерывания от аналового компаратора
// Ждём спада анаового компаратора
#define WAIT_FOR_END_PULSE   \
        ac_init();           \
        ACSR |= (1 << ACI);  \
        while((ACSR & (1 << ACI)) == 0)

void ac_init(void);

#endif
