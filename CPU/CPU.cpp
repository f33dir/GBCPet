//
// Created by f33dir on 6/26/21.
//
#include <fstream>
#include "CPU.h"
void CPU::step() {
    switch(state){
        case READ:
            readOpCode();
            break;
        case EXECUTING:
            MCyclesAmount--;
            break;
    }

}

void CPU::readOpCode() {
    currentInstruction = memory->getMem8(SP);
}

CPU::CPU() {
    A = 0x11;
    B = 0x00;
}

void CPU::loadGame(std::ifstream &file) {
    memory->initMemory(file);
}

