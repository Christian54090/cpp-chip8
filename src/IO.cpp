//
// Created by csanders on 10/24/19.
//

#include <iostream>
#include "IO.h"

void IO::init() {
    draw_flag = false;
    for (unsigned char & i : screen) {
        i = 0;
    }
    for (unsigned char & i : key) {
        i = 0;
    }
}

bool IO::is_key_pressed(u8 index) {
    return key[index] != 0;
}

bool IO::pixel_is_on(u16 index) {
    return screen[index] == 1;
}

void IO::xor_pixel(u16 index) {
    std::cout << "Drawing screen at: " << std::hex << index << "\n";
    screen[index] ^= 1;
}

void IO::set_draw_flag(bool val) {
    draw_flag = val;
}