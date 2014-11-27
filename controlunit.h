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
        bool WE, MemWR;        
        int ALUop;
        
        int Op0, Op1;
        int Data0;
        int WAddr0;
    };
    struct EX_MEM{
        bool WE, MemWR;
        
        int MemAddr0;
        int WAddr0;
        int Data0;
    };
    struct MEM_WB{
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
    
    void Propagate();
    void Decode();
    
public:
    ControlUnit();

    void Step(const Instruction&);
    unsigned int nInstructions();
    unsigned int getPC();
    
    int getRead0();
    int getRead1();
    void setData0(int);
    void setData1(int);
    
    int getOp0();
    int getOp1();
    int getALUOp();
    void setALUres(int);
    
    bool getMemWR();
    int getMemAddr0();
    int getMemWData0();
    void setMemRData0(int);
    
    bool getWE();
    int getWAddr0();
    int getWData0();
};

#endif // CONTROLUNIT_H
