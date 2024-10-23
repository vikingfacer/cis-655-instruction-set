#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <iomanip>
#include <bitset>

class ALU
{
    std::map<std::string, int> M = {
        {"M0", 0}, {"M1", 1}, {"M2", 2}, {"M3", 3}, {"M4", 4}, {"M5", 5}, {"M6", 6}, {"M7", 7}, {"M8", 8}, {"M9", 9}, {"M10", 10}, {"M11", 11}, {"M12", 12}, {"M13", 13}, {"M14", 14}, {"M15", 15}};

    // build a dictionary of op codes
    std::map<uint8_t, std::string> OPCODES = {
        {0b0000, "am"},
        {0b0001, "sm"},
        {0b0010, "mm"},
        {0b0011, "dm"},
        {0b0100, "bnem"},
        {0b0101, "sltm"},
        {0b0110, "ai"},
        {0b0111, "si"},
        {0b1000, "mi"},
        {0b1001, "di"},
        {0b1010, "lci"},
        {0b1011, "sci"},
        {0b1100, "lo"},
        {0b1101, "so"},
        {0b1110, "jb"}};

    std::map<uint8_t, std::string> MEMORY_REGISTERS = {
        {0b0000, "M0"},
        {0b0001, "M1"},
        {0b0010, "M2"},
        {0b0011, "M3"},
        {0b0100, "M4"},
        {0b0101, "M5"},
        {0b0110, "M6"},
        {0b0111, "M7"},
        {0b1000, "M8"},
        {0b1001, "M9"},
        {0b1010, "M10"},
        {0b1011, "M11"},
        {0b1100, "M12"},
        {0b1101, "M13"},
        {0b1110, "M14"},
        {0b1111, "M15"}};

    // Program counter
    int pc;

    // Array to hold function pointers, indexed by opcode
    std::vector<std::function<int(uint8_t, uint8_t, uint8_t)>> functions;

