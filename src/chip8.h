#include <SDL2/SDL.h>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <stdexcept>

struct Chip_8 {

    std::array<uint8_t, 4096> memoria;
    uint16_t PC = 0;
    uint16_t R_index_I;
    uint16_t stack;
    uint8_t timer;
    uint8_t sound_timer;
    /*-------registradores-----*/
    uint8_t V0;
    uint8_t V1;
    uint8_t V2;
    uint8_t V3;
    uint8_t V4;
    uint8_t V5;
    uint8_t V6;
    uint8_t V7;
    uint8_t V8;
    uint8_t V9;
    uint8_t VA;
    uint8_t VB;
    uint8_t VC;
    uint8_t VD;
    uint8_t VF;
    uint8_t VG;
    /********************display********************/
    std::array<uint8_t, 2048> display;
    std::array<uint8_t, 80> sprites = {
        0xf0,
        0x90,
        0x90,
        0x90,
        0xf0, // 0
        0x20,
        0x60,
        0x20,
        0x20,
        0x70, // 1
        0xf0,
        0x10,
        0xf0,
        0x80,
        0xf0, // 2
        0xf0,
        0x10,
        0xf0,
        0x10,
        0xf0, // 3
        0x90,
        0x90,
        0xf0,
        0x10,
        0x10, // 4
        0xf0,
        0x80,
        0xf0,
        0x10,
        0xf0, // 5
        0xf0,
        0x80,
        0xf0,
        0x90,
        0xf0, // 6
        0xf0,
        0x10,
        0x20,
        0x40,
        0x40, // 7
        0xf0,
        0x90,
        0xf0,
        0x90,
        0xf0, // 8
        0xf0,
        0x90,
        0xf0,
        0x10,
        0xf0, // 9
        0xf0,
        0x90,
        0xf0,
        0x90,
        0x90, // A
        0xe0,
        0x90,
        0xe0,
        0x90,
        0xe0, // B
        0xf0,
        0x80,
        0x80,
        0x80,
        0xf0, // C
        0xe0,
        0x90,
        0x90,
        0x90,
        0xe0, // D
        0xf0,
        0x80,
        0xf0,
        0x80,
        0xf0, // E
        0xf0,
        0x80,
        0xf0,
        0x80,
        0x80, // F
    };
};

struct dados {
    // 4 mais significativos
    uint16_t opcode;
    // 4 upper instrucao
    uint8_t x;
    // 4 depois do x
    uint8_t y;
    // 12 lower (toda a instrucao)
    uint16_t nnn; // 8 lower da instrucao
    uint8_t kk;
    // ultimos 4 bits
    uint8_t n;
};

void desestruturar(dados&);
