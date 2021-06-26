#include<avr/io.h>
#include"uart.h"
 

int uart_putchar(char c, FILE *stream)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
	return 0;
}


void uart_init(void){
    #define BAUD 500000
    #include <util/setbaud.h>
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
    #if USE_2X
    UCSRA |= (1 << U2X);
    #else
    UCSRA &= ~(1 << U2X);
    #endif
    //------------------------------------------------------------
    // Настраиваем UART0
    UCSRA = 0
        | (0 << RXC)
        | (1 << TXC)
        | (1 << UDRE)
        | (0 << FE)
        | (0 << DOR)
        | (0 << PE)
        | (0 << U2X)
        | (0 << MPCM)
        ;
    /* Enable receiver and transmitter */
    // UDRIE не должен быть установлен! Этот бит используется как флаг далее.
    UCSRB = 0
        | (0 << RXCIE)	// Enable rx complet interrupt
        | (0 << TXCIE)	// Enable tx complet interrupt
        | (0 << UDRIE)	// Enable data register empty complet interrupt
        | (1 << RXEN)	// On receaver
        | (1 << TXEN)	// On transmitter
        | (1 << UCSZ2)	// 9-bit character size
        | (0 << RXB8)
        | (1 << TXB8)
        ;
    /* Set frame format: 9data, 2stop bit Enabled, Odd Parity */
    UCSRC = 0
        | (1 << URSEL) | (0 << UMSEL)	// Asynchronous USART
        | (0 << UPM1)  | (0 << UPM0)	// Parity None
        | (1 << USBS)					// 2 stop bit
        | (1 << UCSZ1) | (1 << UCSZ0)	// 8-bit character size
        | (0 << UCPOL)					// Rising TX, falling RX
        ;

    DDRB |= (1<<PB5); //  pinMode(13,OUTPUT);
}
