/**
 * File name: display.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <array>

class Display {
public:
    static const unsigned int WIDTH = 64;
    static const unsigned int HEIGHT = 32;
    uint8_t& operator[](int index);
    const uint8_t& operator[](int index) const;
    void clearScreen();

private:
    std::array<uint8_t, WIDTH*HEIGHT> displayArr;
};
#endif //CHIP8_DISPLAY_H
