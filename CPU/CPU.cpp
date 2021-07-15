//
// Created by f33dir on 6/26/21.
//
#include <fstream>
#include "CPU.h"
void CPU::step() {
    switch(state){
        case READ:
            readOpCode();
            switch(currentInstruction){

            }
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

}

void CPU::loadGame(std::ifstream &file) {
    memory->initMemory(file);
}
