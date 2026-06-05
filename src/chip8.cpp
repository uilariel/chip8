#include "chip8.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <stdexcept>

void desestruturar(dados& dado, uint16_t instrucao)
{
    dado.full = instrucao;
    dado.opcode = (0b1111000000000000 & instrucao) >> 12;
    dado.x = (0b0000111100000000 & instrucao) >> 8;
    dado.y = (0b0000000011110000 & instrucao) >> 4;
    dado.nnn = (0b0000111111111111 & instrucao);
    dado.kk = (0b0000000011111111 & instrucao);
    dado.n = (0b0000000000001111 & instrucao);
}

// TODO: FUNCAO QUE TRANSFORMA OS 2 BYTES DA INSTRUCAO EM UM UINT16_T
void decode(dados dado, Chip_8& chip)
{
    chip.PC = chip.PC + 2;
    switch (dado.opcode) {
    }
}

void op_0(dados& dado, Chip_8& chip)
{
    // clear the display
    if (dado.full == 0x00E0) {
        for (int i = 0; i < 2048; i++) {
            chip.display.at(i) = 0;
        }
    }
    // return from a subroutine ERRADO AJEITAR
    if (dado.full == 0x00EE) {
        chip.PC = chip.stack[chip.SP];
        chip.stack[chip.SP] = { };
        chip.SP = chip.SP - 1;
    }

    // pode ser ignorada: SYS addr
    // jump to a machine code at nnn
    chip.PC = dado.nnn;
}

// jump to address  nnn
void op_1(dados& dado, Chip_8& chip)
{
    chip.PC = dado.nnn;
}

// call subnroutine at nnn
void op_2(dados& dado, Chip_8& chip)
{
    chip.SP = chip.SP + 1;
    chip.stack[chip.SP] = chip.PC;
    chip.PC = dado.nnn;
}

// if registrador x = kk, pula pra proxima instrucao
void op_3(dados& dado, Chip_8& chip)
{
    if (chip.registradores[dado.x] == dado.kk) {
        chip.PC = chip.PC + 2;
    }
}

// if regitrador x != kk, pula pra proxima instrucao
void op_4(dados& dado, Chip_8& chip)
{
    if (chip.registradores[dado.x] == dado.kk) {
        chip.PC = chip.PC + 2;
    }
}

// if registrador x = registrador y, pula pra proxima instrucao
void op_5(dados& dado, Chip_8& chip)
{
    if (chip.registradores[dado.x] == chip.registradores[dado.y]) {
        chip.PC = chip.PC + 2;
    }
}

// set registrador x = kk
void op_6(dados& dado, Chip_8& chip)
{
    chip.registradores[dado.x] = dado.kk;
}

// soma kk ao registrador x
void op_7(dados& dado, Chip_8& chip)
{
    chip.registradores[dado.x] = chip.registradores[dado.x] + dado.kk;
}

// operacoes entre registradores (x e y) n1 -> n7 & nE
void op_8(dados& dado, Chip_8& chip)
{

    // seta registrador x como registrador y
    if (dado.n == 0x0) {
        chip.registradores[dado.x] = chip.registradores[dado.y];
    }
    // reg_x or reg_y -> reg_x
    if (dado.n == 0x1) {
        chip.registradores[dado.x] = chip.registradores[dado.x] | chip.registradores[dado.y];
    }

    // reg_x and reg_y -> reg x
    if (dado.n == 0x2) {
        chip.registradores[dado.x] = chip.registradores[dado.x] & chip.registradores[dado.y];
    }

    // xor vx vy -> reg x
    if (dado.n == 0x3) {
        chip.registradores[dado.x] = chip.registradores[dado.x] ^ chip.registradores[dado.y];
    }

    // soma reg x e reg y -> reg x || e poe o carry no registrador F
    if (dado.n == 0x4) {
        uint16_t soma_total = chip.registradores[dado.x] + chip.registradores[dado.y];
        uint16_t carry = (soma_total & 0b0000000100000000) >> 8;
        uint16_t soma = (soma_total & 0b0000000011111111);
        chip.registradores[dado.x] = soma;
        chip.registradores[0xF] = carry;
    }

    // reg_x - reg_y -> se der underflow, vf = 0, se nao vF = 1
    if (dado.n == 0x5) {
        if (chip.registradores[dado.x] > chip.registradores[dado.y]) {
            chip.registradores[0XF] = 0x1;
        } else {
            chip.registradores[0xF] = 0x0;
        }

        chip.registradores[dado.x] = chip.registradores[dado.x] - chip.registradores[dado.y];
    }

    // se o ultimo bit de reg x for , VF = 1, se nao, VF = 0
    //-> divide vx por2
    if (dado.n == 0x6) {

        if ((chip.registradores[dado.x] & 0b00000001) == 0x1) {
            chip.registradores[0xF] = 0x1;
        } else {
            chip.registradores[0xF] = 0x0;
        }
        chip.registradores[dado.x] = chip.registradores[dado.x] / 2;
    }

    // reg_y - reg_x -> se der underflow | 0, vf = 0, se nao vf = 1
    if (dado.n == 0x7) {
        if (chip.registradores[dado.y] > chip.registradores[dado.x]) {
            chip.registradores[0xF] = 0x1;
        } else {
            chip.registradores[0xF] = 0x0;
        }
        chip.registradores[dado.y] = chip.registradores[dado.y] - chip.registradores[dado.x];
    }

    // se o primeiro bit de x for 1, vf = 1
    // se nao -> vf = o
    // -> multiplica oq tem no reg_x por 2
    if (dado.n == 0xE) {
        if ((chip.registradores[dado.x] & 0b10000000) == 0b100000000) {
            chip.registradores[0xF] = 0x1;
        } else {
            chip.registradores[0xF] = 0x0;
        }

        chip.registradores[dado.x] = chip.registradores[dado.x] * 2;
    }
}

void op_9(dados& dado, Chip_8& chip);
void op_A(dados& dado, Chip_8& chip);
void op_B(dados& dado, Chip_8& chip);
void op_C(dados& dado, Chip_8& chip);
void op_D(dados& dado, Chip_8& chip);
void op_E(dados& dado, Chip_8& chip);
void op_F(dados& dado, Chip_8& chip);
