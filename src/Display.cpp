/**
 * File name: Display.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "Display.h"
Display::Display() {
    clearScreen();
}

const uint32_t &Display::operator[](int index) const {
  return displayArr[index];
}

uint32_t &Display::operator[](int index) {
  return const_cast<uint32_t &>(
      const_cast<const uint32_t *>(this->displayArr)[index]);
}

void Display::clearScreen() {
    std::fill(std::begin(displayArr), std::end(displayArr), 0);
}

uint32_t *Display::getDisplay() { return displayArr; }