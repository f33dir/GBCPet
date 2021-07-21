//
// Created by f33dir on 6/26/21.
//
#ifndef GAMEBOY_CPU_H
#define GAMEBOY_CPU_H
#include <CPU/Memory/Memory.h>
#include <cstdint>
#include "Utils/Utils.h"

class CPU {
public:
    CPU();
    void step();
    void reset();
    void loadGame(std::ifstream&);
    void start();
private:

    Memory * memory = new Memory();
    CPUState state = READ;


    uint16_t SP = 0xFFFE;
    uint16_t PC = 0x0100;

    int MCyclesAmount;
    uint8_t currentInstruction;

    bool z,n,h,c;
    uint8_t A,B,C,D,E,H,L;

    void readOpCode();
    void executeOperation();

    uint16_t c8to16(uint8_t a, uint8_t b);
    void LD(uint8_t & target, uint8_t value);
    void INC8(uint8_t & reg);
    void INC16(uint16_t & reg);
    void DEC8
};


#endif //GAMEBOY_CPU_H
