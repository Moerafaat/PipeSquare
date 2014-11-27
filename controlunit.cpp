#include "controlunit.h"

ControlUnit::ControlUnit() : PC(0){
}

void ControlUnit::Step(const Instruction &inst){
    if(InstQ.size() == 5) InstQ.dequeue();
    InstQ.enqueue(inst);
    
    //Propagate();
    //Decode();
    
    b1.Mnemonic = inst.Mnemonic;
    b1.rs = inst.rs;
    b1.rt = inst.rt;
    b1.rd = inst.rd;
    b1.imm = inst.imm;
    b1.jaddr = inst.jaddr;
    
    PC++;
}

unsigned int ControlUnit::nInstructions(){
    return InstQ.size();
}

unsigned int ControlUnit::getPC(){
    return PC;
}

int ControlUnit::getRead0(){
    return b1.rs;
}
int ControlUnit::getRead1(){
    return b1.rt;
}

int ControlUnit::getOp0(){
    return b2.Op0;
}
int ControlUnit::getOp1(){
    return b2.Op1;
}
int ControlUnit::getALUOp(){
    return b2.ALUop;
}

bool ControlUnit::getMemWR(){
    return b3.MemWR;
}
int ControlUnit::getMemAddr0(){
    return b3.MemAddr0;
}
int ControlUnit::getMemWData0(){
    return b3.Data0;
}

bool ControlUnit::getWE(){
    return b4.WE;
}
int ControlUnit::getWAddr0(){
    return b4.WAddr0;
}
int ControlUnit::getWData0(){
    return b4.WData0;
}
