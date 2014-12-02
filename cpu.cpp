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
    if (Farray[0])
        CU.Step(IMem[CU.getPC()]);
}
void CPU::Read(){
    if (Farray[1])
    {CU.setData0(CU.getRead0());
    CU.setData1(CU.getRead1());}
}
void CPU::Execute(){
    if (Farray[2])
    {
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
}

void CPU::Mem(){
    if (Farray[3])
    {CU.setMemRData0(mem[CU.getMemAddr0()]);
    if (CU.getMemWR()) mem[CU.getMemAddr0()]= CU.getMemWData0();}
}

void CPU::WriteBack(){
   if (Farray[4])
    {if (CU.getWE()) RegFile[CU.getWAddr0()]= CU.getWData0();}
}

void CPU::Branch(){

}

bool CPU::Step(){
    for (int i=0; i<5; i++) Farray[i]=false;
    int tnI = CU.nInstructions();
    int tPC = CU.getPC();
    int IMemSize = IMem.size();
    if (tnI==5)
        {
            for (int i=0; i<5; i++) Farray[i]=true;
            WriteBack();
            Mem();
            Execute();
            Read();
            Fetch();
            return true;
         }
    else
    {
        if ((tPC>=0)&&(tPC<IMemSize))
        {
            for (int i=0; i<tnI; i++) Farray[i]=true;
            WriteBack();
            Mem();
            Execute();
            Read();
            Fetch();
            return true;
        }
        else
        {
            for (int i=4; i<=(5-tnI); i--) Farray[i]=true;
            WriteBack();
            Mem();
            Execute();
            Read();
            Fetch();
            return true;
        }
        return false;
    }


}

bool CPU::EOI(){
    return (CU.getPC()>(IMem.size()+4));
}
