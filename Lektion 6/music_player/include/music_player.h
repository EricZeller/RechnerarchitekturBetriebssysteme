#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Starte den Music-Player.
 *
 * @param note_pitches    Zeiger auf Array mit den Notenhöhen (MIDI-Notenindex)
 * @param note_durations  Zeiger auf Array mit den Notendauern in Ticks
 * @param note_count      Anzahl der Noten
 * @param ms_per_tick     Millisekunden pro Tick
 */
void player_start(const uint8_t *note_pitches,
                  const uint16_t *note_durations,
                  const size_t note_count,
                  const uint16_t ms_per_tick);

/**
 * Führe die Melodie um einen Tick weiter.
 */
bool player_tick();

#endif /* MUSIC_PLAYER_H */