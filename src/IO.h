//
// Created by csanders on 10/24/19.
//

#ifndef CCHIP8_IO_H
#define CCHIP8_IO_H

typedef unsigned char u8;
typedef unsigned short int u16;

class IO {
private:
    u8 screen[32 * 64];
    u8 key[16];
    bool draw_flag;
public:
    void init();
    bool is_key_pressed(u8 index);
    bool pixel_is_on(u16 index);
    void xor_pixel(u16 index);
    void set_draw_flag(bool val);
    void set_key(u8 index, u8 val);
    bool check_draw_flag();
    u8 get_pixel(u16 index);
    void clear_display();
};


#endif //CCHIP8_IO_H
