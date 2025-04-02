#include <avr/io.h> /* Für Zugriff auf Ports */
#include <util/delay.h> /* Für _delay_ms() */

int main() {
    DDRD = (0b00111100);
    /* TODO Pins D2 bis D5 als Output konfigurieren*/
    /* Endlose Hauptschleife */
    while (1 == 1) {
        for (int i=2;i<6;i++) {
            PORTD |= (1<<i);
            _delay_ms(250);
            /* TODO Pin Di auf HIGH schalten, andere Bits unverändert lassen*/
            /* TODO 250ms warten*/
            /* TODO Pin Di auf LOW schalten, andere Bits unverändert lassen*/
            PORTD &= ~(1<<i);
        }
    }
}