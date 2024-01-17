/**
 * File name: Window.cpp
 * Author: Lisa (Chuci) Liu
 */

#include <iostream>
#include "Window.h"

Window::Window(){
    std::cout<<"Initializing SDL video..."<<std::endl;
    SDL_Init(SDL_INIT_VIDEO);

    std::cout<<"Initializing SDL window and renderer..."<<std::endl;
    window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              20*Display::WIDTH,20*Display::HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_UNKNOWN,
                                SDL_TEXTUREACCESS_STREAMING,
                                Display::WIDTH, Display::HEIGHT);
}

Window::~Window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::render(const uint32_t * pixels){
    // Clear screen
    SDL_RenderClear(renderer);

    // Configure texture and render
    SDL_UpdateTexture(texture, nullptr, pixels, sizeof(uint32_t) * 64);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // Render to screen
    SDL_RenderPresent(renderer);
}