#include <gtest/gtest.h>

int32_t main(int32_t argc, char** argv)
{
    // Initialize google test library.
    testing::InitGoogleTest(&argc, argv);

    // Run all tests
    return RUN_ALL_TESTS();
}