    // array of integers to represent memory
    std::vector<uint16_t> &memory;

public:
    ALU(std::vector<uint16_t> &mem, int pcInit = 32) : memory(mem), pc(pcInit)
    {
        if (mem.empty())
        {
            mem = std::vector<uint16_t>(64, 0);
        }

        // Initialize the function array with 15 opcodes
        functions.resize(15);

        // Map opcodes to corresponding functions
        functions[0] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return am(op1, op2, op3); };
        functions[1] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return sm(op1, op2, op3); };
        functions[2] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return mm(op1, op2, op3); };
        functions[3] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return dm(op1, op2, op3); };
        functions[4] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return bnem(op1, op2, op3); };
        functions[5] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return sltm(op1, op2, op3); };
        functions[6] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return ai(op1, op2, op3); };
        functions[7] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return si(op1, op2, op3); };
        functions[8] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return mi(op1, op2, op3); };
        functions[9] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return di(op1, op2, op3); };
        functions[10] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return lci(op1, op2, op3); };
        functions[11] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return sci(op1, op2, op3); };
        functions[12] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return lo(op1, op2, op3); };
        functions[13] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return so(op1, op2, op3); };
        functions[14] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
        { return jb(op1, op2, op3); };
    }

    // add memory-memory
    // opcode 0000
    int am(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = memory[op1] + memory[op2];
        return 1;
    }

    // subtract memory-memory
    // opcode 0001
    int sm(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = memory[op1] - memory[op2];
        return 1;
    }

    // multiply memory-memory
    // opcode 0010
    int mm(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = memory[op1] * memory[op2];
        return 1;
    }

    // divide memory-memory
    // opcode 0011
    int dm(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        if (memory[op2] == 0)
        {
            throw std::invalid_argument("Error: Division by zero.");
            return 0;
        }
        memory[op3] = memory[op1] / memory[op2];
        return 1;
    }

    // branch if not equal memory-memory
    // opcode 0100
    int bnem(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        if (memory[op1] != memory[op2])
        {
            return int(op3); // Adjust program counter
        }
        else
        {
            return 1;
        }
    }

    // set less than memory-memory
    // opcode 0101
    int sltm(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = (memory[op1] < memory[op2]) ? 1 : 0;
        return 1;
    }

    // add immediate
    // opcode 0110
    int ai(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = memory[op1] + op2;
        return 1;
    }

    // subtract immediate
    // opcode 0111
    int si(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = memory[op1] - op2;
        return 1;
    }

    // multiply immediate
    // opcode 1000
    int mi(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = memory[op1] * op2;
        return 1;
    }

    // divide immediate
    // opcode 1001
    int di(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        if (op2 == 0)
        {
            throw std::invalid_argument("Error: Division by zero.");
        }
        memory[op3] = memory[op1] / op2;
        return 1;
    }

    // load constant immediate
    // opcode 1010
    int lci(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = op1 + op2;
        return 1;
    }

    // subtract constant immediate
    // opcode 1011
    int sci(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        // is this right?
        memory[op3] = op1 + op2;
        return 1;
    }

    // load using offset
    // opcode 1100
    int lo(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[op3] = memory[memory[op1] + memory[op2]];
        return 1;
    }

    // store using offset
    // opcode 1101
    int so(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        memory[memory[op1] + memory[op2]] = memory[op3];
        return 1;
    }

    // jump back
    // opcode 1110
    int jb(uint8_t op1, uint8_t op2, uint8_t op3)
    {
        return -(int(op1 + op2 + op3));
    }

    void printMemory()
    {
        int c = 0;
        for (auto const &x : memory)
        {
            std::cout << c << " : " << x << std::endl;
            c++;
        }
    }

    void printInColumns(const std::vector<uint16_t> &list, int columns)
    {
        int rows = (list.size() + columns - 1) / columns; // Calculate number of rows needed

        // Print the elements in multiple columns
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                int index = i + j * rows;
                if (index < list.size())
                {

                    // print the 16 bit number in binary
                    std::cout << std::setw(3) << index << " : " << std::setw(6) << std::bitset<16>(list[index]) << " | ";
                }
            }
            std::cout << std::endl;
        }
    }

    void printInColumnsInt(const std::vector<uint16_t> &list, int columns)
    {
        int rows = (list.size() + columns - 1) / columns; // Calculate number of rows needed

        // Print the elements in multiple columns
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                int index = i + j * rows;
                if (index < list.size())
                {
                    // print the 16 bit number in binary
                    std::cout << std::setw(3) << index << " : " << std::setw(6) << list[index] << " | ";
                }
            }
            std::cout << std::endl;
        }
    }

    void printPC()
    {
        std::cout << "PC: " << pc << std::endl;
    }

    void printOPCODE(uint16_t opcode)
    {
        uint8_t op = (opcode >> 12) & 0x0F; // Extract bits [15:12]
        uint8_t op1 = (opcode >> 8) & 0x0F; // Extract bits [11:8]
        uint8_t op2 = (opcode >> 4) & 0x0F; // Extract bits [7:4]
        uint8_t op3 = opcode & 0x0F;

        std::cout << "OPCODE: " << std::bitset<4>(op) << " " << std::bitset<4>(op1) << " " << std::bitset<4>(op2) << " " << std::bitset<4>(op3) << std::endl;
    }

    void printEXECUTING(uint16_t opcode)
    {
        uint8_t op = (opcode >> 12) & 0x0F; // Extract bits [15:12]
        uint8_t op1 = (opcode >> 8) & 0x0F; // Extract bits [11:8]
        uint8_t op2 = (opcode >> 4) & 0x0F; // Extract bits [7:4]
        uint8_t op3 = opcode & 0x0F;

        std::cout << "EXECUTING: " << OPCODES[op] << " " << MEMORY_REGISTERS[op1] << " " << MEMORY_REGISTERS[op2] << " " << MEMORY_REGISTERS[op3] << std::endl;
    }

    // execute(0000 0000 0000 0000)
    int execute(uint16_t opcode)
    {
        uint8_t op = (opcode >> 12) & 0x0F; // Extract bits [15:12]
        uint8_t op1 = (opcode >> 8) & 0x0F; // Extract bits [11:8]
        uint8_t op2 = (opcode >> 4) & 0x0F; // Extract bits [7:4]
        uint8_t op3 = opcode & 0x0F;

        if (op >= 0 && op < functions.size())
        {
            try
            {
                int inc = functions[op](op1, op2, op3);
                if (inc)
                {
                    pc += inc;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            std::cout << "Error: Invalid opcode." << std::endl;
        }
        printOPCODE(opcode);
        // printEXECUTING(opcode);
        printInColumnsInt(memory, 4);
        // printInColumns(memory, 4);
        printPC();
        return pc;
    }

    void setPC(int newPC)
    {
        pc = newPC;
    }

    int getPC()
    {
        return pc;
    }
};

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
