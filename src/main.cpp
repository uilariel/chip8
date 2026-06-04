#include "chip8.h"
#include <SDL2/SDL.h>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>

int main()
{

    std::ifstream ROM;
    ROM.open("nomearquivo.txt", std::ios_base::binary);
    if (ROM.is_open() == false) {
        std::cout << "abertura falhou\n";
        return -1;
    }
    char c;
    Chip_8 Chip8;
    // variavel que vai auxiliar na copia
    int i = 0;
    /*
     ==========COPIA A ROM PRA MEMORIA============
     * */
    while (ROM.get(c)) {
        Chip8.memoria.at(512 + i) = c;
        i++;
    }

    return 0;
}
