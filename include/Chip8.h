/**
 * File name: chip8.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <array>
#include <stack>
#include <chrono>
#include <thread>
#include "Display.h"
#include "Memory.h"
#include "Opcode.h"
#include "EventHandler.h"


/**
 * @struct Cpu
 * @brief This struct holds variables in and related to the CPU, including
 *        registers, address pointers, timers, and stack.
 */
struct Cpu{
    static constexpr unsigned int REG_SIZE = 0x10;
    std::array<uint8_t, REG_SIZE> registers;
    std::stack<uint16_t> stack;
    uint16_t pc;
    uint16_t i;
    uint8_t delayTimer;
    std::chrono::steady_clock::time_point prevTickTime;

    Cpu();
};

/**
 * @brief   Defines the functions of the Memory class that holds
 *          an array of size 4096 that represents the RAM of the Chip8
 * @details Functionalities are creating and loading ROMs into the memory
 *          array.
 */
class Chip8{
public:
    Chip8();

    void loadProgram(const std::string& filePath);

    void handleTime(int frameRate);

    void cycle(const Keypad& k);

    uint32_t* getDisplay();

private:
    Cpu cpu;
    Display display;
    Memory memory;

    std::unordered_map<std::string, size_t> instrCount;

    void runInstruction(const Opcode& instr, const Keypad& k);

    void printInstrCount() const;

    void exitProgram(const Opcode& instr);

    // 00E0
    void CLS();

    // 00EE
    void RET();

    // 1NNN
    void JMP(const Opcode& op);

    // 2NNN
    void CALL(const Opcode& op);

    // 3XNN
    void SE_VX_NN(const Opcode& op);

    // 4XNN
    void SNE_VX_NN(const Opcode& op);

    // 5XY0
    void SE_VX_VY(const Opcode& op);

    // 6XNN
    void LD_VX_NN(const Opcode& op);

    // 7XNN
    void ADD_VX_NN(const Opcode& op);

    // 8XY0
    void LD_VX_VY(const Opcode& op);

    // 8XY1
    void OR_VX_VY(const Opcode& op);

    // 8XY2
    void AND_VX_VY(const Opcode& op);

    // 8XY3
    void XOR_VX_VY(const Opcode& op);

    // 8XY4
    void ADD_VX_VY(const Opcode& op);

    // 8XY5
    void SUB_VX_VY(const Opcode& op);

    // 8XY6
    void SHR_VX(const Opcode& op);

    // 8XY7
    void SUBN_VX_VY(const Opcode& op);

    // 8XYE
    void SHL_VX(const Opcode& op);

    // 9XY0
    void SNE_VX_VY(const Opcode& op);

    // ANNN - Set the index register I to NNN
    void LD_I(const Opcode& op);

    // BNNN
    void JP_V0(const Opcode& op);

    // CXNN
    void RND(const Opcode& op);

    // DXYN
    void DRW(const Opcode& op);

    // EX9E
    void SKP(const Opcode& op, const Keypad& k);

    // EXA1
    void SKNP(const Opcode& op, const Keypad& k);

    // FX07
    void LD_VX_DT(const Opcode& op);

    // FX0A
    void LD_VX_K(const Opcode& op, const Keypad& k);

    // FX15
    void LD_DT(const Opcode& op);

    // FX18
    void LD_ST(const Opcode& op);

    // FX1E
    void ADD_I_VX(const Opcode& op);

    // FX29
    void LD_F_VX(const Opcode& op);

    // FX33
    void LD_B_VX(const Opcode& op);

    // FX55
    void LD_I_VX(const Opcode& op);

    // FX65
    void LD_VX_I(const Opcode& op);

};

#endif //CHIP8_CHIP8_H
