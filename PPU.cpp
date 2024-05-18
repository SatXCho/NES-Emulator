#include "PPU.h"

PPU::PPU()
{
    reset();
}

void PPU::reset()
{
    frameBuffer.fill(0);
    patternTables.fill(0);
    nameTables.fill(0);
}

void PPU::render(uint8_t *screenData)
{
    renderBackground();

    std::copy(frameBuffer.begin(), frameBuffer.end(), screenData);
}

void PPU::renderBackground()
{
    // Render background using pattern tables and name tables
    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            frameBuffer[y * SCREEN_WIDTH + x] = (x / 32) % 2 == (y / 32) % 2 ? 255 : 0;
        }
    }
}

uint8_t PPU::read(uint16_t address)
{
    if (address < PATTERN_TABLE_SIZE * 2)
    {
        return patternTables[address];
    }
    else if (address >= 0x2000 && address < 0x2000 + NAME_TABLE_SIZE * 4)
    {
        return nameTables[address - 0x2000];
    }
    // Handle other PPU address spaces...
    return 0;
}

void PPU::write(uint16_t address, uint8_t value)
{
    if (address < PATTERN_TABLE_SIZE * 2)
    {
        patternTables[address] = value;
    }
    else if (address >= 0x2000 && address < 0x2000 + NAME_TABLE_SIZE * 4)
    {
        nameTables[address - 0x2000] = value;
    }
    // Handle other PPU address spaces...
}
