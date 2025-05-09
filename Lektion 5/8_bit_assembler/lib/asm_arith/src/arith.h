#ifndef ARITH_H
#define ARITH_H

#include <stdint.h>

extern int16_t add16(int16_t a, int16_t b);
extern uint16_t shl16(uint16_t a);
extern int16_t mult8_8(int8_t a, int8_t b);
extern uint32_t multu8_16(uint8_t a, uint16_t b);
extern uint32_t multu16_16(uint16_t a, uint16_t b);

#endif /* ARITH_H */