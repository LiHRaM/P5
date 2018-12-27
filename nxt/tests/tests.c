#include "../inc/minunit.h"
#include "../inc/logic.h"

// 1023 - 1023 = 0
MU_TEST(example) {
    mu_check(1 == 1);
}

MU_TEST_SUITE(example_suite) {
    MU_RUN_TEST(example);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(example_suite);
    MU_REPORT();
    return minunit_status;
}