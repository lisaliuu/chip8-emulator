/**
 * File name: memory.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "memory.h"
#include <iostream>
#include <fstream>
#include <sstream>

Memory::Memory() {
    // clear memory
    memoryArr.fill(0);

    // load fonts into memory location 0x0050 - 0x009f
    std::copy(begin(fonts), end(fonts),
              begin(memoryArr)+FONT_START_ADDRESS);
}

bool Memory::loadProgram(const std::string& filePath) {
    try{
        std::cout<<filePath;
        // attempt to open file as binary for reading
        std::ifstream file (filePath, std::ios::binary);

        // get file size
        file.seekg(0, file.end);
        long long fileLen = file.tellg();
        file.seekg(0, file.beg);

        // check file size
        if(fileLen<=0 || fileLen > MAX_ROM_SIZE){
            std::cout<<"File is empty or of invalid file.";
            return false;
        }

        // extract from file stream string
        std::ostringstream ss;
        ss << file.rdbuf();
        std::string contents = ss.str();

        // load program
        std::copy(begin(contents), end(contents),
                  begin(memoryArr)+ROM_START_ADDRESS);
    }
    catch (const std::ifstream::failure& e){
        std::cout<<"Failed to open ROM file.";
        return false;
    }

    return true;
}

uint8_t Memory::operator[](int index){
    return memoryArr[index];
}