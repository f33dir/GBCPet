//
// Created by f33dir on 6/26/21.
//

#ifndef GAMEBOY_MEMORY_H
#define GAMEBOY_MEMORY_H


#include <cstdint>
#include <fstream>
#include "MemUtils/MemUtils.h"
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
class Memory {
    //IO
    uint8_t DPAD;
    uint8_t ACTION_BUTTONS;
    uint8_t TIME;

    std::vector<uint8_t> RAWMEM ;
    MBCType mbcType;
    //memory blocks
    uint8_t ** ROMBANKS = new uint8_t*[512];//16kb
    uint8_t * ROM1;
    uint8_t * ROM2;
    uint8_t ** VRAMBANKS = new uint8_t*[2];//8kb
    uint8_t * VRAM;
    uint8_t ** ERAMBANKS = new uint8_t*[16];//8kb
    uint8_t * ERAM;
    uint8_t ** WRAMBANKS = new uint8_t*[8];//4kb
    uint8_t * WRAM1;
    uint8_t * WRAM2;
    uint8_t * OAM = new uint8_t[160];
    uint8_t * IO = new uint8_t[128];
    uint8_t * HRAM = new uint8_t[126];
    uint8_t  IE;

    uint8_t BANKMODE = 0;
    uint8_t LOWBANKNUM = 0x01;
    uint8_t HIGHBANKNUM = 0x01;

    bool CART_RUMBLE;
    bool IS_RUMBLING;
    bool CART_BATT;

    int TIMER_CLOCK;
    int TIMER_COUNTER;

public:
    Memory(){};
    void initMemory(std::ifstream &file);
    uint8_t&  getMem8(uint16_t);
    uint16_t getMem16(uint16_t);
    int write8(uint8_t value, uint16_t pos);
    int write16();
};

#endif //GAMEBOY_MEMORY_H
