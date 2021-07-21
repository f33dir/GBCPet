//
// Created by f33dir on 20.07.2021.
//

#include "CPU.h"

void CPU::executeOperation() {
    switch(currentInstruction){
        case 0x00:
            break;
        case 0x01:
            LD(B,memory->getMem(++PC));
            LD(C,memory->getMem(++PC));
        case 0x02:
            LD(memory->getMem(c8to16(B,C)),A);
        case 0x03:
            break;
    };
    PC++;
}

void CPU::INC8(uint8_t &reg) {
    reg++;

}
void CPU::INC16(uint16_t &reg) {
    reg++;
}
void CPU::LD(uint8_t & target, uint8_t value){
    target = value;
}
uint16_t CPU::c8to16(uint8_t a, uint8_t b){
    return a*0x0100+ b;
}