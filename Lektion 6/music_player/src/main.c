#include <avr/io.h>
#include <stdint.h>
#include "music_player.h"

#include "melodies/fuer_elise.h"

int main(void) {
	/* Pin B1 auf Output */
	DDRB = (1<<PB1);

	while (1) {
		/* Auf Tastendruck warten */
		while (PINB & (1<<PB0)) {
			/* Nichts tun */
		}
		/* Melodie abspielen */
		player_start(note_pitches, note_durations, NOTE_COUNT, MS_PER_TICK);
	}
}
