#include <regex>
#include <QRegExp>
#include <QTextStream>
#include <QMap>
#include <QDebug>
#include "parser.h"

using namespace std;

QVector<Instruction> Parser::parse(QFile& file){
    QVector<Instruction> instructions;
    Instruction current;
    QMap<QString, InstType> mnem;

    mnem.insert("ADD", ADD); mnem.insert("XOR", XOR); mnem.insert("SLT", SLT); mnem.insert("OR", OR);
    mnem.insert("ADDI", ADDI); mnem.insert("SUBI", SUBI); mnem.insert("BEQ", BEQ); mnem.insert("BLE", BLE);
    mnem.insert("LW", LW); mnem.insert("SW", SW);
    mnem.insert("J", J); mnem.insert("JAL", JAL); mnem.insert("JR", JR);

    QRegExp whitespace("^(\\s*)?$");
    QRegExp ops_3("\\s*(ADD|XOR|SLT|OR|ADDI|SUBI|BEQ|BLE)\\s+\\$(\\d+)\\s*,\\s*\\$(\\d+)\\s*,\\s*(\\$?\\d+)\\s*");
    QRegExp ops_2("\\s*(LW|SW)\\s+\\$(\\d+)\\s*,\\s*(\\d+)\\s*\\(\\s*\\$(\\d+)\\s*\\)\\s*");
    QRegExp ops_1("\\s*(J|JAL|JR)\\s+(\\$?\\d+)\\s*");
    QString error = "Error: Specify the file to be compiled first";

    if(!file.open(QFile::ReadOnly)) throw(error);
    QTextStream stream(&file);
    QString row;
    unsigned int counter=1;
    while(!stream.atEnd()){
        row = stream.readLine();
        if(ops_3.indexIn(row) != -1){ //3 operand instructions
            current.RawInst = row;
            current.Mnemonic = mnem[ops_3.cap(1)];
            if(current.Mnemonic == ADD || current.Mnemonic == XOR || current.Mnemonic == SLT || current.Mnemonic == OR){
                if(ops_3.cap(4).at(0) != '$') throw("Error: Problem at instruction " + QString::number(counter));
                current.rs = atoi(ops_3.cap(3).toStdString().c_str());
                current.rt = atoi(ops_3.cap(4).toStdString().substr(1).c_str());
                current.rd = atoi(ops_3.cap(2).toStdString().c_str());
                current.imm = 0;
                current.jaddr = 0;
                try{
                    isvalid_reg(current.rs, counter); isvalid_reg(current.rt, counter); isvalid_reg(current.rd, counter);
                }catch(QString error){throw error;}
            }
            else{
                if(ops_3.cap(4).at(0) == '$') throw("Error: Problem at instruction " + QString::number(counter));
                current.rs = atoi(ops_3.cap(3).toStdString().c_str());
                current.rt = atoi(ops_3.cap(2).toStdString().c_str());
                if(current.Mnemonic == BEQ || current.Mnemonic == BLE) swap(current.rs, current.rt);
                current.rd = 0;
                current.imm = atoi(ops_3.cap(4).toStdString().c_str());
                current.jaddr = 0;
                try{
                    isvalid_reg(current.rs, counter); isvalid_reg(current.rt, counter);
                }catch(QString error){throw error;}
            }
        }
        else if(ops_2.indexIn(row) != -1){ //2 operand instructions
            current.RawInst = row;
            current.Mnemonic = mnem[ops_2.cap(1)];
            current.rs = atoi(ops_2.cap(4).toStdString().c_str());
            current.rt = atoi(ops_2.cap(2).toStdString().c_str());
            current.rd = 0;
            current.imm = atoi(ops_2.cap(3).toStdString().c_str());
            current.jaddr = 0;
            try{
                isvalid_reg(current.rs, counter); isvalid_reg(current.rt, counter);
            }catch(QString error){throw error;}
        }
        else if(ops_1.indexIn(row) != -1){ //1 operand instrutions
            current.RawInst = row;
            current.Mnemonic = mnem[ops_1.cap(1)];
            if(current.Mnemonic == JR){
                if(ops_1.cap(2).at(0) != '$') throw("Error: Problem at instruction " + QString::number(counter));
                current.rs = atoi(ops_1.cap(2).toStdString().substr(1).c_str());
                current.rt = 0;
                current.rd = 0;
                current.imm = 0;
                current.jaddr = 0;
                try{
                    isvalid_reg(current.rs, counter);
                }catch(QString error){throw error;}
            }
            else{
                if(ops_1.cap(2).at(0) == '$') throw("Error: Problem at instruction " + QString::number(counter));
                current.rs = 0;
                current.rt = 0;
                current.rd = 0;
                current.imm = 0;
                current.jaddr = atoi(ops_1.cap(2).toStdString().c_str());
                try{
                    isvalid_reg(current.jaddr, counter);
                }catch(QString error){throw error;}
            }
        }
        else if(whitespace.indexIn(row) != -1) continue;
        else throw("Error: Problem at instruction " + QString::number(counter));
        instructions.push_back(current);
        counter++;
    }
    return instructions;
}

void Parser::isvalid_reg(int val, int counter){
    if(val<0 || val>=RegisterFile::RegisterCount) throw("Error: Register address out of range at instruction " + QString::number(counter));
}
