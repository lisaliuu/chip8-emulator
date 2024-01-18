#include <SDL.h>
#include <iostream>
#include "Chip8.h"
#include "Window.h"

std::pair<std::string, int> parseArgs(int argc, const char * argv[]);

int main(int argc, const char * argv[]) {

    // Initialize Chip8 emulator
    std::pair<std::string, int> parsedArgs = parseArgs(argc, argv);
    Chip8 c8 = Chip8();
    std::cout<<parsedArgs.first<<" "<<std::to_string(parsedArgs.second)<<std::endl;

    // Load ROM
    c8.loadProgram(parsedArgs.first);

    // Initialize platform
    Window w = Window();
    Keypad k = Keypad();

    // Initialize event handler for keyboard
    EventHandler e = EventHandler();

    // Main loop
    while(true){
        e.handleEvent(k); // Poll keyboard event
        c8.cycle(k); // Fetch, decode, execute
        c8.handleTime(parsedArgs.second); // Process delay timer
        w.render(c8.getDisplay()); // Render to SDL
    }
}

std::pair<std::string, int> parseArgs(int argc, const char * argv[]){
    if (argc!=3){
        std::cout<<"[ERROR] Command error. Usage: "<<argv[0]<<" <ROM-filename> <frame-rate"
                                                              "(400-800)>"<<std::endl;
        exit(EXIT_FAILURE);
    }
    int inputFrameRate = std::stoi(argv[2]);
    if (inputFrameRate<0){
        std::cerr<<"[ERROR] Command error. Please input a positive frame rate";
        exit(EXIT_FAILURE);
    }
    if (inputFrameRate<400 || inputFrameRate>800){
        std::cerr<<"[WARNING] Suggested frame rate between 400-800 Hz";
    }
    return {argv[1], inputFrameRate};
}