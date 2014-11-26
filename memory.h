#ifndef MEMORY_H
#define MEMORY_H

class Memory{
public:
    static const unsigned int WordCount = 1024;
private:
    int mem[WordCount];
public:
    Memory();
    Memory(const Memory&);
    Memory& operator=(const Memory&);
    int& operator[](unsigned int);
};

#endif // MEMORY_H
