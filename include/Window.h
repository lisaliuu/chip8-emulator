/**
 * File name: Window.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include "SDL.h"
#include "Display.h"


/**
 * @class Window
 * @brief  Window class that utilizes the SDL library to render the Chip8 display.
 */
class Window{
public:
    // Initializes SDL video of size 32 * 64 with window, render, and texture objects
    Window();

    // Destroys window and texture objects and terminates the SDL system
    ~Window();

    // Renders pixels of size 32 * 64 onto the SDL video
    void render(const uint32_t * pixels);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif //CHIP8_WINDOW_H
