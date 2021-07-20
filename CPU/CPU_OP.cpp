//
// Created by f33dir on 20.07.2021.
//

#include "CPU.h"

void CPU::executeOperation() {
    switch(currentInstruction){
        case 0x00:
            break;
    }
}
void LD_Im(uint8_t & reg, uint8_t value){
    reg = value;
}
uint16_t c8to16(uint8_t)