#include "controlunit.h"
#include "cstring"
#include<QVector>
bool ControlUnit::isIMMasOp1(const InstType v){
    return v == ADDI || v == LW || v == SW || v == SUBI;
}

ControlUnit::ControlUnit() : PC(0), BranchStall(0){
    memset((char*)&b1, 0, sizeof(b1) + sizeof(b2) + sizeof(b3) + sizeof(b4));   //I am proud of myself :D :D
    b2.IsIdle = b3.IsIdle = b4.IsIdle = true;
    b2.WE = b2.MemRW = b3.WE = b3.MemRW = b4.WE = false;
}
int ControlUnit::PopBranchStallFlag(){
    int t = BranchStall;
    BranchStall = 0;
    return t;
}

void ControlUnit::reset(){
    PC = BranchStall = 0;
    memset((char*)&b1, 0, sizeof(b1) + sizeof(b2) + sizeof(b3) + sizeof(b4));   //I am proud of myself :D :D
    b2.IsIdle = b3.IsIdle = b4.IsIdle = true;
    b2.WE = b2.MemRW = b3.WE = b3.MemRW = b4.WE = false;
}

void ControlUnit::FillBuffers(QVector<int> &if_id, QVector<int> &id_ex, QVector<int> &ex_mem, QVector<int> &mem_wb){
    if_id[0] = b1.Mnemonic;
    if_id[1] = b1.rs;
    if_id[2] = b1.rt;
    if_id[3] = b1.rd;
    if_id[4] = b1.imm;
    if_id[5] = b1.jaddr;

    id_ex[0] = b2.WE;
    id_ex[1] = b2.WAddr0;
    id_ex[2] = b2.Data0;
    id_ex[3] = b2.MemRW;
    id_ex[4] = b2.ALU_MEM;
    id_ex[5] = b2.ALUop;
    id_ex[6] = b2.Op0;
    id_ex[7] = b2.Op1;

    ex_mem[0] = b3.WE;
    ex_mem[1] = b3.WAddr0;
    ex_mem[2] = b3.WData0;
    ex_mem[3] = b3.MemRW;
    ex_mem[4] = b3.ALU_MEM;
    ex_mem[5] = b3.MemAddr0;

    mem_wb[0] = b4.WE;
    mem_wb[1] = b4.WAddr0;
    mem_wb[2] = b4.WData0;
}

int ControlUnit::Step(const Instruction &inst){
    if(!b4.IsIdle) InstQ.dequeue();
    if(BranchStall&1) return 0;
    InstQ.enqueue(inst);
    
    b1.Mnemonic = inst.Mnemonic;
    b1.rs = inst.rs;
    b1.rt = inst.rt;
    b1.rd = inst.rd;
    b1.imm = inst.imm;
    b1.jaddr = inst.jaddr;
    
    if(~BranchStall&1) PC++;
    return 0;
}

unsigned int ControlUnit::nInstructions(){
    return InstQ.size();
}

unsigned int ControlUnit::getPC(){
    return PC;
}

