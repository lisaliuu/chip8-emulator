/**
 * File name: Chip8.cpp
 * Author: Lisa (Chuci) Liu
 */

#include "Chip8.h"

Cpu::Cpu()
    : pc(Memory::ROM_START_ADDRESS), i(0), delayTimer(0),
      prevTickTime(std::chrono::steady_clock::now()) {}

Chip8::Chip8() : display(Display()), cpu(Cpu()), memory(Memory()) {}

void Chip8::loadProgram(const std::string &filePath) {
  return memory.loadProgram(filePath);
}

void Chip8::handleTime(int frameRate) {
  // 60 Hz = 0.0167 seconds = 16.7 ms
  int8_t timeElapsed = static_cast<int8_t>(
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::steady_clock::now() - cpu.prevTickTime)
          .count());
  if (timeElapsed > 16.7) {
    cpu.prevTickTime = std::chrono::steady_clock::now();
    if (cpu.delayTimer > 0) {
      cpu.delayTimer -= 1;
    }
  }
  std::this_thread::sleep_for(
      std::chrono::microseconds(int(1.0 / frameRate * 1000 * 1000)));
}

void Chip8::cycle(const Keypad &k) {
  // fetch
  uint16_t instr = memory.getMemory()[cpu.pc] << 8 | memory.getMemory()[cpu.pc + 1];
  cpu.pc += 2;

  // decode
  Opcode op = Opcode(instr);

  // execute
  runInstruction(op, k);
}

uint32_t *Chip8::getDisplay() { return display.getDisplay(); }

void Chip8::runInstruction(const Opcode &instr, const Keypad &k) {
  instrCount[instr.toString()] += 1;
  switch (instr.getHigh()) {
  case 0x0000:
    switch (instr.getNN()) {
    case 0x00E0:
      CLS();
      break;
    case 0x00EE:
      RET();
      break;
    default:
      exitProgramWithError(instr);
      break;
    }
    break;

  case 0x1000:
    JMP(instr);
    break;

  case 0x2000:
    CALL(instr);
    break;

  case 0x3000:
    SE_VX_NN(instr);
    break;

  case 0x4000:
    SNE_VX_NN(instr);
    break;

  case 0x5000:
    SE_VX_VY(instr);
    break;

  case 0x6000:
    LD_VX_NN(instr);
    break;

  case 0x7000:
    ADD_VX_NN(instr);
    break;

  case 0x8000:
    switch (instr.getN()) {
    case 0x0000:
      LD_VX_VY(instr);
      break;
    case 0x0001:
      OR_VX_VY(instr);
      break;
    case 0x0002:
      AND_VX_VY(instr);
      break;
    case 0x0003:
      XOR_VX_VY(instr);
      break;
    case 0x0004:
      ADD_VX_VY(instr);
      break;
    case 0x0005:
      SUB_VX_VY(instr);
      break;
    case 0x0006:
      SHR_VX(instr);
      break;
    case 0x0007:
      SUBN_VX_VY(instr);
      break;
    case 0x000E:
      SHL_VX(instr);
      break;
    default:
      exitProgramWithError(instr);
      break;
    }
    break;

  case 0x9000:
    SNE_VX_VY(instr);
    break;

  case 0xA000:
    LD_I(instr);
    break;

  case 0xB000:
    JP_V0(instr);
    break;

  case 0xC000:
    RND(instr);
    break;

  case 0xD000:
    DRW(instr);
    break;

  case 0xE000:
    switch (instr.getNN()) {
    case 0x009E:
      SKP(instr, k);
      break;
    case 0x00A1:
      SKNP(instr, k);
      break;
    default:
      exitProgramWithError(instr);
      break;
    }
    break;

  case 0xF000:
    switch (instr.getNN()) {
    case 0x0007:
      LD_VX_DT(instr);
      break;
    case 0x000A:
      LD_VX_K(instr, k);
      break;
    case 0x0015:
      LD_DT(instr);
      break;
    case 0x0018:
      LD_ST(instr);
      break;
    case 0x001E:
      ADD_I_VX(instr);
      break;
    case 0x0029:
      LD_F_VX(instr);
      break;
    case 0x0033:
      LD_B_VX(instr);
      break;
    case 0x0055:
      LD_I_VX(instr);
      break;
    case 0x0065:
      LD_VX_I(instr);
      break;
    default:
      exitProgramWithError(instr);
      break;
    }
    break;
  default:
    exitProgramWithError(instr);
    break;
  }
}

