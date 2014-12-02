#include "registerfile.h"

RegisterFile::RegisterFile(){
    for (int i=0; i<RegisterCount; i++)
        this->reg[i]=0;
}

RegisterFile::RegisterFile(const RegisterFile & t){
    for (int i=0; i<RegisterCount; i++)
        this->reg[i]=t[i];
}

RegisterFile &RegisterFile::operator=(const RegisterFile & t){
    for (int i=0; i<RegisterCount; i++)
        this->reg[i]=t[i];
    return *this;

}

int RegisterFile::operator[](unsigned int x) const{
    return reg[x];
}

int &RegisterFile::operator[](unsigned int x){
    return reg[x];
}

