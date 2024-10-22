#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>

class ALU
{
    std::map<std::string, int> M = {
        {"M0", 0}, {"M1", 1}, {"M2", 2}, {"M3", 3}, {"M4", 4}, {"M5", 5}, {"M6", 6}, {"M7", 7}, {"M8", 8}, {"M9", 9}, {"M10", 10}, {"M11", 11}, {"M12", 12}, {"M13", 13}, {"M14", 14}, {"M15", 15}};

    int pc = 0; // Program counter

    // Array to hold function pointers, indexed by opcode
    std::vector<std::function<bool(std::string, std::string, std::string)>> functions;

    // array of integers to represent memory
    std::vector<int> &memory;

    // size of memory
    int memorySize;

public:
    ALU(std::vector<int> &mem, int memSize) : memory(mem), memorySize(memSize)
    {

        // not sure if we need memSize

        // Initialize the function array with 15 opcodes
        functions.resize(15);

        // Map opcodes to corresponding functions
        functions[0] = [this](std::string op1, std::string op2, std::string dest)
        { return am(op1, op2, dest); };
        functions[1] = [this](std::string op1, std::string op2, std::string dest)
        { return sm(op1, op2, dest); };
        functions[2] = [this](std::string op1, std::string op2, std::string dest)
        { return mm(op1, op2, dest); };
        functions[3] = [this](std::string op1, std::string op2, std::string dest)
        { return dm(op1, op2, dest); };
        functions[4] = [this](std::string op1, std::string op2, std::string target)
        { return bnem(op1, op2, target); };
        functions[5] = [this](std::string op1, std::string op2, std::string dest)
        { return sltm(op1, op2, dest); };
        functions[6] = [this](std::string op1, std::string op2i, std::string dest)
        { return ai(op1, op2i, dest); };
        functions[7] = [this](std::string op1, std::string op2i, std::string dest)
        { return si(op1, op2i, dest); };
        functions[8] = [this](std::string op1, std::string op2i, std::string dest)
        { return mi(op1, op2i, dest); };
        functions[9] = [this](std::string op1, std::string op2i, std::string dest)
        { return di(op1, op2i, dest); };
        functions[10] = [this](std::string op1i, std::string op2i, std::string dest)
        { return lci(op1i, op2i, dest); };
        functions[11] = [this](std::string op1i, std::string op2i, std::string dest)
        { return sci(op1i, op2i, dest); };
        functions[12] = [this](std::string op1, std::string op2, std::string dest)
        { return luo(op1, op2, dest); };
        functions[13] = [this](std::string op1, std::string op2, std::string dest)
        { return suo(op1, op2, dest); };
        functions[14] = [this](std::string j1i, std::string j2i, std::string j3i)
        { return jb(j1i, j2i, j3i); };
    }

    // add memory-memory
    // opcode 0000
    bool am(std::string op1, std::string op2, std::string destination)
    {
        memory[M[destination]] = memory[M[op1]] + memory[M[op2]];
        return true;
    }

    // subtract memory-memory
    // opcode 0001
    bool sm(std::string op1, std::string op2, std::string destination)
    {
        memory[M[destination]] = memory[M[op1]] - memory[M[op2]];
        return true;
    }

    // multiply memory-memory
    // opcode 0010
    bool mm(std::string op1, std::string op2, std::string destination)
    {
        memory[M[destination]] = memory[M[op1]] * memory[M[op2]];
        return true;
    }

    // divide memory-memory
    // opcode 0011
    bool dm(std::string op1, std::string op2, std::string destination)
    {
        if (memory[M[op2]] == 0)
        {
            return false;
        }
        memory[M[destination]] = memory[M[op1]] / memory[M[op2]];
        return true;
    }

    // branch if not equal memory-memory
    // opcode 0100
    bool bnem(std::string op1, std::string op2, std::string target)
    {
        if (memory[M[op1]] != memory[M[op2]])
        {
            pc += std::stoi(target); // Adjust program counter
        }
        return true;
    }

    // set less than memory-memory
    // opcode 0101
    bool sltm(std::string op1, std::string op2, std::string destination)
    {
        memory[M[destination]] = (memory[M[op1]] < memory[M[op2]]) ? 1 : 0;
        return true;
    }

    // add immediate
    // opcode 0110
    bool ai(std::string op1, std::string op2i, std::string destination)
    {
        memory[M[destination]] = memory[M[op1]] + std::stoi(op2i);
        return true;
    }

    // subtract immediate
    // opcode 0111
    bool si(std::string op1, std::string op2i, std::string destination)
    {
        memory[M[destination]] = memory[M[op1]] - std::stoi(op2i);
        return true;
    }

    // multiply immediate
    // opcode 1000
    bool mi(std::string op1, std::string op2i, std::string destination)
    {
        memory[M[destination]] = memory[M[op1]] * std::stoi(op2i);
        return true;
    }

    // divide immediate
    // opcode 1001
    bool di(std::string op1, std::string op2i, std::string destination)
    {
        if (std::stoi(op2i) == 0)
        {
            return false;
        }
        memory[M[destination]] = memory[M[op1]] / std::stoi(op2i);
        return true;
    }

    // load constant immediate
    // opcode 1010
    bool lci(std::string op1i, std::string op2i, std::string destination)
    {
        memory[M[destination]] = std::stoi(op1i) + std::stoi(op2i);
        return true;
    }

    // subtract constant immediate
    // opcode 1011
    bool sci(std::string op1i, std::string op2i, std::string destination)
    {
        // is this right?
        memory[M[destination]] = std::stoi(op1i) + std::stoi(op2i);
        return true;
    }

    // load using offset
    // opcode 1100
    bool luo(std::string op1, std::string op2, std::string destination)
    {
        memory[M[destination]] = memory[M[op1]] + memory[M[op2]];
        return true;
    }

    // store using offset
    // opcode 1101
    bool suo(std::string op1, std::string op2, std::string destination)
    {
        memory[M[op1]] = memory[M[op2]];
        return true;
    }

    // jump back
    // opcode 1110
    bool jb(std::string j1i, std::string j2i, std::string j3i)
    {
        pc -= std::stoi(j1i) + std::stoi(j2i) + std::stoi(j3i);
        return true;
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

    // execute("0000","0000","0000","0000")
    // or
    // execute("am","M0","M0","M0")
    // or a combination of both?
    void execute(std::string opcode, std::string op1, std::string op2, std::string op3)
    {
        // print opcode, op1, op2, op3
        std::cout << opcode << " " << op1 << " " << op2 << " " << op3 << std::endl;
        int op = std::stoi(opcode, 0, 2);
        if (op >= 0 && op < functions.size())
        {
            if (functions[op](op1, op2, op3))
            {
                std::cout << "Operation successful." << std::endl;
            }
            else
            {
                std::cout << "Error: Operation failed." << std::endl;
            }
        }
        else
        {
            std::cout << "Error: Invalid opcode." << std::endl;
        }
        printMemory();
    }
};

int main()
{

    const int memSize = 16;
    std::vector<int> mainMemory(memSize, 0);

    ALU alu(mainMemory, memSize);

    // Example: Execute am with opcode 0
    alu.execute("1010", "2", "3", "M1");
    alu.execute("1010", "1", "2", "M2");
    alu.execute("0000", "M1", "M2", "M3"); // am operation (add mem-mem)

    return 0;
}
