#ifndef ALU_H
#define ALU_H

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <iomanip>
#include <bitset>

class ALU
{
private:
    std::map<std::string, int> M;
    std::map<uint8_t, std::string> OPCODES;
    std::map<uint8_t, std::string> MEMORY_REGISTERS;

    int pc;
    std::vector<std::function<int(uint8_t, uint8_t, uint8_t)>> functions;
    std::vector<uint16_t> &memory;

public:
    ALU(std::vector<uint16_t> &mem, int pcInit);

    int am(uint8_t op1, uint8_t op2, uint8_t op3);
    int sm(uint8_t op1, uint8_t op2, uint8_t op3);
    int mm(uint8_t op1, uint8_t op2, uint8_t op3);
    int dm(uint8_t op1, uint8_t op2, uint8_t op3);
    int bnem(uint8_t op1, uint8_t op2, uint8_t op3);
    int sltm(uint8_t op1, uint8_t op2, uint8_t op3);
    int ai(uint8_t op1, uint8_t op2, uint8_t op3);
    int si(uint8_t op1, uint8_t op2, uint8_t op3);
    int mi(uint8_t op1, uint8_t op2, uint8_t op3);
    int di(uint8_t op1, uint8_t op2, uint8_t op3);
    int lci(uint8_t op1, uint8_t op2, uint8_t op3);
    int sci(uint8_t op1, uint8_t op2, uint8_t op3);
    int lo(uint8_t op1, uint8_t op2, uint8_t op3);
    int so(uint8_t op1, uint8_t op2, uint8_t op3);
    int jb(uint8_t op1, uint8_t op2, uint8_t op3);

    void printMemory();
    void printInColumns(const std::vector<uint16_t> &list, int columns);
    void printInColumnsInt(const std::vector<uint16_t> &list, int columns);
    void printPC();
    void printOPCODE(uint16_t opcode);
    void printEXECUTING(uint16_t opcode);
    int execute(uint16_t opcode);

    void setPC(int newPC);
    int getPC();
};

#endif // ALU_H
