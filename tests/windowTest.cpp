//
// Created by Lisa Liu on 1/1/24.
//
#include "../include/Window.h"
#include <gtest/gtest.h>
#include <SDL.h>
#include <chrono>

namespace {
class WindowTest : public ::testing::Test {};

TEST_F(WindowTest, TestInit) {
  int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
  EXPECT_EQ(sdlInitResult, 0);
  SDL_Quit();
}

TEST_F(WindowTest, TestSDLFunctions) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("\nThere is a error:%s\n", SDL_GetError());
  }
  SDL_Window *window;
  window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    printf("\nerror is %s\n", SDL_GetError());
  }
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  SDL_FillRect(surface, nullptr,
               SDL_MapRGBA(surface->format, 0x00, 0xFF, 0x00, 1));
  SDL_UpdateWindowSurface(window);

  SDL_bool quit = SDL_FALSE;
  auto start = std::chrono::steady_clock::now();
  while (!quit) {
    if (std::chrono::steady_clock::now() - start > std::chrono::seconds(3)) {
      break;
    }
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

TEST_F(WindowTest, TestWindowAndDisplay) {
  Window window = Window();
  Display d = Display();

  auto start = std::chrono::steady_clock::now();
  bool quit = false;
  while (!quit) {
    if (std::chrono::steady_clock::now() - start > std::chrono::seconds(3)) {
      break;
    }
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      for (int i = 0; i < Display::WIDTH * Display::HEIGHT; ++i) {
        d.getDisplay()[i] = (std::rand() % 2 == 0) ? 0x00 : 0xffffffff;
      }
      window.render(d.getDisplay());
      SDL_Delay(1000);
      if (e.type == SDL_QUIT) {
        quit = SDL_TRUE;
      }
    }
  }
  SDL_Quit();
}
} // namespace