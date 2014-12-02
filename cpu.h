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
    bool Farray[5];

public:
    CPU();
    CPU(const CPU&);
    CPU& operator=(const CPU&);

    void SetVector(const QVector<Instruction>&); //beye3mel eh dah?? btset el IMem mn el parser
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
