//
// Created by csanders on 10/23/19.
//

#include <stdexcept>
#include <iostream>
#include "CPU.h"
#include "RAM.h"
#include "IO.h"

void CPU::init() {
    pc = 0x200;
    I = 0;
    sp = 0;
    delay_timer = 0;
    sound_timer = 0;

    for (int i = 0; i < 16; ++i) {
        stack[i] = 0;
        v[i] = 0;
    }
}

void CPU::step(RAM ram, IO io) {
    u16 opcode = ram.get_word(pc);

    // DEBUGGING
//    std::cout << std::hex << opcode << " " << pc << " " << sp << " " << I << "\n";
//    for (unsigned char i : v) {
//        std::cout << std::hex << (int)i << ", ";
//    }
//    std::cout << "\n\n";

    execute(opcode, ram, io);
}

void CPU::execute(u16 opcode, RAM ram, IO io) {
    u16 nnn = opcode & 0x0FFF;
    u8 nn = opcode & 0x00FF;
    u8 n = opcode & 0x000F;
    u8 x = (opcode & 0x0F00) >> 8;
    u8 y = (opcode & 0x00F0) >> 4;

    switch(opcode & 0xF000) {
        case 0x0000:
            switch(nnn) {
                case 0x0E0:
                    io.clear_display();
                    io.set_draw_flag(true);
                    pc += 2;
                    break;
                case 0x0EE:
                    --sp;
                    pc = stack[sp];
                    pc += 2;
                    break;
                default:
                    printf("Unrecognized 0 opcode: %.4X\n", opcode);
                    exit(3);
            }
            break;
        case 0x1000:
            pc = nnn;
            break;
        case 0x2000:
            stack[sp] = pc;
            ++sp;
            pc = nnn;
            break;
        case 0x3000:
            pc += 2;
            if (v[x] == nn)
                pc += 2;
            break;
        case 0x6000:
            v[x] = nn;
            pc += 2;
            break;
        case 0x7000:
            v[x] += nn;
            pc += 2;
            break;
        case 0x8000:
            switch(n) {
                case 0x0:
                    v[x] = v[y];
                    pc += 2;
                    break;
                case 0x2:
                    v[x] = v[x] & v[y];
                    pc += 2;
                    break;
                case 0x6:
                    if ((v[x] & 0x0F) == 1) {
                        v[0xF] = 1;
                    } else {
                        v[0xF] = 0;
                    }
                    v[x] /= 2;
                    pc += 2;
                    break;
                default:
                    printf("Unrecognized 8 opcode: %.4X\n", opcode);
                    exit(3);
            }
            break;
        case 0xA000:
            I = nnn;
            pc += 2;
            break;
        case 0xD000:
            v[0xF] = 0;

            u8 pixel;
            for (int row = 0; row < n; row++) {
                pixel = ram.mem[I + row];
                for (int col = 0; col < 8; col++) {
                    if ((pixel & (0x80 >> col)) != 0) {
                        u16 index = x + col + ((row + col) * 64);
                        if (io.pixel_is_on(index))
                            v[0xF] = 1;
                        io.xor_pixel(index);
                    }
                }
            }
            io.set_draw_flag(true);
            pc += 2;
            break;
        case 0xE000:
            switch(nn) {
                case 0x9E:
                    if (io.is_key_pressed(x)) {
                        pc += 4;
                    } else {
                        pc += 2;
                    }
                    break;
                case 0xA1:
                    if (!io.is_key_pressed(x)) {
                        pc += 4;
                    } else {
                        pc += 2;
                    }
                    break;
                default:
                    printf("Unrecognized E opcode: %.4X\n", opcode);
                    exit(3);
            }
            break;
        case 0xF000:
            switch(nn) {
                case 0x07:
                    v[x] = delay_timer;
                    break;
                case 0x15:
                    delay_timer = v[x];
                    break;
                case 0x1E:
                    I += v[x];
                    break;
                default:
                    printf("Unrecognized F opcode: %.4X\n", opcode);
                    exit(3);
            }
            pc += 2;
            break;
        default:
            printf("Unrecognized opcode: %.4X\n", opcode);
            exit(3);
    }
}