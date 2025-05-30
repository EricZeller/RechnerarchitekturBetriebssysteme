#include <avr/io.h>
#include <util/delay.h>

void uart_setup()
{
    unsigned int ubrr = 16000000 / 16 / 9600 - 1;
    /* TODO UART initialisieren - 9600Baud, 8N1*/
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);/* Enable receiver and transmitter * /
     /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send_char(char ch)
{
    /* TODO Zeichen ch über UART senden*/
    {
        /* Wait for empty transmit buffer */
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        /* Put data into buffer, sends the data */
        UDR0 = ch;
    }
}

int main()
{
    /* UART-Initialisierung */
    uart_setup();

    /* Wiederholt ein Zeichen senden */
    while (1)
    {
        uart_send_char('H');
        /*uart_send_char('a');
        uart_send_char('l');
        uart_send_char('l');
        uart_send_char('o');
        uart_send_char(' ');*/
        _delay_ms(500);
    }
}