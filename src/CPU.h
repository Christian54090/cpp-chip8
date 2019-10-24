//
// Created by csanders on 10/23/19.
//

#ifndef CCHIP8_CPU_H
#define CCHIP8_CPU_H

typedef unsigned char u8;
typedef unsigned short int u16;

class CPU {
private:
    u16 pc;
    u16 sp;
    u16 stack[16];
    u8 delay_timer;
    u8 sound_timer;
    u8 v[16];

public:
    void init();
};


#endif //CCHIP8_CPU_H
