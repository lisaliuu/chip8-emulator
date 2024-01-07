/**
 * File name: display.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <array>

//class Chip8;

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

    Display();

    const uint32_t& operator[] (int index) const;

    uint32_t& operator[] (int index);

    // Fills display array with 0
    void clearScreen();

    friend class Chip8;

private:
    // Array representing the Chip8 display where each element is a pixel.
    uint32_t displayArr [WIDTH * HEIGHT];
};
#endif //CHIP8_DISPLAY_H
