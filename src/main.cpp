#include <iostream>
#include "stdint.h"
#include "SDL2/SDL.h"
#include "CPU.h"
#include "RAM.h"
#include "IO.h"

typedef unsigned char u8;
typedef unsigned short int u16;

int main() {
    CPU cpu{};
    cpu.init();
    RAM ram{};
    ram.init();
    IO io{};
    io.init();

    FILE *rom_file;
    rom_file = fopen("../roms/INVADERS", "rb");
    fread(&ram.mem[0x200], 4095, 1, rom_file);
    fclose(rom_file);

    while(true) {
        cpu.step(ram, io);
    }
}