#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "Memory.h"

class CPU {
public:
    CPU(Memory& memory);
    void reset();
    void executeInstruction();
private:
    uint16_t pc; // Program counter
    uint8_t sp;  // Stack pointer
    uint8_t a;   // Accumulator
    uint8_t x;   // X register
    uint8_t y;   // Y register
    uint8_t status; // Status register

    Memory& memory;

    void LDA(uint16_t address);
    void TAX();
    void INX();
    void BRK();
    // Add more instruction methods here...

    void setFlag(uint8_t flag, bool value);
    bool getFlag(uint8_t flag);
};

#endif // CPU_H
