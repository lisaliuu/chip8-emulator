/**
 * File name: chip8.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <array>
#include <stack>
#include "display.h"
#include "memory.h"


/**
 * @struct Cpu
 * @brief This struct holds variables in and related to the CPU, including
 *        registers, address pointers, timers, and stack.
 */
struct Cpu{

    static constexpr unsigned int REG_SIZE = 0x10;
    std::array<uint8_t, REG_SIZE> registers;
    std::stack<uint16_t> stack;
    uint16_t pc = 0;
    uint16_t i = 0;
    uint8_t delayTimer = 0;
    uint8_t soundtimer = 0;
};

/**
 * @struct Opcode
 * @brief  This struct represents a Chip8 opcode with accessor methods for decoding
 *         the opcode.
 */
struct Opcode{
public:
    // Constr
    Opcode(uint16_t inOp);

    // Accesses the second nibble, X in register VX.
    uint8_t getX() const;

    // Accesses the third nibble, Y in register VY.
    uint8_t getY() const;

    // Accesses the fourth nibble.
    uint8_t getN() const; // fourth nibble

    // Accesses the third and fourth nibble.
    uint8_t getNN() const;

    // Accesses the second, third, and fourth nibble.
    uint16_t getNNN() const;

private:
    uint16_t rawInstr;
};

/**
 * @brief   Defines the functions of the Memory class that holds
 *          an array of size 4096 that represents the RAM of the Chip8
 * @details Functionalities are creating and loading ROMs into the memory
 *          array.
 * @author  Lisa (Chuci) Liu
 */
class Chip8{
private:
    Display display;
    Cpu cpu;
    Memory memory;

    void incrementPC();

    // 00E0 - Clear display
    void CLS();

    // 00EE - Return from subroutine
    void RET();

    // 1NNN - Jump to memory location NNN
    void JMP(const Opcode& op);

    // 2NNN - Call subroutine at NNN
    void CALL(const Opcode& op);

    // 3XNN - Skip next instruction if reg[VX] equals NN
    void SE_VX_NN(const Opcode& op);

    // 4XNN - Skip next instruction if reg[VX] does not equal NN
    void SNE_VX_NN(const Opcode& op);

    // 5XY0 - Skip next instruction if reg[VX] = reg[VY]
    void SE_VX_VY(const Opcode& op);

    // 6XNN - Set the value NN in reg[VX]
    void LD_VX_NN(const Opcode& in);

    // 7XNN - Add the value NN to reg[VX]
    void ADD_VX_NN(const Opcode& op);

//// 8xy0 - Stores the value of register Vy in register Vx.
//    void LD_VX_VY(Opcode in, Cpu *cpu) {
//        cpu->regs[in.x()] = cpu->regs[in.y()];
//    }
//
//// 8xy1 - Performs a bitwise OR on the values of Vx and Vy.
//    void OR_VX_VY(Opcode in, Cpu *cpu) {
//        cpu->regs[in.x()] |= cpu->regs[in.y()];
//    }
//
//// 8xy2 - Performs a bitwise AND on the values of Vx and Vy.
//    void AND_VX_VY(Opcode in, Cpu *cpu) {
//        cpu->regs[in.x()] &= cpu->regs[in.y()];
//    }
//
//// 8xy3 - Performs a bitwise exclusive OR on the values of Vx and Vy.
//    void XOR_VX_VY(Opcode in, Cpu *cpu) {
//        cpu->regs[in.x()] ^= cpu->regs[in.y()];
//    }
//
//// 8xy4 - Set Vx = Vx + Vy, set VF = carry.
//    void ADD_VX_VY(Opcode in, Cpu *cpu) {
//        uint16_t sum = cpu->regs[in.x()] + cpu->regs[in.y()];
//        cpu->regs[0x0F] = sum > 0xFF ? 1 : 0;
//        cpu->regs[in.x()] = sum & 0xFF;
//    }
//
//// 8xy5 - Set Vx = Vx - Vy, set VF = NOT borrow.
//    void SUB_VX_VY(Opcode in, Cpu *cpu) {
//        cpu->regs[0x0F] = cpu->regs[in.x()] > cpu->regs[in.y()] ? 1 : 0;
//        cpu->regs[in.x()] -= cpu->regs[in.y()];
//    }
//
//// 8xy6 - Set Vx = Vx SHR 1.
//    void SHR_VX(Opcode in, Cpu *cpu) {
//        cpu->regs[0x0F] = cpu->regs[in.x()] & 0x01;
//        cpu->regs[in.x()] >>= 1;
//    }
//
//// 8xy7 - Set Vx = Vy - Vx, set VF = NOT borrow.
//    void SUBN_VX_VY(Opcode in, Cpu *cpu) {
//        cpu->regs[0x0F] = cpu->regs[in.y()] > cpu->regs[in.x()] ? 1 : 0;
//        cpu->regs[in.x()] = cpu->regs[in.y()] - cpu->regs[in.x()];
//    }
//
//// 8xyE - Set Vx = Vx SHL 1.
//    void SHL_VX(Opcode in, Cpu *cpu) {
//        cpu->regs[0x0F] = cpu->regs[in.x()] >> 7;
//        cpu->regs[in.x()] <<= 1;
//    }
//
//// 9xy0 - Skip next instruction if Vx != Vy.
//    void SNE_VX_VY(Opcode in, Cpu *cpu) {
//        if (cpu->regs[in.x()] != cpu->regs[in.y()]) {
//            cpu->pc += 2;
//        }
//    }
//
    // ANNN - Set the index register I to NNN
    void LD_I(const Opcode& op);

//// Bnnn - Program counter is set to nnn plus the value of V0.
//    void JP_V0(Opcode in, Cpu *cpu) {
//        cpu->pc = in.address() + cpu->regs[0x00];
//    }
//
//// Cxkk - Set Vx = random byte AND kk
//    void RND(Opcode in, Cpu *cpu, Random *rand) {
//        cpu->regs[in.x()] = (*rand)() & in.byte();
//    }
//

