/**
 * File name: memory.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "Memory.h"
#include <iostream>
#include <fstream>
#include <sstream>

Memory::Memory() {
    // Clear memory
    memoryArr.fill(0);

    // Load fonts into memory location 0x0050 - 0x009f
    std::copy(begin(fonts), end(fonts),
              begin(memoryArr)+FONT_START_ADDRESS);
}

void Memory::loadProgram(const std::string& filePath) {
    try{
        std::cout<<filePath;
        // Attempt to open ROM file as binary
        std::ifstream file (filePath, std::ios::binary);

        // Get file size
        file.seekg(0, file.end);
        long long fileLen = file.tellg();
        file.seekg(0, file.beg);

        // Check file size
        if(fileLen<=0 || fileLen > MAX_ROM_SIZE){
            std::cout<<"Failed to load ROM program. File is empty or invalid.";
            exit(EXIT_FAILURE);
        }

        // Extract from file stream string
        std::ostringstream ss;
        ss << file.rdbuf();
        std::string contents = ss.str();

        // Load program
        std::copy(begin(contents), end(contents),
                  begin(memoryArr)+ROM_START_ADDRESS);
    }
    catch (const std::ifstream::failure& e){
        std::cout<<"Failed to open ROM file.";
        exit(EXIT_FAILURE);
    }
    
}

uint8_t& Memory::operator[] (int index){
    return const_cast<uint8_t&>
    (const_cast<const std::array<uint8_t, MEM_SIZE> &>(this->memoryArr)[index]);
}

const uint8_t& Memory::operator[] (int index) const{
    return memoryArr.at(index);
}