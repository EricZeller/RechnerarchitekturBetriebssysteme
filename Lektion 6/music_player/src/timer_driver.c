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
void start_melody(uint16_t ms_per_tick) {
    /* TODO Timer0 konfigurieren*/
    do {
        TCNT0 = 0;
        for (uint16_t ms=0; ms < ms_per_tick; ms++) {
            /* TODO Mit Timer0 1ms warten*/
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
void note_on(uint8_t note_number) {
    /* TODO Timer1 für Tonerzeugung konfigurieren*/
}

/**
 * Schalte die Tonerzeugung ab.
 */
void note_off() {
    /* TODO Tonerzeugung stoppen*/
}
