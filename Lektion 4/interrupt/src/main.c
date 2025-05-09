#include <avr/io.h> /* Für Zugriff auf Ports */
#include <avr/interrupt.h>
#include <util/delay.h> /* Für _delay_ms() */

/* Interrupt-Handler für Pin-Change-Interrupt PCINT2 */
ISR(PCINT2_vect)
{
    /* Wenn Taster (nun) offen (HIGH wegen Pull-Up), LED an B5 einschalten*/
    if (PIND & (1 << PD6)) {
        PORTB |= (1 << PB5);
    }
}

int main()
{
    /* Pins D2 bis D5 sowie B5 als Output und Pin D6 als Input konfigurieren*/
    DDRD = (0b00111100);
    DDRB = (1 << DDB5);
    
    /* Pin-Change-Interrupt PCINT2 über PCICR-Register einschalten*/
    PCICR = (1 << PCIE2);
    
    /* Pin-Change-Interrupt für PIN D6/PCINT22 über PCMSK2-Register einschalten*/
    PCMSK2 = (1 << PCINT22);
    
    /* Interrupts global aktivieren*/
    sei();
    
    /* Pin B5 auf 0 zurücksetzen*/
    PORTB &= ~(1 << PB5);
    
    while (1)
    {
        for (int i = 2; i < 6; i++)
        {
            /* Pin Di auf HIGH schalten, andere Bits unverändert lassen*/
            PORTD |= (1 << i);
            _delay_ms(250);
            
            /* Pin Di auf LOW schalten, andere Bits unverändert lassen*/
            PORTD &= ~(1 << i);
            
            
        }
        /* Lichtorgel durch, LED ausschalten */
        PORTB &= ~(1 << PB5);
    }
}