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
    int BranchStallFlag;
    int nCycles;
    int nStages;
    int tempPC;
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
    void getContext(QVector<int>&, QVector<int>&,
                    QVector<int>&, QVector<int>&, QVector<int>&, QVector<int>&,
                    int&, int&, bool&, bool&);
    bool isValidPC();
    void reset();
    bool Step();    //Returns Branch\Stall mask
};

#endif // CPU_H
