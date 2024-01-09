//
// Created by Lisa Liu on 1/6/24.
//

#ifndef CHIP8_EVENTHANDLER_H
#define CHIP8_EVENTHANDLER_H

#include <SDL.h>
#include <unordered_map>

struct Keypad{
    enum keyState
    {
        KEY_UP,
        KEY_DOWN
    };

    std::unordered_map<SDL_Scancode , uint8_t> keyMap =
            {
                    {SDL_SCANCODE_1, 0x01},
                    {SDL_SCANCODE_2, 0x02},
                    {SDL_SCANCODE_3, 0x03},
                    {SDL_SCANCODE_4, 0x0C},

                    {SDL_SCANCODE_Q, 0x04},
                    {SDL_SCANCODE_W, 0x05},
                    {SDL_SCANCODE_E, 0x06},
                    {SDL_SCANCODE_R, 0x0D},

                    {SDL_SCANCODE_A, 0x07},
                    {SDL_SCANCODE_S, 0x08},
                    {SDL_SCANCODE_D, 0x09},
                    {SDL_SCANCODE_F, 0x0E},

                    {SDL_SCANCODE_Z, 0x0A},
                    {SDL_SCANCODE_X, 0x00},
                    {SDL_SCANCODE_C, 0x0B},
                    {SDL_SCANCODE_V, 0x0F},
            };

    std::array<keyState, 0xF> keys; // key -> keyState
};

class EventHandler {
public:
    void handleEvent(Keypad& k);

private:
    SDL_Event event;
};


#endif //CHIP8_EVENTHANDLER_H