    // Dxyn - Display N bytes from memory at i and displayed starting at coordinates (VX, VY)
    void DRW(const Opcode& op);

//// Ex9E - Skip instruction if key with the value of Vx is pressed.
//    void SKP(Opcode in, Cpu *cpu, Input *input) {
//        if (input->IsPressed(cpu->regs[in.x()]) == 1) {
//            cpu->pc += 2;
//        }
//    }
//
//// ExA1 - Skip instruction if key with the value of Vx is not pressed.
//    void SKNP(Opcode in, Cpu *cpu, Input *input) {
//        if (input->IsPressed(cpu->regs[in.x()]) == 0) {
//            cpu->pc += 2;
//        }
//    }
//
//// Fx07 - Set Vx = delay timer value.
//    void LD_VX_DT(Opcode in, Cpu *cpu) {
//        cpu->regs[in.x()] = cpu->t_delay;
//    }
//
//// Fx0A - Wait for a key press, store the value of the key in Vx.
//    void LD_VX_K(Opcode in, Cpu *cpu, Input *input) {
//        for (auto i = 0; i < 0x0F; ++i) {
//            if (input->IsPressed(i)) {
//                cpu->regs[in.x()] = i;
//            }
//        }
//    }
//
//// Fx15 - Set delay timer = Vx.
//    void LD_DT(Opcode in, Cpu *cpu) {
//        cpu->t_delay = cpu->regs[in.x()];
//    }
//
//// Fx18 - Set sound timer = Vx.
//    void LD_ST(Opcode in, Cpu *cpu) {
//        cpu->t_sound = cpu->regs[in.x()];
//    }
//
//// Fx1E - Set I = I + Vx.
//    void ADD_I_VX(Opcode in, Cpu *cpu) {
//        cpu->I += cpu->regs[in.x()];
//    }
//
//// Fx29 - Set I = location of sprite for digit Vx.
//    void LD_F_VX(Opcode in, Cpu *cpu) {
//        // Sprites start at 0x00 and the size of each sprite is 5 bytes
//        cpu->I = cpu->regs[in.x()] * 0x05;
//    }
//
//// Fx33 - Store BCD representation of Vx in memory locations I, I+1, and I+2.
//    void LD_B_VX(Opcode in, Cpu *cpu, Memory *memory) {
//        auto& ram = *memory;
//        ram[cpu->I] = cpu->regs[in.x()] / 100;
//        ram[cpu->I + 1] = (cpu->regs[in.x()] / 10) % 10;
//        ram[cpu->I + 2] = cpu->regs[in.x()] % 10;
//    }
//
//// Fx55 - Store regs V0 through Vx in memory starting at location I.
//    void LD_I_VX(Opcode in, Cpu *cpu, Memory *memory) {
//        auto& ram = *memory;
//        for (uint8_t i = 0; i <= in.x(); ++i) {
//            ram[cpu->I + i] = cpu->regs[i];
//        }
//    }
//
//// Fx65 - Read regs V0 through Vx from memory starting at location I.
//    void LD_VX_I(Opcode in, Cpu *cpu, Memory *memory) {
//        auto& ram = *memory;
//        for (uint8_t i = 0; i <= in.x(); ++i) {
//            cpu->regs[i] = ram[cpu->I + i];
//        }
//
//    public:



};

#endif //CHIP8_CHIP8_H
