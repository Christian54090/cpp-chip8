#include <iostream>
#include <chrono>
#include <thread>
#include "stdint.h"
#include "SDL2/SDL.h"

#include "CPU.h"
#include "RAM.h"
#include "IO.h"

using namespace std;

typedef unsigned char u8;
typedef unsigned short int u16;

u8 keymap[16] = {
        SDLK_x,
        SDLK_1,
        SDLK_2,
        SDLK_3,
        SDLK_q,
        SDLK_w,
        SDLK_e,
        SDLK_a,
        SDLK_s,
        SDLK_d,
        SDLK_z,
        SDLK_c,
        SDLK_4,
        SDLK_r,
        SDLK_f,
        SDLK_v,
};

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

    int width = 1024;
    int height = 512;

    SDL_Window *window = nullptr;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow(
            "Chip-8 Emulator",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(2);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, width, height);

    SDL_Texture *sdlTexture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            64, 32
    );

    uint32_t buffer[2048];

    while(true) {
        cpu.step(ram, io);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) exit(0);
                for (int i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i])
                        io.set_key(i, 1);
                }
            }
            if (e.type == SDL_KEYUP) {
                for (int i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i])
                        io.set_key(i, 0);
                }
            }
        }
        if (io.check_draw_flag()) {
            io.set_draw_flag(false);

            for (int i = 0; i < 2048; ++i) {
                u8 pixel = io.get_pixel(i);
                buffer[i] = (0x00FFFFFF * pixel) | 0xFF000000;
            }
            SDL_UpdateTexture(sdlTexture, nullptr, buffer, 64 * sizeof(Uint32));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, sdlTexture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
    }
}