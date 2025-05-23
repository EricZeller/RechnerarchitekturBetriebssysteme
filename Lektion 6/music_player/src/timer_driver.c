#include "timer_driver.h"
#include "music_player.h"

#include <avr/io.h>

/** Timer-Werte für die Noten nach MIDI-Notennummer.
 * Der erste Eintrag entspricht MIDI-Notennummer 1. */
extern uint16_t note_freqs[];

/**
 * Beginne die Melodie und setze die Tick-Frequenz.
 *
 * Diese Funktion wird zum Start einer Melodie aufgerufen.
 * Es wird erwartet, dass danach periodisch die Funktion player_tick
 * aufgerufen wird bis der Rückgabewert der Funktion player_tick Null wird.
 * Die Periode zwischen den Aufrufen soll ms_per_tick Millisekunden betragen.
 *
 * Der Aufruf von player_tick soll dabei immer am Ende einer Periode liegen.
 *
 * @param ms_per_tick    Dauer einer Periode in Millisekunden.
 */
void start_melody(uint16_t ms_per_tick)
{
    /* Timer0 konfigurieren für 1ms Interrupt */
    TCCR0A = 0; // Normal mode
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64 (bei 16MHz: 64/16MHz = 4µs pro Tick)
    TCNT0 = 0;
    
    do
    {
        TCNT0 = 0;
        for (uint16_t ms = 0; ms < ms_per_tick; ms++)
        {
            /* Mit Timer0 1ms warten */
            while((TIFR0 & (1 << TOV0)) == 0); // Warte auf Overflow
            TIFR0 |= (1 << TOV0); // Clear Overflow Flag
        }
    } while (player_tick() != 0);
}

/**
 * Beginne, eine Note zu spielen.
 *
 * Diese Funktion soll den Timer so konfigurieren, dass er eine Note
 * mit der angegebenen Notenummer spielt. Die Notennummer entspricht der
 * MIDI-Notennummer und muss erst über die Tabelle note_freqs in freqs.c
 * in einen OCR-Wert umgerechnet werden.
 */
void note_on(uint8_t note_number)
{
    /* TODO Timer1 für Tonerzeugung konfigurieren*/
    TCCR1A = (0 << COM1A1) | (1 << COM1A0)           /* Toggle OC1A on Compare Match */
             | (0 << WGM11) | (0 << WGM10);          /* Lower part of WGM1x-Bits */
    TCCR1B = (0 << CS12) | (0 << CS11) | (1 << CS10) /* Prescaler = 1 */
             | (0 << WGM13) | (1 << WGM12);          /* Upper half of WGM1x-Bits */
    OCR1A = 18175;                                   /* Length of half-period -1*/
}

/**
 * Schalte die Tonerzeugung ab.
 */
void note_off()
{
    /* TODO Tonerzeugung stoppen*/
    TCCR1B = 0;
}
