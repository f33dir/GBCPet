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

    bool * mainFlags = new bool[4];// z h n c
    uint8_t * reg = new uint8_t[7];//A,B,C,D,E,H,L

    void movePC();
    void readOpCode();



};


#endif //GAMEBOY_CPU_H
