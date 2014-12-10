#include "cpu.h"
#include<QtAlgorithms>

CPU::CPU() : nCycles(0), nStages(5), BranchStallFlag(0){
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
    if(CU.getPC() >= IMem.size() && nStages < 5) {tempPC = -1; return;}
    if(CU.getPC() >= IMem.size() || CU.getPC() < 0) throw(QString("PC out of bound"));
    tempPC = CU.getPC();
    CU.Step(IMem[CU.getPC()]);
}
void CPU::Read(){
    if(CU.getPC() >= IMem.size() && nStages < 4) return;
    if(CU.getRAddr0() < 0 || CU.getRAddr0() >= RegFile.RegisterCount) throw(QString("Register address out of bound"));
    if(CU.getRAddr1() < 0 || CU.getRAddr1() >= RegFile.RegisterCount) throw(QString("Register address out of bound"));
    CU.setData0(RegFile[CU.getRAddr0()]);
    CU.setData1(RegFile[CU.getRAddr1()]);
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
    if(CU.getMemAddr0() < 0 || CU.getMemAddr0() >= mem.WordCount) throw(QString("Memory Index out of bound"));
    CU.setMemRData0(mem[CU.getMemAddr0()]);
    if (CU.getMemRW()) mem[CU.getMemAddr0()]= CU.getMemWData0();

    CU.Propagate34();
}
void CPU::WriteBack(){
    if(CU.getPC() >= IMem.size() && nStages < 1) return;
    if(CU.getWAddr0() < 0 || CU.getWAddr0() >= RegFile.RegisterCount) throw(QString("Register address out of bound"));
    if(CU.getWE()) RegFile[CU.getWAddr0()] = CU.getWData0();
}

bool CPU::Step(){
    nCycles++;
    switch(nCycles){      //You will like this one! :D
    default:    WriteBack();
    case 4:     Mem();
    case 3:     Execute();
    case 2:     Read();
    case 1:     Fetch();
    }
    BranchStallFlag = 0;
    BranchStallFlag = CU.PopBranchStallFlag();
    if(CU.getPC() >= IMem.size() && ~BranchStallFlag&1) nStages--;    //Need to check the correctness;
    return nStages;
}

void CPU::getContext(QVector<int> &rf, QVector<int> &memory,
                     QVector<int> &IF_ID, QVector<int> &ID_EX, QVector<int> &EX_MEM, QVector<int> &MEM_WB,
                     int &PC, int &Cycles, bool &IsStall, bool &IsBranch){
    rf.resize(RegFile.RegisterCount);
    memory.resize(mem.WordCount);
    for(int i = 0; i < RegFile.RegisterCount; i++) rf[i] = RegFile[i];
    for(int i = 0; i < mem.WordCount; i++) memory[i] = mem[i];
    CU.FillBuffers(IF_ID, ID_EX, EX_MEM, MEM_WB);
    PC = tempPC;
    Cycles = nCycles;
    IsStall = BranchStallFlag&1;
    IsBranch = BranchStallFlag&2;
}

bool CPU::isValidPC(){
    return tempPC >= 0 && tempPC < IMem.size();
}

void CPU::reset(){
    CU.reset();
    nCycles = BranchStallFlag = 0;
    nStages = 5;
    for(int i = 0; i < RegFile.RegisterCount; i++) RegFile[i] = 0;
    for(int i = 0; i < mem.WordCount; i++) mem[i] = 0;
}
