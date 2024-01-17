/**
 * File name: Memory.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <array>
#include <string>

/**
 * @class Memory
 * @brief Memory class that implements the memory of the Chip8 as an STD array
 * of size 4096. This class provides functions to load a ROM into memory and
 *        access to and information about the address locations in memory.
 */
class Memory {
public:
  static constexpr unsigned int ROM_START_ADDRESS = 0x0200;

  // Creates and fills the memory array with 0s, then loads font sprites into
  // memory.
  Memory();

  // Loads the ROM at filePath into memory
  void loadProgram(const std::string &filePath);

  // Returns a const reference to the element stored at specified index in
  // memory array
  const uint8_t &operator[](int index) const;

  // Returns a reference to the element stored at specified index in memory
  // array
  uint8_t &operator[](int index);

  friend class Chip8;

private:
  static constexpr unsigned int MEM_SIZE = 0x1000;
  static constexpr unsigned int FONT_SET_SIZE = 0x50;
  static constexpr unsigned int FONT_START_ADDRESS = 0x0050;
  static constexpr unsigned int MAX_ROM_SIZE = MEM_SIZE - ROM_START_ADDRESS;

  std::array<uint8_t, MEM_SIZE> memoryArr;

  // Chip8 font sprites
  const std::array<uint8_t, FONT_SET_SIZE> fonts = {
      0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
      0x20, 0x60, 0x20, 0x20, 0x70, // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };
};
#endif // CHIP8_MEMORY_H