void Chip8::printInstrCount() const {
  std::cout << "Contents of instruction count map: " << std::endl;
  for (const auto& ic : instrCount) {
    std::cout << ic.first << " was called " << ic.second << " times"
              << std::endl;
  }
}

void Chip8::exitProgramWithError(const Opcode &instr) {
  instr.reportInvalidInstr();
  printInstrCount();
  exit(EXIT_FAILURE);
}

void Chip8::CLS() { display.clearScreen(); }

void Chip8::RET() {
  cpu.pc = cpu.stack.top();
  cpu.stack.pop();
}

void Chip8::JMP(const Opcode &op) { cpu.pc = op.getNNN(); }

void Chip8::CALL(const Opcode &op) {
  cpu.stack.push(cpu.pc);
  cpu.pc = op.getNNN();
}

void Chip8::SE_VX_NN(const Opcode &op) {
  if (cpu.registers[op.getX()] == op.getNN()) {
    cpu.pc += 2;
  }
}

void Chip8::SNE_VX_NN(const Opcode &op) {
  if (cpu.registers[op.getX()] != op.getNN()) {
    cpu.pc += 2;
  }
}

void Chip8::SE_VX_VY(const Opcode &op) {
  if (cpu.registers[op.getX()] == cpu.registers[op.getY()]) {
    cpu.pc += 2;
  }
}

void Chip8::LD_VX_NN(const Opcode &op) {
  cpu.registers[op.getX()] = op.getNN();
}

void Chip8::ADD_VX_NN(const Opcode &op) {
  cpu.registers[op.getX()] += op.getNN();
}

void Chip8::LD_VX_VY(const Opcode &op) {
  cpu.registers[op.getX()] = cpu.registers[op.getY()];
}

void Chip8::OR_VX_VY(const Opcode &op) {
  cpu.registers[op.getX()] |= cpu.registers[op.getY()];
}

void Chip8::AND_VX_VY(const Opcode &op) {
  cpu.registers[op.getX()] &= cpu.registers[op.getY()];
}

void Chip8::XOR_VX_VY(const Opcode &op) {
  cpu.registers[op.getX()] ^= cpu.registers[op.getY()];
}

void Chip8::ADD_VX_VY(const Opcode &op) {
  uint16_t sum = cpu.registers[op.getX()] + cpu.registers[op.getY()];
  if (sum > 0xFF) {
    // overflow
    cpu.registers[0xF] = 1;
  } else {
    cpu.registers[0xF] = 0;
  }
  cpu.registers[op.getX()] = sum & 0xFF;
}

void Chip8::SUB_VX_VY(const Opcode &op) {
  if (cpu.registers[op.getX()] <= cpu.registers[op.getY()]) {
    // underflow
    cpu.registers[0xF] = 0;
  } else {
    cpu.registers[0xF] = 1;
  }
  cpu.registers[op.getX()] -= cpu.registers[op.getY()];
}

void Chip8::SHR_VX(const Opcode &op) {
  cpu.registers[0xF] = (cpu.registers[op.getX()] & 1);
  cpu.registers[op.getX()] = cpu.registers[op.getX()] >> 1;
}

