#include "cpu.h"
#include<QtAlgorithms>

CPU::CPU() : nCycles(0), nStages(5){
}
CPU::CPU(const CPU &temp){
    this->mem=temp.mem;
    this->IMem=temp.IMem;
    this->RegFile=temp.RegFile;
    this->CU=temp.CU;
    this->nCycles = temp.nCycles;
    this->nStages = temp.nStages;
}
CPU& CPU::operator=(const CPU& temp){
    this->mem=temp.mem;
    this->IMem=temp.IMem;
    this->RegFile=temp.RegFile;
    this->CU=temp.CU;
    return *this;
}

void CPU::SetVector(const QVector<Instruction> & inst){
    this->IMem = inst;
}

void CPU::Fetch(){
    if(CU.getPC() >= IMem.size() && nStages < 5) return;
    CU.Step(IMem[CU.getPC()]);
}
void CPU::Read(){
    if(CU.getPC() >= IMem.size() && nStages < 4) return;
    CU.setData0(CU.getRAddr0());
    CU.setData1(CU.getRAddr1());
    CU.Propagate12();
}
void CPU::Execute(){
    if(CU.getPC() >= IMem.size() && nStages < 3) return;
    int tOp0 = CU.getOp0();
    int tOp1 = CU.getOp1();
    int tALUop = CU.getALUOp();
    switch (tALUop){
    case 0:
        CU.setALUres(tOp0+tOp1);//ADD or ADDI or SW or LW
        break;
    case 1:
        CU.setALUres(tOp0^tOp1);//XOR
        break;
    case 2:
        CU.setALUres(tOp0|tOp1);//OR
        break;
    case 3:
        CU.setALUres(tOp0-tOp1);//SUBI or BLE or BEQ
        break;
    case 4://SLT
        if (tOp0<tOp1) CU.setALUres(1);
        else CU.setALUres(0);
        break;
    default:    throw("Invalid ALUop");       
    }
    CU.Propagate23();
}
void CPU::Mem(){
    if(CU.getPC() >= IMem.size() && nStages < 2) return;
    CU.setMemRData0(mem[CU.getMemAddr0()]);
    if (CU.getMemRW()) mem[CU.getMemAddr0()]= CU.getMemWData0();
    CU.Propagate34();
}
void CPU::WriteBack(){
    if(CU.getPC() >= IMem.size() && nStages < 1) return;
    if (CU.getWE()) RegFile[CU.getWAddr0()] = CU.getWData0();
}

int CPU::Step(){
    nCycles++;
    switch(nCycles){      //You will like this one! :D
    default:    WriteBack();
    case 4:     Mem();
    case 3:     Execute();
    case 2:     Read();
    case 1:     Fetch();
    }
    if(CU.getPC() >= IMem.size()) nStages--;    //Need to check the correctness;
    return nStages;
}

bool CPU::EOI(){
    return nStages == 0;
}
