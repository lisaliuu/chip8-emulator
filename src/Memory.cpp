/**
 * File name: Memory.cpp
 * Author: Lisa (Chuci) Liu
 */
#include "../include/Memory.h"

Memory::Memory() {
    // load fonts into memory location 0x0050 - 0x009f
    std::copy(begin(fonts), end(fonts),
              begin(memoryArr)+FONT_START_ADDRESS);
}

bool Memory::loadProgram(std::string filePath) {
    try{
        // attempt to open file as binary for reading
        std::ifstream file (filePath, std::ios::binary);

        // get file size
        file.seekg(0, file.end);
        size_t fileLen = file.tellg();
        file.seekg(0, file.beg);

        // check file size
        if(fileLen==0 || fileLen > MAX_ROM_SIZE){
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