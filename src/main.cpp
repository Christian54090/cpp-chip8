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


    return 0;
}