/**
 * File name: Display.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "Display.h"
Display::Display(){
    memset(displayArr, 0, sizeof(displayArr));
}

const uint32_t& Display::operator[] (int index) const{
    return displayArr[index];
}

uint32_t& Display::operator[] (int index){
    return const_cast<uint32_t&>
    (const_cast<const uint32_t*> (this->displayArr)[index]);
}

void Display::clearScreen(){
    memset(displayArr, 0, sizeof(displayArr));
}

uint32_t* Display::getDisplay() {
    return displayArr;
}