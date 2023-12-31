/**
 * File name: chip8.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "Chip8.h"

Cpu::Cpu(): pc(Memory::ROM_START_ADDRESS), i(0), delayTimer(0),
                prevTickTime(std::chrono::steady_clock::now()){

}

Chip8::Chip8(): display(Display()), cpu(Cpu()), memory(Memory()){

}

void Chip8::loadProgram(const std::string& filePath){
    return memory.loadProgram(filePath);
}

uint32_t* Chip8::getDisplay(){
    return display.displayArr;
}

void Chip8::incrementPC() {
    cpu.pc+=2;
}

void Chip8::runInstruction(Opcode instr){
    switch(instr.getHigh()){
        case 0x0000:
            switch(instr.getNN()){
                case 0x00E0:
                    break;
                case 0x00EE:
                    break;
                default:
                    instr.reportInvalidInstr();
                    break;
            }

        case 0x1000:
            break;
        case 0x2000:
            break;
        case 0x3000:
            break;
        case 0x4000:
            break;
        case 0x5000:
            break;
        case 0x6000:
            break;
        case 0x7000:
            break;
        case 0x8000:
            switch(instr.getN()){
                case 0x0001:
                    break;
                case 0x0002:
                    break;
                case 0x0003:
                    break;
                case 0x0004:
                    break;
                case 0x0005:
                    break;
                case 0x0006:
                    break;
                default:
                    instr.reportInvalidInstr();
                    break;
            }

            case 0x9000:
                break;

            case 0xA000:
                break;

            case 0xB000:
                break;

            case 0xC000:
                break;

            case 0xD000:
                break;

            case 0xE000:
                switch(instr.getNN()){
                    case 0x009E:
                        break;
                    case 0x00A1:
                        break;
                    default:
                        instr.reportInvalidInstr();
                        break;
                }
                break;

            case 0xF000:
                switch(instr.getNN()){
                    case 0x0007:
                        break;
                    case 0x0015:
                        break;
                    case 0x0018:
                        break;
                    case 0x001E:
                        break;
                    case 0x000A:
                        break;
                    case 0x0029:
                        break;
                    case 0x0033:
                        break;
                    case 0x0055:
                        break;
                    case 0x0065:
                        break;
                    default:
                        instr.reportInvalidInstr();
                        break;
                }
                default:
                    instr.reportInvalidInstr();
                    break;
    }
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
    uint16_t instr = memory.memoryArr[cpu.pc]<<8 | memory.memoryArr[cpu.pc+1];
    incrementPC();

    // decode + execute
    Opcode op = Opcode(instr);

    // execute
    runInstruction(op);
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