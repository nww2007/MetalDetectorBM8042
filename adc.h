#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

enum{SIGNAL=0,  // Выход усилителя
     BATTERY=1, // Напряжение батареи
     CURRENT=2, // Плюс датчика тока
     GROUND=3,  // Минус датчика тока
     SENSOR=5,  // Признак датчика
     MODE=6,    // Режим
     LIMIT=7};  // Порог (потенциометр)

void adc_init(void);
unsigned int adc_read(unsigned char);

#endif
