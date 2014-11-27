#ifndef CPU_H
#define CPU_H

#include<QVector>
#include"instruction.h"
#include"memory.h"
#include"registerfile.h"
#include"controlunit.h"

class CPU{
    Memory mem;
    RegisterFile RegFile;
    QVector<Instruction> IMem;
    ControlUnit CU;

public:
    CPU(const QVector<Instruction>&);
    CPU(const CPU&);
    CPU& operator=(const CPU&);

    void Fetch();
    void Read();
    void Execute();
    void Mem();
    void WriteBack();
    void Branch();

    bool Step();    //Takes elements from GUI to update
    bool EOI();     //End of Instructions
};

#endif // CPU_H
