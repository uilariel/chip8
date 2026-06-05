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
    dado.nnn = (0000111111111111 & instrucao);
    dado.kk = (0000000011111111 & instrucao);
    dado.n = (0000000000001111 & instrucao);
}

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
        chip.SP = chip.SP - 1;
    }
}
