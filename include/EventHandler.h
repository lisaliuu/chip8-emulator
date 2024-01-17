/**
 * File name: EventHandler.h
 * Author: Lisa (Chuci) Liu
 */

#ifndef CHIP8_EVENTHANDLER_H
#define CHIP8_EVENTHANDLER_H

#include <SDL.h>
#include <iostream>
#include <unordered_map>

/**
 * @struct Keypad
 * @brief Keypad struct that tracks of the pressing of keys, mapping input keys
 *        with SDL to the original 16 keys on the Chip8. The state of the keys
 *        is maintained in an array.
 */
struct Keypad {
  enum keyState { KEY_UP, KEY_DOWN };

  // Maps the SDL scancode for the user keyboard to the original Chip8 keys
  std::unordered_map<SDL_Scancode, uint8_t> keyMap = {
      {SDL_SCANCODE_1, 0x01}, {SDL_SCANCODE_2, 0x02},
      {SDL_SCANCODE_3, 0x03}, {SDL_SCANCODE_4, 0x0C},

      {SDL_SCANCODE_Q, 0x04}, {SDL_SCANCODE_W, 0x05},
      {SDL_SCANCODE_E, 0x06}, {SDL_SCANCODE_R, 0x0D},

      {SDL_SCANCODE_A, 0x07}, {SDL_SCANCODE_S, 0x08},
      {SDL_SCANCODE_D, 0x09}, {SDL_SCANCODE_F, 0x0E},

      {SDL_SCANCODE_Z, 0x0A}, {SDL_SCANCODE_X, 0x00},
      {SDL_SCANCODE_C, 0x0B}, {SDL_SCANCODE_V, 0x0F},
  };

  // Array where each element is the state (up or down) of the key at that index
  std::array<keyState, 0x10> keys;

  // Initializes all keys to the up state
  Keypad();

  // Prints the state of all the keys
  void printKeys() const;
};

/**
 * @class EventHandler
 * @brief Event Handler class that polls user events, key presses and window
 *        termination, with SDL and updates the keys state array.
 */
class EventHandler {
public:
  // Polls for user input, updating the state of the keypad
  void handleEvent(Keypad &k);

private:
  SDL_Event event;
};

#endif // CHIP8_EVENTHANDLER_H
