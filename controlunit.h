#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include"instruction.h"
#include<QQueue>

class ControlUnit{
    struct Buff1{
    };
    struct Buff2{
    };
    struct Buff3{
    };
    struct Buff4{
    };
    struct Buff5{
    };
    Buff1 b1;
    Buff2 b2;
    Buff3 b3;
    Buff4 b4;
    Buff5 b5;
    unsigned int PC;
    QQueue<Instruction> inst;
public:
    ControlUnit();

    void Step(const Instruction&);
    unsigned int nInstructions();
};

#endif // CONTROLUNIT_H
