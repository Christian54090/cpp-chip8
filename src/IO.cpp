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

void IO::set_key(u8 index, u8 val) {
    key[index] = val;
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

bool IO::check_draw_flag() {
    return draw_flag;
}

u8 IO::get_pixel(u16 index) {
    return screen[index];
}

void IO::clear_display() {
    for (unsigned char & i : screen) {
        i = 0;
    }
}