/**
 * File name: cpu.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <array>
#include <stack>

class CPU{
private:
    static const unsigned int REG_COUNT = 16;
    std::array<uint8_t, REG_COUNT> registerArr;
    std::stack<uint16_t> stack;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint16_t pc;

public:
    void cycle();

};

#endif //CHIP8_CPU_H
