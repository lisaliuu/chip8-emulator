//
// Created by Lisa Liu on 9/17/23.
//

#include "../include/Memory.h"
#include <array>
#include <gtest/gtest.h>

namespace {

// Sample data
std::string EXISTING_FILE_NAME = "IBM_Logo.ch8";
std::string NO_EXISTING_FILE_NAME = "tst.ch8";

// The test fixture for testing memory.
class MemoryTest : public ::testing::Test {};

TEST_F(MemoryTest, ExtractValidFile) {
  Memory mem = Memory();
  ASSERT_NO_FATAL_FAILURE(mem.loadProgram(EXISTING_FILE_NAME));
}

TEST_F(MemoryTest, ExtractInvalidFile) {
  ASSERT_EXIT({
    Memory mem = Memory();
    mem.loadProgram(NO_EXISTING_FILE_NAME); },
              ::testing::ExitedWithCode(EXIT_FAILURE), ".*");
}
} // namespace