int ControlUnit::getRAddr0(){
    return b1.rs;
}
int ControlUnit::getRAddr1(){
    return b1.rt;
}
void ControlUnit::setData0(int val){
    if(BranchStall&1) return;
    if(b4.WE && b4.WAddr0 == b1.rs) val = b4.WData0;    //Forwarding from the output of the Memory Read
    if(b3.WE && !b3.ALU_MEM && b3.WAddr0 == b1.rs) val = b3.WData0;  //Forwarding from ALU output
    if(b3.WE && b3.ALU_MEM && b3.WAddr0 == b1.rs) {BranchStall|=1; return;}
    if(~BranchStall&2 && b1.Mnemonic == InstType::JR) {PC = val; BranchStall |= 2;}
    b2.Op0 = val;
}
void ControlUnit::setData1(int val){
    if(BranchStall&1) return;
    if(b4.WE && b4.WAddr0 == b1.rt) val = b4.WData0;    //Forwarding from the output of the Memory Read
    if(b3.WE && !b3.ALU_MEM && b3.WAddr0 == b1.rt) val = b3.WData0;  //Forwarding from ALU output
    else if(b3.WE && b3.ALU_MEM && b3.WAddr0 == b1.rt && b1.Mnemonic != InstType::SW) {BranchStall|=1; return;}
    else if(b3.WE && b3.ALU_MEM && b3.WAddr0 == b1.rt && b1.Mnemonic == InstType::SW) {b2.LWSWFlag = true; return;}
    if(isIMMasOp1(b1.Mnemonic)) b2.Data0 = val;
    else b2.Op1 = val;
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
void ControlUnit::setALUres(int val){
    if(b2.IsIdle) return;
    switch(b2.IsComparator){
    case 1: //BEQ
        if(val == 0) {PC = b2.Data0; BranchStall |= 2;}
        break;
    case 2: //BLE
        if(val <= 0) {PC = b2.Data0; BranchStall |= 2; }
        break;
    default:
        if(b2.IsDMemAddr) b3.MemAddr0 = val;
        else b3.WData0 = val;
    }
}

bool ControlUnit::getMemRW(){
    return b3.MemRW;
}
int ControlUnit::getMemAddr0(){
    return b3.MemAddr0;
}
int ControlUnit::getMemWData0(){
    return b3.WData0;
}
void ControlUnit::setMemRData0(int val){
    if(b3.IsIdle) return;
    if(b3.ALU_MEM) b4.WData0 = val;
    else b4.WData0 = b3.WData0;
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

void ControlUnit::Propagate12(){
    b2.IsIdle = BranchStall&1;
    //if(BranchStall&1) return;
    b2.WE = b1.Mnemonic != InstType::SW && b1.Mnemonic != InstType::BEQ && b1.Mnemonic != InstType::BLE &&
            b1.Mnemonic != InstType::J && b1.Mnemonic != InstType::JR;
    b2.MemRW = b1.Mnemonic == InstType::SW;
    b2.IsDMemAddr = b1.Mnemonic == InstType::LW || b1.Mnemonic == InstType::SW || b1.Mnemonic == InstType::JAL;
    b2.ALU_MEM = b1.Mnemonic == InstType::LW;
    if(b1.Mnemonic == InstType::BEQ) b2.IsComparator = 1;
    else if(b1.Mnemonic == InstType::BLE) b2.IsComparator = 2;
    else b2.IsComparator = 0;

    switch(b1.Mnemonic){
    case InstType::J:
    case InstType::JAL:
    case InstType::JR:
    case InstType::ADD:
    case InstType::ADDI:
    case InstType::LW:
    case InstType::SW:
        b2.ALUop = 0;
        break;
    case InstType::XOR:
        b2.ALUop = 1;
        break;
    case InstType::OR:
        b2.ALUop = 2;
        break;
    case InstType::SLT:
        b2.ALUop = 4;
        break;
    case InstType::BEQ:
    case InstType::BLE:
    case InstType::SUBI:
        b2.ALUop = 3;
        break;
    default: throw(QString("Unknown Mnemonic"));
    }
    if(isIMMasOp1(b1.Mnemonic)) b2.Op1 = b1.imm;
    else if(b1.Mnemonic == InstType::BLE || b1.Mnemonic == InstType::BEQ) b2.Data0 = PC + b1.imm;
    else b2.Data0 = b1.imm;
    if(b1.Mnemonic == InstType::JAL) {b2.WAddr0 = 31; b2.Data0 = PC;}
    else if(isIMMasOp1(b1.Mnemonic)) b2.WAddr0 = b1.rt;
    else b2.WAddr0 = b1.rd;
    if(~BranchStall&2 && (b1.Mnemonic == InstType::J || b1.Mnemonic == InstType::JAL)) PC = b1.jaddr;
    if(BranchStall) b2.WE = b2.MemRW = false;

}
void ControlUnit::Propagate23(){
    b3.IsIdle = b2.IsIdle;
    b3.WE = b2.WE;
    b3.MemRW = b2.MemRW;
    b3.ALU_MEM = b2.ALU_MEM;
    b3.WAddr0 = b2.WAddr0;
    if(b2.IsDMemAddr) b3.WData0 = b2.Data0;
    if(b2.LWSWFlag) b3.WData0 = b4.WData0;
    b2.LWSWFlag = false;
}
void ControlUnit::Propagate34(){
    b4.IsIdle = b3.IsIdle;
    b4.WE = b3.WE;
    b4.WAddr0 = b3.WAddr0;
    if(!b3.ALU_MEM) b4.WData0 = b3.WData0;
}

