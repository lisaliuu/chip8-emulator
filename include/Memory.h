/**
 * File name: Memory.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief   Defines the functions of the Memory class that holds
 *          an array of size 4096 that represents the RAM of the Chip8
 * @details Functionalities are creating and loading ROMs into the memory
 *          array.
 * @author  Lisa (Chuci) Liu
 */
class Memory {
private:
    // size of Chip8 memory -- 4096 bytes
    static const unsigned int MEM_SIZE = 0x1000;

    // starting address of loaded Chip8 program
    static const unsigned int ROM_START_ADDRESS = 0x0200;

    // size of font set storage in memory
    static const unsigned int FONT_SET_SIZE = 0x50;

    // starting address of font data in memory
    static const unsigned int FONT_START_ADDRESS = 0x0050;

    // Maximum allowed ROM size
    static const unsigned int MAX_ROM_SIZE = MEM_SIZE - ROM_START_ADDRESS;

    // Chip8 memory as represented by an array where each element is a byte
    std::array<uint8_t, MEM_SIZE> memoryArr;

    // Chip8 font data
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

    /**
     * @brief   The constructor for the Memory class that loads the
     *          font set into memory.
     */
    Memory();

    /**
     * @brief   Loads the ROM at path provided into memory
     * @param   <filePath> path to the ROM file to load into memory
     */
    bool loadProgram(std::string filePath);

public:
    friend class Chip8;
};
#endif //CHIP8_MEMORY_H
