/**
 * File name: memory.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <array>
#include <string>

/**
 * @class Memory
 * @brief This class represents the RAM of the Chip8 as an array of size 4096.
 *        Functions include creating and loading ROMs into the memory array.
 */
class Memory {
public:
     // Constructor. Fills the memory with 0 and font sprites.
    Memory();

     // Loads the ROM at filePath into memory.
    bool loadProgram(const std::string& filePath);

    // Const subscript operator to get specified element in memory - checks bound.
    const uint8_t& operator[](int index) const;

    // Subscript operator to get specified element in memory - checks bound.
    uint8_t& operator[](int index);

private:
    // Size of Chip8 memory - 4096 bytes.
    static constexpr unsigned int MEM_SIZE = 0x1000;

    // Starting address of ROM.
    static constexpr unsigned int ROM_START_ADDRESS = 0x0200;

    // Size of font set storage in memory.
    static constexpr unsigned int FONT_SET_SIZE = 0x50;

    // Starting address of font data in memory.
    static constexpr unsigned int FONT_START_ADDRESS = 0x0050;

    // Maximum allowed ROM size.
    static constexpr unsigned int MAX_ROM_SIZE = MEM_SIZE - ROM_START_ADDRESS;

    // Array representing the Chip8 memory where each element is a byte.
    std::array<uint8_t, MEM_SIZE> memoryArr;

    // Chip8 font sprites.
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
#endif //CHIP8_MEMORY_H
