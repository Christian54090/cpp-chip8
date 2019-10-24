#include <iostream>
#include <fstream>
#include <vector>
#include "CPU.h"
#include "RAM.h"

typedef unsigned char u8;
typedef unsigned short int u16;

int main() {
    CPU cpu{};
    cpu.init();
    RAM ram{};
    ram.init();

    FILE *rom_file;
    rom_file = fopen("../roms/INVADERS", "rb");
    fread(&ram.mem[0x200], 4095, 1, rom_file);
    fclose(rom_file);

    while(true) {
        cpu.step(ram);
    }
}