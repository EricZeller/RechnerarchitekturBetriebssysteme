#include "music_player.h"
#include "timer_driver.h"

static size_t current_note_index;
static const uint8_t* melody_note_pitches;
static const uint16_t* melody_note_durations;
static size_t melody_note_count;
static uint8_t remaining_note_duration;

static bool player_next_note();

void player_start(const uint8_t *note_pitches,
                  const uint16_t *note_durations,
                  const size_t note_count,
                  const uint16_t ms_per_tick) {
    current_note_index = 0;
    melody_note_pitches = note_pitches;
    melody_note_durations = note_durations;
    melody_note_count = note_count;
    if (player_next_note()) {
        /* Die Melodie ist nicht leer. */

        /* Starte Melodie */
        start_melody(ms_per_tick);
    }
}

bool player_tick() {
    if (remaining_note_duration > 1) {
        /* Note hält an => runterzählen und weiterspielen */
        remaining_note_duration--;
        return true;
    }

    /* Aktuelle Note wurde beendet => nächste Note oder Ende der Melodie */
    return player_next_note();
}

/* Bereite das Abspielen der nächsten Note vor */
static bool player_next_note() {
    if (current_note_index >= melody_note_count) {
        /* Die Melodie ist zuende */
        note_off();
        return false;
    }

    remaining_note_duration = melody_note_durations[current_note_index];
    uint8_t note_pitch = melody_note_pitches[current_note_index];
    if (note_pitch) {
        /* Eine echte Note, keine Pause */
        note_on(note_pitch);
    } else {
        /* Pause => Zur Sicherheit schalten wir die Note aus */
        note_off();
    }
    current_note_index++;
    return true;
}
