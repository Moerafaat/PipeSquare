#include "registerfile.h"

RegisterFile::RegisterFile(){
    for (int i=0; i<RegisterCount; i++)
        this->reg[i]=0;
}

RegisterFile::RegisterFile(const RegisterFile & t){
    for (int i=0; i<RegisterCount; i++)
        this->reg[i]=t.reg[i];
}

RegisterFile &RegisterFile::operator=(const RegisterFile & t){
    for (int i=0; i<RegisterCount; i++)
        this->reg[i]=t.reg[i];
    return *this;

}

int &RegisterFile::operator[](unsigned int x){
    return reg[x];
}

