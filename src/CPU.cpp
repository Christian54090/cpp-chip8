//
// Created by csanders on 10/23/19.
//

#include "CPU.h"

void CPU::init() {
    pc = 0x200;
    sp = 0;
    delay_timer = 0;
    sound_timer = 0;

    for (int i = 0; i < 16; ++i) {
        stack[i] = 0;
        v[i] = 0;
    }
}