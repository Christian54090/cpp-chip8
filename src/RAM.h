//
// Created by csanders on 10/23/19.
//

#ifndef CCHIP8_RAM_H
#define CCHIP8_RAM_H

typedef unsigned char u8;
typedef unsigned short int u16;

class RAM {
private:
public:
    u8 mem[4096];
    void init();
    void wb(u16 address, u8 value);
    u8 rb(u16 address);
    u16 get_word(u16 address);
};


#endif //CCHIP8_RAM_H
