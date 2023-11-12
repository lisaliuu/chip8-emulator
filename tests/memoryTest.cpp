//
// Created by Lisa Liu on 9/17/23.
//

#include "memory.h"
#include <gtest/gtest.h>
#include <array>

namespace {

    // Sample data
    std::string EXISTING_FILE_NAME = "../roms/test.ch8";
    std::string NO_EXISTING_FILE_NAME = "../roms/tst.ch8";

    // The test fixture for testing memory.
    class MemoryTest : public ::testing::Test { };

    TEST_F(MemoryTest, ExtractValidFile) {
        Memory mem;
        EXPECT_TRUE( mem.loadProgram(EXISTING_FILE_NAME));
    }

    TEST_F(MemoryTest, ExtractInvalidFile) {
        Memory mem;
        EXPECT_FALSE(mem.loadProgram(NO_EXISTING_FILE_NAME));
    }

}