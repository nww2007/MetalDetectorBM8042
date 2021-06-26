#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "pin_macros.h"

enum{DIV2=1, DIV4=2, DIV8=3, DIV16=4, DIV32=5, DIV64=6, DIV128=7};
void adc_init(void){
    DDRA = 0;
    PORTA = 0;
    ADMUX = (3<<REFS0)             // AREF, Internal Vref turned off
          | (0<<ADLAR)             // Данные АЦП прижаты к младшему биту
          | (0);                   // Аналоговый комутатор к входу ADC0
    // разрешаем АЦП и устанавливаем коэффициент деления предделителя = 128
    ADCSRA = (1<<ADEN)             // Включить АЦП
           | (0<<ADSC)             // Пока не запускать преобразование
           | (0<<ADATE)            // Самозапук запретить
           | (1<<ADIF)             // Очистить флаг прерывания
           | (0<<ADIE)             // Запретить прерывание от АЦП
           | (DIV8<<ADPS0);        // Настроить делитель на 8
}

unsigned int adc_read(unsigned char chnl) {
    // Теперь измеряем нужный канал
    ADMUX = (3<<REFS0)             // AREF, Internal Vref turned off
          | (0<<ADLAR)             // Данные АЦП прижаты к младшему биту
          | (chnl);                // Аналоговый комутатор к заданному входу
    _delay_us(1.5);                // Эта задержка оказалась нужна чтобы исключить влияние между каналами.
    ADCSRA |= (1<<ADSC);           // старт преобразования
    while(!(ADCSRA & (1<<ADIF)));  // ждем окончания преобразования
    ADCSRA |= (1<<ADIF);           // очистим ADIF когда преобразование закончится
    return (ADC);                  // возвращаем рассчитанное значение АЦП
}
