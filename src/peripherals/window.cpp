/**
 * File name: window.cpp
 * Author: Lisa (Chuci) Liu
 */
#include <iostream>
#include "peripherals/window.h"

Window::Window(uint8_t scale){
    std::cout<<"Initializing SDL video and audio...";
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    std::cout<<"Initializing SDL window and renderer...";
    window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              scale*Display::WIDTH,scale*Display::HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_UNKNOWN,
                                SDL_TEXTUREACCESS_STREAMING,
                                64, 32);

    SDL_SetTextureColorMod(texture, 255, 255, 255);
    running = true;
}

Window::~Window(){
    std::cout<<"Shutting down SDL video and audio...";
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    std::cout<<"Quitting SDL subsystems";
    SDL_Quit();
}

void Window::render(const uint32_t * pixels){
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Configure texture and render
    SDL_UpdateTexture(texture, nullptr, pixels, sizeof(uint32_t) * 64);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // Render to screen
    SDL_RenderPresent(renderer);
}

void Window::getKeyboardInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:

                break;
            case SDL_KEYUP:
                break;
        }
    }
}

