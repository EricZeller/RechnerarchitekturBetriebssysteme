#include "unity.h"
#include <arith.h>
#include <util/delay.h>

void test_add16() {
    TEST_ASSERT_EQUAL_INT16_MESSAGE(          25+5, add16(25, 5), "8 bit, no mid-carry");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(          25+5, add16(25, 5), "8 bit, no mid-carry, swapped");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 0x1020+0x2030, add16(0x1020, 0x2030), "16 bit positive, no mid-carry");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 0x1020+0x2030, add16(0x2030, 0x1020), "16 bit positive, no mid-carry, swapped");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(-0x1020+0x101F, add16(-0x1020, 0x101F), "16 bit negative, no mid-carry");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(-0x1020+0x101F, add16(0x101F, -0x1020), "16 bit negative, no mid-carry, swapped");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 0x1020+0x20E0, add16(0x1020, 0x20E0), "16 bit positive, mid-carry");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 0x1020+0x20E0, add16(0x20E0, 0x1020), "16 bit positive, mid-carry, swapped");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 0x1020-0x1F20, add16(0x1020, -0x1F20), "16 bit negative, mid-carry");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 0x1020-0x1F20, add16(-0x1F20, 0x1020), "16 bit negative, mid-carry, swapped");
}

void test_shl16() {
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(0x55<<1, shl16(0x55), "8 bit, no mid-carry");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(0x5555<<1, shl16(0x5555), "16 bit, no mid carry");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(0x0AAA<<1, shl16(0x0AAA), "16 bit, mid carry");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(0xAAAA<<1, shl16(0xAAAA), "16 bit, high carry");
}

void test_mult8_8() {
    TEST_ASSERT_EQUAL_INT16_MESSAGE(     25*5, mult8_8(25,5), "8 bit positive");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(     25*5, mult8_8(5,25), "8 bit positive swapped");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(    125*5, mult8_8(125,5), "16 bit positive");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 125*(-5), mult8_8(125,-5), "16 bit negative");
    TEST_ASSERT_EQUAL_INT16_MESSAGE( 125*(-5), mult8_8(-5,125), "16 bit negative swapped");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(-125*(-5), mult8_8(-125,-5), "16 bit both negative");
}

void test_multu8_16() {
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t) 25*5, multu8_16( 25,5), "8 bit");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t) 25*5, multu8_16( 5,25), "8 bit swapped");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)125*5, multu8_16(125,5), "16 bit");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)125*5, multu8_16(5,125), "16 bit swapped");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)5*513, multu8_16(5,513), "24 bit");
}

void test_multu16_16() {
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t) 25*  5, multu16_16( 25,  5), "8 bit");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t) 25*  5, multu16_16(  5, 25), "8 bit swapped");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)125*  5, multu16_16(125,  5), "16 bit");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)125*  5, multu16_16(  5,125), "16 bit swapped");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)  5*513, multu16_16(  5,513), "24 bit");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)  5*513, multu16_16(513,  5), "24 bit swapped");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)911*513, multu16_16(911,513), "32 bit");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)911*513, multu16_16(513,911), "32 bit swapped");
}

int main() {
    _delay_ms(2000);
    UNITY_BEGIN();
    RUN_TEST(test_add16);
    RUN_TEST(test_shl16);
    RUN_TEST(test_mult8_8);
    RUN_TEST(test_multu8_16);
    RUN_TEST(test_multu16_16);
    return UNITY_END();
}