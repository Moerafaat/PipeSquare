#include "controlunit.h"

bool ControlUnit::isIMMasOp1(const InstType v){
    //enum InstType{ADD, ADDI, XOR, LW, SW, BLE, J, SLT, JAL, JR, BEQ, OR, SUBI};
    return v == ADDI || v == LW || v == SW || v == SUBI;
}

ControlUnit::ControlUnit() : PC(0), BranchStall(0){
    b2.IsIdle = b3.IsIdle = b4.IsIdle = true;
}

int ControlUnit::Step(const Instruction &inst){
    if(!b4.IsIdle) InstQ.dequeue();
    int t = BranchStall;
    BranchStall = 0;
    if(t) return t;
    InstQ.enqueue(inst);
    
    b1.Mnemonic = inst.Mnemonic;
    b1.rs = inst.rs;
    b1.rt = inst.rt;
    b1.rd = inst.rd;
    b1.imm = inst.imm;
    b1.jaddr = inst.jaddr;
    
    PC++;
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
    if(b2.WE && b2.ALU_MEM && b3.MemAddr0 == b1.rs) {BranchStall|=1; return;}

    b2.Op0 = val;
}
void ControlUnit::setData1(int val){
    if(BranchStall&1) return;
    if(b4.WE && b4.WAddr0 == b1.rs) val = b4.WData0;    //Forwarding from the output of the Memory Read
    if(b3.WE && !b3.ALU_MEM && b3.WAddr0 == b1.rs) val = b3.WData0;  //Forwarding from ALU output
    else if(b2.WE && b2.ALU_MEM && b3.MemAddr0 == b1.rs) {BranchStall|=1; return;}

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
    switch(b2.IsComparator){
    case 1: //BEQ
        if(val == 0) {PC += b2.Data0; BranchStall |= 2;}
        break;
    case 2: //BLE
        if(val <= 0) {PC += b2.Data0; BranchStall |= 2; }
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
    b2.WE = b1.Mnemonic != InstType::SW && b1.Mnemonic != InstType::BEQ && b1.Mnemonic != InstType::BLE &&
            b1.Mnemonic != InstType::J && b1.Mnemonic != InstType::JR;
    b2.MemRW = b1.Mnemonic == InstType::SW;
    b2.IsDMemAddr = b1.Mnemonic == InstType::LW || b1.Mnemonic == InstType::SW;
    b2.ALU_MEM = b1.Mnemonic == InstType::LW;
    b2.IsIdle == false;

    b2.IsComparator = 0;
    switch(b1.Mnemonic){
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

    case InstType::BEQ:
    case InstType::BLE:
        b2.IsComparator = true;
    case InstType::SUBI:
        b2.ALUop = 3;
    default: throw("Unknown Mnemonic");
    }
    if(b1.Mnemonic == InstType::JAL) b2.WAddr0 == 31;
    else if(isIMMasOp1(b1.Mnemonic)) b2.WAddr0 = b1.rt;
    else b2.WAddr0 = b1.rd;
    if(isIMMasOp1(b1.Mnemonic)) b2.Op1 = b1.imm;
    else b2.Data0 = b1.imm;
    //Don't forget to execute the jump in the propagate
    if(b1.Mnemonic == InstType::J || b1.Mnemonic == InstType::JAL) PC = b1.jaddr;
    else if(b1.Mnemonic == InstType::JR) PC = b1.;//
}
