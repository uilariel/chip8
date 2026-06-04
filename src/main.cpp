#include "chip8.h"
#include <SDL2/SDL.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

int main()
{

    std::ifstream ROM;
    ROM.open("../roms/teste1.ch8", std::ios_base::binary);
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

    for (int x = 0; i < 80; i++) {
        Chip8.memoria.at(x) = Chip8.sprites.at(x);
    }
    /*
-----------------------TESTES DA MEMORIA--------------------------

    for (int z = 511; z < 540; z++) {
        std::cout << Chip8.memoria.at(z) << std::endl;
    }


    */
    return 0;
}
