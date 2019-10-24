#include <iostream>
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
    rom_file = fopen("c:/INVADERS", "rb");
    fread(&ram.mem[0x200], 0xFFF, 1, rom_file);
    fclose(rom_file);

    cpu.step(ram);

    return 0;
}