//
// Created by f33dir on 6/26/21.
//

#include "Memory.h"
#include <fstream>
#include <vector>

uint8_t& Memory::getMem(uint16_t input) {
    if(input<0x4000){
        return ROM1[input];
    }
    if(input<0x8000){
        return ROM2[input-0x4000];
    }
    if(input<0xA000){
        return VRAM[input-0x8000];
    }
    if(input<0xC000){
        return ERAM[input-0xA000];
    }
    if(input<0xD000){
        return WRAMBANKS[1][input-0xC000];
    }
    if(input<0xE000){
        return WRAM2[input-0xD000];
    }
    if(input<0xFE00){
        return ERAM[input-0xE000];
    }
    if(input<0xFEA0){
        return OAM[input-0xFE00];
    }
//    if(input<0xFF00){
//        return ;
//    }
    if(input<0xFF80) {
        return IO[input-0xFEFF];
    }
    if(input<0xFFFF) {
        return HRAM[input-0xFF80];
    }
    return IE;
}
void Memory::initMemory(std::ifstream &filestream ) {
    std::vector<uint8_t> vec;
    std::for_each(std::istreambuf_iterator<char>(filestream),
                  std::istreambuf_iterator<char>(),
                  [&vec](const char c){
                      vec.push_back(c);
                  });
    RAWMEM = vec;
    for(int i = 0;i<8;i++){
        WRAMBANKS[i] = new uint8_t [4096];
    }
    WRAM1 = WRAMBANKS[0];
    WRAM2 = WRAMBANKS[1];
    VRAMBANKS[0] = new uint8_t [8192];
    VRAMBANKS[1] = new uint8_t [8192];
    VRAM = VRAMBANKS[0];
    int rombankamount;
    switch(RAWMEM[0x148]){
        case 0://32kb
            rombankamount = 2;
            break;
        case 1://64kb
            rombankamount = 4;
            break;
        case 2://128kb
            rombankamount = 8;
            break;
        case 3://256kb
            rombankamount = 16;
            break;
        case 4://512kb
            rombankamount = 32;
            break;
        case 5://1mb
            rombankamount = 64;
            break;
        case 0x52:
            rombankamount = 36;
            break;
        case 0x53:
            rombankamount = 40;
            break;
        case 0x54:
            rombankamount = 48;
            break;
    }
    for(int i = 0 ;i<rombankamount;i++){
        ROMBANKS[i] = new uint8_t [16384];
        std::copy(RAWMEM.begin()+(16384*i),RAWMEM.begin()+(16384*(i+1)),ROMBANKS[i]);
    }
    ROM1 = ROMBANKS[0];
    ROM2 = ROMBANKS[1];
    switch(RAWMEM[0x147]){
        case 0:
        case 8:
        case 9:
            mbcType = NOMBC;
            break;
        case 1:
        case 2:
        case 3:
            mbcType = MBC1;
            break;
        case 5:
        case 6:
            mbcType = MBC2;
            break;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            mbcType = MBC3;
            break;
        case 25:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            mbcType = MBC5;
            break;
        default:
            std::exit(2);
    }
}


