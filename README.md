# Chip8 Emulator

Chip8 emulator written in C++.


### To Run
```bash
git clone https://github.com/lisaliuu/chip8-emulator
cd chip8-emulator
mkdir build
cd build
cmake ..
make
cd ..
cd bin
./Chip8 tetris.ch8 600
```
*Ensure ROM exists in `roms/`*

### Package Dependencies
- **SDL2**: Used for displaying Chip8 graphics and mapping and gathering keyboard input
- **GoogleTest**: Used for runing unit tests

### Helpful Resources:
#### Guides:
- https://en.wikipedia.org/wiki/CHIP-8
- https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#make-your-own-chip-8-game
- https://austinmorlan.com/posts/chip8_emulator/

#### Reference Repositories:
- https://github.com/shlomnissan/chip8/tree/main
- https://github.com/berkkirtay/berk-8/tree/main

### ROMs Source
- [test_opcode](https://github.com/corax89/chip8-test-rom)
- [IBM_Logo.ch8](https://github.com/loktar00/chip8/blob/master/roms/IBM%20Logo.ch8)
- [pong.ch8](https://github.com/loktar00/chip8/blob/master/roms/Pong%20(alt).ch8)
- [snake.ch8](https://johnearnest.github.io/chip8Archive/play.html?p=snake)
- [space_invaders.ch8](https://github.com/loktar00/chip8/blob/master/roms/Space%20Invaders%20%5BDavid%20Winter%5D.ch8)
- [tetris.ch8](https://github.com/loktar00/chip8/blob/master/roms/Tetris%20%5BFran%20Dachille%2C%201991%5D.ch8)

### MIT License
```
Copyright (c) 2023 Lisa Liu

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```