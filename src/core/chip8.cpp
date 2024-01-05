/**
 * File name: chip8.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "core/chip8.h"

Cpu::Cpu(): pc(0), i(0), delayTimer(0), prevTickTime(std::chrono::steady_clock::now()){

}
Opcode::Opcode(uint16_t inOp):rawInstr(inOp) {}

uint8_t Opcode::getX() const {
    return (rawInstr & (0x0F00)) >> 8;
}

uint8_t Opcode::getY() const {
    return (rawInstr & (0x00F0)) >> 4;
}

uint8_t Opcode::getN() const {
    return (rawInstr & (0x000F));
}

uint8_t Opcode::getNN() const {
    return (rawInstr & (0x00FF));
}

uint16_t Opcode::getNNN() const {
    return (rawInstr & (0x0FFF));
}

Chip8::Chip8(): display(Display()), cpu(Cpu()), memory(Memory()){

}

void Chip8::loadProgram(const std::string& filePath){
    return memory.loadProgram(filePath);
}

void Chip8::incrementPC() {
    cpu.pc+=2;
}

void Chip8::handleTime(int frameRate){
    // 60 Hz = 	0.0167 seconds = 16.7 ms
    int8_t timeElapsed = static_cast<int8_t>(
            duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() -
                                                     cpu.prevTickTime)
                    .count());
    if (timeElapsed>16.7){
        cpu.prevTickTime = std::chrono::steady_clock::now();
        if(cpu.delayTimer>0){
            cpu.delayTimer-=1;
        }
    }
    // frameRate in Hz = 1/frameRate seconds = 1/frameRate * 1000 * 1000 microseconds
    auto timeInMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::duration<double>(1.0/frameRate * 1000 * 1000)
    );
    std::this_thread::sleep_for(timeInMicroseconds);
}

void Chip8::cycle() {
    // fetch

    // decode

    // execute
}

void Chip8::CLS() {
    display.clearScreen();
}

void Chip8::RET() {
    cpu.stack.pop();
}

void Chip8::JMP(const Opcode& op) {
    cpu.pc = op.getNNN();
}

void Chip8::CALL(const Opcode& op) {
    cpu.stack.push(cpu.pc);
    cpu.pc = op.getNNN();
}

void Chip8::SE_VX_NN(const Opcode& op) {
    if (cpu.registers[op.getX()] == op.getNN()) {
        incrementPC();
    }
}

void Chip8::SNE_VX_NN(const Opcode& op) {
    if (cpu.registers[op.getX()] != op.getNN()) {
        incrementPC();
    }
}

void Chip8::SE_VX_VY(const Opcode& op) {
    if (cpu.registers[op.getX()] == cpu.registers[op.getY()]) {
        incrementPC();
    }
}

void Chip8::LD_VX_NN(const Opcode& op) {
    cpu.registers[op.getX()] = op.getNN();
}

void Chip8::ADD_VX_NN(const Opcode& op) {
    cpu.registers[op.getX()] += op.getNN();
}

void Chip8::LD_I(const Opcode& op) {
    cpu.i = op.getNNN();
}

void Chip8::DRW(const Opcode& op) {
    uint8_t xStart = cpu.registers[op.getX()];
    uint8_t yStart = cpu.registers[op.getY()];
    xStart %= Display::WIDTH;
    yStart %= Display::HEIGHT;
    uint8_t yEnd = yStart+op.getN();
    for(auto y=yStart;y<yEnd;++y){
        cpu.registers[0xF]=0;
        uint8_t drawSpriteVal = memory[cpu.i+y];
        //draw bits from most to least significant
        uint16_t py = yStart+y;
        for(int x=0;x<8;++x){
            if(drawSpriteVal&(0b10000000>>x)){
                uint16_t px = xStart+x;
                uint16_t p = px+py*Display::WIDTH;
                if(display[p]){
                    cpu.registers[0xF]=1;
                }
                display[p]^=1;
            }
        }
    }
}