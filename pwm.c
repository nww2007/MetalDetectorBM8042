#include <avr/io.h>
#include "pwm.h"

void pwm_init(void){
    DDRD |= (1<<PD4); // OC1B
    OCR1B = 0;
    // Выставляем для каналоа ШИМ режим вывода ОС1B сброс при совпадении. 
    // COM1B = 0b10 Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM, (non-inverting mode)
    // Также ставим режим FAST PWM 8bit (таймер 16ти разрядный и допускает
    // большую разрядность ШИМ сигнала. Вплоть до 10 бит.  WGM = 0101
    // Осталось только запустить таймер на частоте МК CS = 001
    TCCR1A = 2<<COM1B0 | 0<<WGM11 | 1<<WGM10;
    // Делитель CS clk I/O /1 (No prescaling)
    TCCR1B = 0<<WGM13 | 1<<WGM12 | 1<<CS10;
}


void pwm_set(uint8_t value){
    OCR1B = value;
}

