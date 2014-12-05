#include "memory.h"

Memory::Memory(){
    for (int i=0; i<WordCount; i++)
        this->mem[i]=0;
}

Memory::Memory(const Memory & t)
{
    for (int i=0; i<WordCount; i++)
        this->mem[i]=t[i];
}

Memory &Memory::operator=(const Memory & t)
{
    for (int i=0; i<WordCount; i++)
        this->mem[i]=t[i];
    return *this;
}

int Memory::operator[](unsigned int x) const{
    return mem[x];
}

int &Memory::operator[](unsigned int x){
    return mem[x];
}
