/**
 * File name: Opcode.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_OPCODE_H
#define CHIP8_OPCODE_H

#include <sstream>
#include <cstdint>
#include <iostream>


/**
 * @class Opcode
 * @brief  Opcode class with accessor methods for decoding parts of the
 *         opcode and logging.
 */
class Opcode {
public:
    // Sets the class' opcode to the inputted opcode
    Opcode(uint16_t inOp);

    // Returns the second nibble, X in register VX
    uint16_t getX() const;

    // Returns the third nibble, Y in register VY
    uint16_t getY() const;

    // Returns the fourth nibble
    uint16_t getN() const;

    // Returns the third and fourth nibble
    uint16_t getNN() const;

    // Returns the second, third, and fourth nibble
    uint16_t getNNN() const;

    // Returns the first nibble
    uint16_t getHigh() const;

    // Prints the invalid opcode encountered
    void reportInvalidInstr() const;

    // Prints the opcode
    void printInstr() const;

    friend class Chip8;

private:
    uint16_t opcode;

    // Returns the opcode in its string representation
    std::string toString() const;
};


#endif //CHIP8_OPCODE_H
