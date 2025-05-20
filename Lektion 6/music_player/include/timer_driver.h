#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H
#include <stdint.h>

void start_melody(uint16_t ms_per_tick);
void note_on(uint8_t note_number);
void note_off();

#endif /* TIMER_DRIVER_H */
