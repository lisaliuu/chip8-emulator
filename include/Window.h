/**
 * File name: window.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include "SDL.h"
#include "Display.h"

class Window{
public:
    explicit Window();
    ~Window();
    void render(const uint32_t * pixels);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif //CHIP8_WINDOW_H
