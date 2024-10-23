#include "alu.h"

int main()
{
    std::vector<uint16_t> opcodes = {
        0b1010000010000000, // lci 0, 8, M0
        0b1010000010000001, // lci 0, 8, M1
        0b1010000001110010, // lci 0, 7, M2
        0b1010000010110011, // lci 0, 11, M3
        0b1010000010100100, // lci 0, 10, M4
        0b1010000001000101, // lci 0, 4, M5
        0b1010000000010110, // lci 0, 1, M6
        0b1010000000000111, // lci 0, 0, M7
        0b1010000000011000, // lci 0, 1, M8
        0b1010000000011001, // lci 0, 1, M9

        0b0000100101101111, // am M9, M6, M15
        0b1100111101111010, // lo M15, M7, M10

        0b0101101000001011, // sltm M10, M0, M11
        0b0100101110000010, // bnem M11, M8, 2
        0b1100100101100000, // lo M9, M6, M0

        0b0101000110101011, // sltm M1, M10, M11
        0b0100101110000010, // bnem M11, M8, 2
        0b1100100101100001, // lo M9, M6, M1

        0b0110011000010110, // ai M6, 1, M6
        0b0101011001011011, // sltm M6, M5, M11
        0b0100101110000010, // bnem M11, M8, 2
        0b1110000000001011, // jb 0, 0, 11

        0b1010000111111100, // lci 1, 15, M12
        0b1010001011111101, // lci 2, 15, M13
        0b1101110001110000, // so M12, M7, M0
        0b1101110101110001, // so M13, M7, M1
    };

    int pcInit = 32;
    const int memSize = 64;
    std::vector<uint16_t> mainMemory(memSize, 0);

    ALU alu(mainMemory, pcInit);

    // set the memory at the PC with the opcodes
    for (int i = 0; i < opcodes.size(); i++)
    {
        mainMemory[alu.getPC() + i] = opcodes[i];
    }

    alu.printInColumns(mainMemory, 4);

    std::cout << "pc from " << pcInit << " to " << (pcInit + opcodes.size()) << std::endl;
    while (alu.getPC() < (pcInit + opcodes.size()))
    {
        // wait for enter key
        std::cout << "Press enter to continue" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        alu.execute(mainMemory[alu.getPC()]);
    }
    return 0;
}
