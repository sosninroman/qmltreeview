#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    auto retval = RUN_ALL_TESTS();
    //std::getchar();
    return retval;
}
