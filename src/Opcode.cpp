/**
 * File name: Opcode.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "Opcode.h"

Opcode::Opcode(uint16_t inOp):opcode(inOp) {}

uint16_t Opcode::getX() const {
    return (opcode & (0x0F00)) >> 8;
}

uint16_t Opcode::getY() const {
    return (opcode & (0x00F0)) >> 4;
}

uint16_t Opcode::getN() const {
    return (opcode & (0x000F));
}

uint16_t Opcode::getNN() const {
    return (opcode & (0x00FF));
}

uint16_t Opcode::getNNN() const {
    return (opcode & (0x0FFF));
}

uint16_t Opcode::getHigh() const {
    return (opcode & (0xF000));
}

std::string Opcode::toString() const {
    std::stringstream ss;
    ss<< std::hex << opcode;
    return ss.str();
}

void Opcode::reportInvalidInstr() const{
    std::cerr<<"Invalid instruction: "<< toString()<<std::endl;
}

void Opcode::printInstr() const{
    std::cout<<toString()<<std::endl;
}
