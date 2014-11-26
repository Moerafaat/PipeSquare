#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include<QString>

enum InstType{ADD, ADDI, XOR, LW, SW, BLE, J, SLT, JAL, JR, BEQ, OR, SUBI};
struct Instruction
{
    QString RawInst;
    InstType Mnemonic;
    int rs, rt, rd, imm, jaddr;
};

#endif // INSTRUCTION_H
