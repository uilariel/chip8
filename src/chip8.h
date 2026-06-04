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
