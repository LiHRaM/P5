#include "../inc/minunit.h"
#include "../inc/shared.h"

// 1023 - 1023 = 0
MU_TEST(reduce_u16_to_u8_returns_0_on_1023) {
    unsigned char expected = 0;
    unsigned char actual = reduce_u16_to_u8(1023);
    mu_check(expected == actual);
}

// (1023 - 0) / 8 = 127.875
MU_TEST(reduce_u16_to_u8_returns_127_on_0) {
    unsigned char expected = 127;
    unsigned char actual = reduce_u16_to_u8(0);
    mu_check(expected == actual);
}

// (1023 - 512) / 8 = 63.875
MU_TEST(reduce_u16_to_u8_returns_63_on_512) {
    unsigned char expected = 63;
    unsigned char actual = reduce_u16_to_u8(512);
    mu_check(expected == actual);
}

MU_TEST_SUITE(test_shared) {
    MU_RUN_TEST(reduce_u16_to_u8_returns_0_on_1023);
    MU_RUN_TEST(reduce_u16_to_u8_returns_127_on_0);
    MU_RUN_TEST(reduce_u16_to_u8_returns_63_on_512);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_shared);
    MU_REPORT();
    return minunit_status;
}