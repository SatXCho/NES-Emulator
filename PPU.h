#ifndef PPU_H
#define PPU_H

#include <cstdint>
#include <array>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;
const int PATTERN_TABLE_SIZE = 0x1000;
const int NAME_TABLE_SIZE = 0x400;

class PPU
{
public:
    PPU();
    void reset();
    void render(uint8_t *screenData);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

private:
    std::array<uint8_t, SCREEN_WIDTH * SCREEN_HEIGHT> frameBuffer;
    std::array<uint8_t, PATTERN_TABLE_SIZE * 2> patternTables;
    std::array<uint8_t, NAME_TABLE_SIZE * 4> nameTables;

    void renderBackground();
};

#endif // PPU_H
