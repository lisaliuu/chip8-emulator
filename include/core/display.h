/**
 * File name: display.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <array>

/**
 * @class Display
 * @brief This class represents the display of the Chip8 as a 64*32 array where.
 *        each element is a pixel.
 */
class Display {
public:
    // Width of display
    static const unsigned int WIDTH = 64;

    // Height of display
    static const unsigned int HEIGHT = 32;

    // Const subscript operator to get specified pixel in the display - checks bound.
    const uint8_t& operator[](int index) const;

    // Subscript operator to get specified pixel in the display - checks bound.
    uint8_t& operator[](int index);

    // Fills display array with 0
    void clearScreen();

private:
    // Array representing the Chip8 display where each element is a pixel.
    std::array<uint8_t, WIDTH*HEIGHT> displayArr;
};
#endif //CHIP8_DISPLAY_H
