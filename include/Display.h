/**
 * File name: Display.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <array>

/**
 * @class Display
 * @brief Display class of the Chip8 that is implemented with a 64*32 array where.
 *        each element is a pixel. This class provides access to and information
 *        about the Chip8 display array.
 */
class Display {
public:
    static const unsigned int WIDTH = 64;
    static const unsigned int HEIGHT = 32;

    // Creates display array filled with 0
    Display();

    // Returns a const reference to the pixel stored at specified index in display array
    const uint32_t& operator[] (int index) const;

    // Returns a reference to the pixel stored at specified index in display array
    uint32_t& operator[] (int index);

    // Fills display array with 0
    void clearScreen();

    // Returns display array
    uint32_t* getDisplay();

private:
    uint32_t displayArr [WIDTH * HEIGHT];

};
#endif //CHIP8_DISPLAY_H
