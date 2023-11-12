/**
 * File name: display.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <array>

class Display {
private:
    static const unsigned int WIDTH = 64;
    static const unsigned int HEIGHT = 32;
    std::array<uint8_t, WIDTH*HEIGHT> displayArr;
public:
    void draw();
    void clearScreen();
};
#endif //CHIP8_DISPLAY_H
