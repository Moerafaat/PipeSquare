#include "cpu.h"

CPU::CPU(){
}
CPU::CPU(const CPU &temp){
  this->mem=temp.mem;
  this->IMem=temp.IMem;
  this->RegFile=temp.RegFile;
  this->CU=temp.CU;
}
CPU& CPU::operator=(const CPU& temp){
    this->mem=temp.mem;
    this->IMem=temp.IMem;
    this->RegFile=temp.RegFile;
    this->CU=temp.CU;
    return *this;
}

void CPU:: Fetch(){
    CU.Step(IMem[CU.getPC()]);
}
void CPU::Read(){
    CU.setData0(CU.getRead0());
    CU.setData1(CU.getRead1());
}
void CPU::Execute(){
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
        CU.setALUres(tOp0-tOp1);//SUBI
        break;
    case 4://SLT
        if (tOp0<tOp1)
        CU.setALUres(1);
        else CU.setALUres(0);
        break;
    default:
           CU.setALUres(tOp0);
    }
}

void CPU::Mem(){
    CU.setMemRData0(mem[CU.getMemAddr0()]);
    if (CU.getMemWR()) mem[CU.getMemAddr0()]= CU.getMemWData0();
}

void CPU::WriteBack(){
   if (CU.getWE()) RegFile[CU.getWAddr0()]= CU.getWData0();
}

void CPU::Branch(){

}

bool CPU::Step(){

}

bool CPU::EOI(){

}
