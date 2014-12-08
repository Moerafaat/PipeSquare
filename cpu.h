#ifndef CPU_H
#define CPU_H

#include <QVector>
#include <functional>
#include "instruction.h"
#include "memory.h"
#include "registerfile.h"
#include "controlunit.h"

class CPU{
    Memory mem;
    RegisterFile RegFile;
    QVector<Instruction> IMem;
    ControlUnit CU;
    int nCycles;
    int nStages;
    void Fetch();
    void Read();
    void Execute();
    void Mem();
    void WriteBack();
public:
    CPU();
    CPU(const CPU&);
    CPU& operator=(const CPU&);

    void SetVector(const QVector<Instruction>&);

    int Step();    //Returns Branch\Stall mask
    bool EOI();     //End of Instructions
};

#endif // CPU_H