int Memory::writeMem(uint8_t value, uint16_t pos) {
    if(pos<0x2000){
        switch(mbcType){
            case NOMBC:
                return 1;
            case MBC1:
                return 0;
            case MBC2:
                int switcher;
                switcher = (pos / 256 ) % 2;
                if(switcher == 1){
                    int bank = value % 16;
                    if(bank == 0) bank++;
                    ROM2 = ROMBANKS[bank];
                }
                return 0;
            case MBC3:
                return 0;
            case MBC5:
                return 0;
        }
    }
    if(pos<0x4000){
        switch(mbcType){
            case NOMBC:
                return 1;
            case MBC1: {
                LOWBANKNUM = value;
                int rombanklow = LOWBANKNUM % 32;
                int rombankhigh = (HIGHBANKNUM % 4)*32;
                int bank;
                if (BANKMODE == 0) {
                    bank = rombanklow + rombankhigh;
                } else {
                    bank = rombankhigh;
                }
                if(bank == 0 || bank == 20 || bank == 40 || bank == 60){
                    bank++;
                }
                ROM2 = ROMBANKS[bank];
                }
                return 0;
            case MBC2:
                int switcher;
                switcher = (pos / 256 ) % 2;
                if(switcher == 1){
                    int bank = value % 16;
                    if(bank == 0) bank++;
                    ROM2 = ROMBANKS[bank];
                }
                return 0;
            case MBC3: {
                int bank = value;
                if (bank == 0) {
                    bank++;
                };
                bank %= 128;
                ROM2 = ROMBANKS[bank];
                return 0;
            }
            case MBC5: {
                if(pos>0x3000) {
                    LOWBANKNUM = value;
                } else {
                    HIGHBANKNUM = value % 2;
                }
                int bank = (HIGHBANKNUM % 2)* 256 +LOWBANKNUM;
                ROM2 = ROMBANKS[bank];
            }
        }

    }
    if(pos<0x6000){
        switch(mbcType){
            case NOMBC:
                return 1;
            case MBC2:
                return 1;
            case MBC1: {
                HIGHBANKNUM = value;
                int rombanklow = LOWBANKNUM % 32;
                int rombankhigh = (HIGHBANKNUM % 4) * 32;
                int bank;
                if (BANKMODE == 0) {
                    bank = rombanklow + rombankhigh;
                    ROM2 = ROMBANKS[bank];
                } else {
                    ERAM = ERAMBANKS[value % 4];
                }
                return 0;
            }
            case MBC3: {
                if(value <8){
                    ERAM = ERAMBANKS[value];
                    return 0;
                } else {
                    //todo finish it with actual date time info cause now idk how rtc works
                    std::time_t t = std::time(0);
                    switch(value){
                        case 0x08:
                            TIME = t % 60;
                            return 0;
                        case 0x09:{
                            int min = t/60;
                            TIME = min % 60;
                            return 0;
                        }
                        case 0x0A:{
                            int hours = t / 3600;
                            TIME = hours % 24;
                            return 0;
                        }
                        case 0x0B:
                            TIME = (t / 3600 / 24)% 256;
                            return 0;
                        case 0x0C:
                            TIME = 0;
                            return 0;
                        default:
                            return 1;
                    }
                }
            }
            case MBC5:{
                if(!CART_RUMBLE){
                    int bank = value % 16;
                    ERAM = ERAMBANKS[bank];
                } else {
                    int bank = value % 8;
                    IS_RUMBLING = (value & 0x08);
                    ERAM = ERAMBANKS[bank];
                }
                return 0;
            }
        }
    }
    if(pos<0x8000){
        switch (mbcType) {
            case NOMBC:return 1;
            case MBC1:{
                BANKMODE = value % 2;
                return 0;
            }
            case MBC2: return 1;
            case MBC3: return 0;
            case MBC5: return 1;
        }
    }
    if(pos < 0xA000){
        VRAM[pos-0x8000] = value;
        return 0;
    }
    if(pos<0xC000){
        WRAM1[pos-0xA000] = value;
        return 0;
    }
    if(pos<0xE000){
        WRAM2[pos-0xC000] = value;
        return 0;
    }
    if(pos<0xFDFF){
        WRAM1[pos - 0xE000] = value;
        return 0;
    }
    if(pos<0xFEA0){
        OAM[pos-0xFDFF] = value;
        return 0;
    }
    if(pos<0xFF00) return 1;
    if(pos<0xFFFF and pos>0xFF7F){
        HRAM[pos - 0xFF00] = value;
    };
    switch(pos){
        case 0xFF00:{
            if((value & 0x30)==16){
                IO[0] = DPAD & 0xD0;
                return 0;
            } else if ((value & 0x30)==32){
                IO[0] = ACTION_BUTTONS & 0xE0;
                return 0;
            } else return 1;
        }
        case 0xFF01:{
            IO[1] = value;
            return 0;
        }
        case 0xFF02:{
            IO[2] = value & 0x7C;
            return 0;
        }
        case 0xFF04:{
            IO[4] = 0;
            return 0;
        }
        case 0xFF05:{
            IO[5] = value;
            return 0;
        }
        case 0xFF06:{
            IO[6] = value;
            return 0;
        }
        case 0xFF07:{
            IO[7] = value & 0xF8;
            return 0;
        }
        case 0xFF0F:{
            IO[0xF] = value & 0xE0;
            return 0;
        }
        case 0xFF40: {
            IO[0x40] = value;
            return 0;
        }
        case 0xFF41: {
            IO[0x41] = (value & 0xC0) - (IO[0x41] &0x07);
            return 0;
        }
        case 0xFF42: {
            IO[42]  = value;
            return 0;
        }
        case 0xFF43: {
            IO[43]  = value;
            return 0;
        }
        case 0xFF44:{
            return 1;
        }
        case 0xFF45:
        case 0xFF46:
        case 0xFF47:
        case 0xFF48:
        case 0xFF49:
        case 0xFF4A:
        case 0xFF4B:{
            IO[pos - 0xFF00]  = value;
            return 0;
        }
        case 0xFFFF:{
           IE = value & 0xE0;
        }
        default:
            return 1;
    }
}

