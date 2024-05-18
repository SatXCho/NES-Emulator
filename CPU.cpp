#include "CPU.h"

CPU::CPU(Memory &memory) : memory(memory)
{
    reset();
}

void CPU::reset()
{
    pc = 0xC000;
    sp = 0xFD;
    a = x = y = 0;
    status = 0x34;
}

void CPU::executeInstruction()
{
    uint8_t opcode = memory.read(pc++);

    switch (opcode)
    {
    case 0xA9:
    { // LDA Immediate
        uint8_t value = memory.read(pc++);
        LDA(value);
        break;
    }
    case 0xAA:
    { // TAX
        TAX();
        break;
    }
    case 0xE8:
    { // INX
        INX();
        break;
    }
    case 0x00:
    { // BRK
        BRK();
        break;
    }
    // Add more cases here...
    default:
        // Handle unknown opcode
        break;
    }
}

void CPU::LDA(uint16_t address)
{
    a = address;
    setFlag(0x02, a == 0);   // Zero flag
    setFlag(0x80, a & 0x80); // Negative flag
}

void CPU::TAX()
{
    x = a;
    setFlag(0x02, x == 0);   // Zero flag
    setFlag(0x80, x & 0x80); // Negative flag
}

void CPU::INX()
{
    x++;
    setFlag(0x02, x == 0);   // Zero flag
    setFlag(0x80, x & 0x80); // Negative flag
}

void CPU::BRK()
{
    // Implement BRK instruction
}

void CPU::setFlag(uint8_t flag, bool value)
{
    if (value)
        status |= flag;
    else
        status &= ~flag;
}

bool CPU::getFlag(uint8_t flag)
{
    return (status & flag) != 0;
}
