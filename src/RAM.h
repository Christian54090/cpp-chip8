//
// Created by csanders on 10/23/19.
//

#ifndef CCHIP8_RAM_H
#define CCHIP8_RAM_H

typedef unsigned char u8;
typedef unsigned short int u16;

class RAM {
private:
    u8 mem[4096];
public:
    void init();
};


#endif //CCHIP8_RAM_H
