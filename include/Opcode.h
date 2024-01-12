//
// Created by Lisa Liu on 1/6/24.
//

#ifndef CHIP8_OPCODE_H
#define CHIP8_OPCODE_H

#include <sstream>
#include <cstdint>
#include <iostream>


/**
 * @struct Opcode
 * @brief  This struct represents a Chip8 opcode with accessor methods for decoding
 *         the opcode.
 */
class Opcode {
public:
    // Constr
    Opcode(uint16_t inOp);

    // Accesses the second nibble, X in register VX.
    uint16_t getX() const;

    // Accesses the third nibble, Y in register VY.
    uint16_t getY() const;

    // Accesses the fourth nibble.
    uint16_t getN() const; // fourth nibble

    // Accesses the third and fourth nibble.
    uint16_t getNN() const;

    // Accesses the second, third, and fourth nibble.
    uint16_t getNNN() const;

    // Accesses the first nibble.
    uint16_t getHigh() const;

    void reportInvalidInstr() const;

    void printInstr() const;

    friend class Chip8;

private:
    uint16_t opcode;

    std::string toString() const;


};


#endif //CHIP8_OPCODE_H
