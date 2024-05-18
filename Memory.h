#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <array>
#include "PPU.h"

class Memory
{
public:
    Memory(PPU &ppu);
    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t value);

private:
    std::array<uint8_t, 0x10000> data; // 64KB of memory
    PPU &ppu;
};

#endif // MEMORY_H
