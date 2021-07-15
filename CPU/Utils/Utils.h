//
// Created by f33dir on 6/26/21.
//

#ifndef GAMEBOY_UTILS_H
#define GAMEBOY_UTILS_H
enum CPUState{
    READ,
    EXECUTING
};
struct opInfo{
    opInfo(){};
    opInfo(short dur, int flags, short lenght,uint8_t op){
        duration = dur;
        this->flags = flags;
        this->lenght = lenght;
        opCode = op;
    };
    short duration;
    int flags;
    short lenght;
    uint8_t opCode;
};
#endif //GAMEBOY_UTILS_H
