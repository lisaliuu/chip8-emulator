
#include <SDL.h>
#include <iostream>
#include "Chip8.h"
#include "Window.h"

std::pair<std::string, int> parseArgs(int argc, const char * argv[]);

int main(int argc, const char * argv[]) {
    // Initialize Chip8 emulator
    std::pair<std::string, int> parsedArgs = parseArgs(argc, argv);
    Chip8 c8 = Chip8();

    // Load ROM
    c8.loadProgram(parsedArgs.first);

    // Initialize platform
    Window w = Window();

    // Main loop: fetch, decode, execute
    while(w.isRunning()){
        c8.cycle();
        c8.handleTime(parsedArgs.second);
    }

    return 0;
}

std::pair<std::string, int> parseArgs(int argc, const char * argv[]){
    if (argc!=3){
        std::cout<<"[ERROR] Command error. Usage: "<<argv[0]<<" <ROM-path> <frame-rate(400-800)>"
                                                                 <<std::endl;
        exit(EXIT_FAILURE);
    }
    int inputFrameRate = std::stoi(argv[2]);
    if (inputFrameRate<0){
        std::cout<<"[ERROR] Command error. Please input a positive frame rate";
        exit(EXIT_FAILURE);
    }
    if (inputFrameRate<400 || inputFrameRate>800){
        std::cout<<"[WARNING] Suggested frame rate between 400-800 Hz";
    }
    return {argv[1], inputFrameRate};
}