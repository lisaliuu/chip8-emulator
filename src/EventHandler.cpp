//
// Created by Lisa Liu on 1/6/24.
//

#include "EventHandler.h"

Keypad::Keypad(){
    std::fill(std::begin(keys), std::end(keys), KEY_UP);
}

void Keypad::printKeys() const{
    std::cout<<"Key values: ";
    for(auto v:keys){
        if (v==Keypad::KEY_UP){
            std::cout<<"U ";
        }
        else{
            std::cout<<"D ";
        }
    }
    std::cout<<std::endl;
}

void EventHandler::handleEvent(Keypad& k){
    while(SDL_PollEvent(&event)==1){
        switch (event.type) {
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                SDL_Scancode sc = event.key.keysym.scancode;
                if(k.keyMap.find(sc)!=k.keyMap.end()) {
                    k.keys[k.keyMap[sc]] = event.type==SDL_KEYUP ? Keypad::KEY_UP:Keypad::KEY_DOWN;
                }
                break;
        }
    }
}