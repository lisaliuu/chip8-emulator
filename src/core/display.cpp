/**
 * File name: display.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "core/display.h"

const uint8_t& Display::operator[] (int index) const{
    return displayArr.at(index);
}

uint8_t& Display::operator[] (int index){
    return const_cast<uint8_t&>
        (const_cast<const std::array<uint8_t, WIDTH*HEIGHT>&>(this->displayArr)[index]);
}


void Display::clearScreen(){
    displayArr.fill(0);
}