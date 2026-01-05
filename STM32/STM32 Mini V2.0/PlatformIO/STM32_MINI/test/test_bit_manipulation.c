#include <unity.h>
#include "bit_manipulation.h"

// Setup function called before each test
void setUp(void) {
    // Initialize if needed
}

// Teardown function called after each test
void tearDown(void) {
    // Cleanup if needed
}

// Example test for bit manipulation macros
void test_bit_manipulation(void) {
    uint32_t reg = 0;

    // Test BIT_SET
    BIT_SET(reg, 0);
    TEST_ASSERT_EQUAL_UINT32(1, reg);

    BIT_SET(reg, 2);
    TEST_ASSERT_EQUAL_UINT32(5, reg); // 1 | 4 = 5

    // Test BIT_CLEAR
    BIT_CLEAR(reg, 0);
    TEST_ASSERT_EQUAL_UINT32(4, reg);

    // Test BIT_TOGGLE
    BIT_TOGGLE(reg, 2);
    TEST_ASSERT_EQUAL_UINT32(0, reg);

    // Test BIT_IS_SET
    BIT_SET(reg, 1);
    TEST_ASSERT_TRUE(BIT_IS_SET(reg, 1));
    TEST_ASSERT_FALSE(BIT_IS_SET(reg, 0));

    // Test BIT_IS_CLEAR
    TEST_ASSERT_TRUE(BIT_IS_CLEAR(reg, 0));
    TEST_ASSERT_FALSE(BIT_IS_CLEAR(reg, 1));

    // Test BITS_SET
    BITS_SET(reg, 0x0F); // Set bits 0-3
    TEST_ASSERT_EQUAL_UINT32(0x0F, reg);

    // Test BIT_SET_2
    reg = 0;
    BIT_SET_2(reg, 0, 1);
    TEST_ASSERT_EQUAL_UINT32(3, reg);
}

// Main function for running tests
int main(void) {
    // Start Unity test framework
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_bit_manipulation);

    // End tests
    return UNITY_END();
}