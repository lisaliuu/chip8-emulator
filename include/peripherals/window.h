/**
 * File name: window.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include <SDL.h>
#include <string_view>

class Window{
public:
    Window(int width, int height, std::string_view title);
    ~Window();
    renderPixel(int x, int y, int scale);
    getKeyboardInput();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif //CHIP8_WINDOW_H
