#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include"instruction.h"
#include<QQueue>

class ControlUnit{
    struct IF_ID{
        InstType Mnemonic;
        int rs, rt, rd;
        int imm;
        int jaddr;
    };
    struct ID_EX{
        bool WE, MemRW;
        bool ALU_MEM;
        bool IsDMemAddr;
        int ALUop;
        int IsComparator;
        bool IsIdle;    //Used only for stalling
        bool LWSWFlag;

        int Op0, Op1;
        int Data0;
        int WAddr0;
    };
    struct EX_MEM{
        bool WE, MemRW;
        bool ALU_MEM;
        bool IsIdle;     //Used only for stalling

        int MemAddr0;
        int WAddr0;
        int WData0;
    };
    struct MEM_WB{
        bool IsIdle;     //Used only for stalling

        bool WE;
        int WAddr0;
        int WData0;
    };
   
    IF_ID b1;
    ID_EX b2;
    EX_MEM b3;
    MEM_WB b4;
    unsigned int PC;
    QQueue<Instruction> InstQ;
    int BranchStall;
    void Decode();
    bool isIMMasOp1(const InstType); //(is immediate as Op1) returns whether instruction is I format
public:
    ControlUnit();
    int PopBranchStallFlag();
    void reset();
    void FillBuffers(QVector<int>&, QVector<int>&, QVector<int>&, QVector<int>&);
    int Step(const Instruction&);
    unsigned int nInstructions();
    unsigned int getPC();
    
    int getRAddr0();
    int getRAddr1();
    void setData0(int);
    void setData1(int);
    
    int getOp0();
    int getOp1();
    int getALUOp();
    void setALUres(int);
    
    bool getMemRW();
    int getMemAddr0();
    int getMemWData0();
    void setMemRData0(int);
    
    bool getWE();
    int getWAddr0();
    int getWData0();
    
    void Propagate12(); // Propagates from buffer 1 to 2
    void Propagate23(); // Propagates from buffer 2 to 3
    void Propagate34(); // Propagates from buffer 3 to 4
};

#endif // CONTROLUNIT_H