void Chip8::SUBN_VX_VY(const Opcode &op) {
  if (cpu.registers[op.getX()] >= cpu.registers[op.getY()]) {
    // underflow
    cpu.registers[0xF] = 0;
  } else {
    cpu.registers[0xF] = 1;
  }
  cpu.registers[op.getX()] =
      cpu.registers[op.getY()] - cpu.registers[op.getX()];
}

void Chip8::SHL_VX(const Opcode &op) {
  cpu.registers[0xF] = (cpu.registers[op.getX()] >> 7);
  cpu.registers[op.getX()] = cpu.registers[op.getX()] << 1;
}

void Chip8::SNE_VX_VY(const Opcode &op) {
  if (cpu.registers[op.getX()] != cpu.registers[op.getY()]) {
    cpu.pc += 2;
  }
}

void Chip8::LD_I(const Opcode &op) { cpu.i = op.getNNN(); }

void Chip8::JP_V0(const Opcode &op) {
  cpu.pc = cpu.registers[0x0] + op.getNNN();
}

void Chip8::RND(const Opcode &op) {
  cpu.registers[op.getX()] = op.getNN() & (std::rand() % 0xFF);
}

void Chip8::DRW(const Opcode &op) {
  cpu.registers[0xF] = 0;
  for (auto y = 0; y < op.getN(); ++y) {
    uint8_t spriteVal = memory[cpu.i + y];
    // draw bits from most to least significant
    for (int x = 0; x < 8; ++x) {
      // calculate index in display
      uint16_t px = (cpu.registers[op.getX()] + x) % Display::WIDTH;
      uint16_t py =
          ((cpu.registers[op.getY()] + y) % Display::HEIGHT) * Display::WIDTH;
      uint16_t p = px + py;
      if (spriteVal & (0b10000000 >> x)) {
        if (display[p]) {
          cpu.registers[0xF] = 1;
        }
        display[p] = ~display[p];
      }
    }
  }
}

void Chip8::SKP(const Opcode &op, const Keypad &k) {
  if (k.keys[cpu.registers[op.getX()]] == Keypad::KEY_DOWN) {
    cpu.pc += 2;
  }
}

void Chip8::SKNP(const Opcode &op, const Keypad &k) {
  if (k.keys[cpu.registers[op.getX()]] == Keypad::KEY_UP) {
    cpu.pc += 2;
  }
}

void Chip8::LD_VX_DT(const Opcode &op) {
  cpu.registers[op.getX()] = cpu.delayTimer;
}

void Chip8::LD_VX_K(const Opcode &op, const Keypad &k) {
  bool keyPressed = false;
  k.printKeys();
  for (auto key : k.keys) {
    if (key == Keypad::KEY_DOWN) {
      keyPressed = true;
      break;
    }
  }
  if (!keyPressed) {
    cpu.pc -= 2; // blocking
  }
}

void Chip8::LD_DT(const Opcode &op) {
  cpu.delayTimer = cpu.registers[op.getX()];
}

void Chip8::LD_ST(const Opcode &op) {}

void Chip8::ADD_I_VX(const Opcode &op) { cpu.i += cpu.registers[op.getX()]; }

void Chip8::LD_F_VX(const Opcode &op) {
  cpu.i = (cpu.registers[op.getX()] & 0XF) * 5;
}

void Chip8::LD_B_VX(const Opcode &op) {
  uint16_t num = op.getX();
  memory[cpu.i + 2] = num % 10;
  num /= 10;
  memory[cpu.i + 1] = num % 10;
  num /= 10;
  memory[cpu.i] = num % 10;
}

void Chip8::LD_I_VX(const Opcode &op) {
  for (uint16_t regIn = 0; regIn <= op.getX(); ++regIn) {
    memory[cpu.i + regIn] = cpu.registers[regIn];
  }
}

void Chip8::LD_VX_I(const Opcode &op) {
  for (uint16_t regIn = 0; regIn <= op.getX(); ++regIn) {
    cpu.registers[regIn] = memory[cpu.i + regIn];
  }
}