#include <SDL2/SDL.h>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <stdexcept>

struct Chip_8 {

    std::array<uint8_t, 4096> memoria;
    uint16_t PC = 0x200;
    uint16_t R_index_I;
    std::array<uint16_t, 16> stack;
    uint8_t timer;
    uint8_t sound_timer;
    uint8_t SP = 0;
    /*-------registradores-----*/
    std::array<uint8_t, 16> registradores;
    /********************display********************/
    std::array<uint8_t, 2048> display;

    // como os digitos do teclado sao representados em hexadecimal
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

// struct que separa as instrucoes
struct dados {
    uint16_t full;
    // 4 mais significativos
    uint8_t opcode;
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
// funcao que separa as instrucoes
void desestruturar(dados&, uint16_t);
void decode(const dados, Chip_8&);

// funcoes que vao ser executadas dentro do switch baseado no opcde
void op_0(dados&, Chip_8&);
void op_1(dados&, Chip_8&);
void op_2(dados&, Chip_8&);
void op_3(dados&, Chip_8&);
void op_4(dados&, Chip_8&);
void op_5(dados&, Chip_8&);
void op_6(dados&, Chip_8&);
void op_7(dados&, Chip_8&);
void op_8(dados&, Chip_8&);
void op_9(dados&, Chip_8&);
void op_A(dados&, Chip_8&);
void op_B(dados&, Chip_8&);
void op_C(dados&, Chip_8&);
void op_D(dados&, Chip_8&);
void op_E(dados&, Chip_8&);
void op_F(dados&, Chip_8&);
