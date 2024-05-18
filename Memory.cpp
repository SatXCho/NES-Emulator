#include "Memory.h"

Memory::Memory(PPU &ppu) : ppu(ppu)
{
    data.fill(0);
}

uint8_t Memory::read(uint16_t address) const
{
    return data[address];
}

void Memory::write(uint16_t address, uint8_t value)
{
    data[address] = value;
}
