/**
 * File name: window.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include <SDL.h>
#include "core/display.h"

class Window{
public:
    explicit Window();
    ~Window();
    void render(const uint32_t * pixels);
    void getKeyboardInput();
    bool isRunning();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    bool running;
};

#endif //CHIP8_WINDOW_H
