#include <avr/io.h>
#include <util/delay.h>

void uart_setup() {
    /* TODO UART initialisieren - 9600Baud, 8N1*/
    
}

void uart_send_char(char ch) {
    /* TODO Zeichen ch über UART senden*/
}

int main() {
    /* UART-Initialisierung */
    uart_setup();

    /* Wiederholt ein Zeichen senden */
    while (1) {
        uart_send_char('H');
        _delay_ms(500);
    }
}