//
// Created by Lisa Liu on 1/1/24.
//
#include <gtest/gtest.h>
#include "Window.h"

namespace {
    class WindowTest : public ::testing::Test { };

    // Testing SDL connectivity
    TEST_F(WindowTest, TestInit) {
        int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
        EXPECT_EQ(sdlInitResult, 0);
        SDL_Quit();
    }

    TEST_F(WindowTest, TestBlackScreen) {
        // insert code here...
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("\nThere is a error:%s\n", SDL_GetError());
        }
        SDL_Window *window;
        window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("\nerror is %s\n", SDL_GetError());
        }
        SDL_Surface *surface = SDL_GetWindowSurface(window);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0x00, 0xFF, 0x00, 1));
        SDL_UpdateWindowSurface(window);

        SDL_bool quit = SDL_FALSE;
        while (!quit) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = SDL_TRUE;
                }
            }
        }
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

//    TEST_F(WindowTest, TestRandomScreen) {
//        Window window = Window();
//        Display d;
//        bool quit = false;
//        while (!quit) {
//            SDL_Event e;
//            while (SDL_PollEvent(&e)) {
//                for (int i = 0; i < Display::WIDTH * Display::HEIGHT; ++i){
//                    d.getDisplay()[i] = (std::rand() % 2 == 0) ? 0x00 : 0xffffffff;
//                }
//                window.render(d.getDisplay());
//                SDL_Delay(1000);
//                if (e.type == SDL_QUIT) {
//                    quit = SDL_TRUE;
//                }
//            }
//        }
//    }
}