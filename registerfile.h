#ifndef REGISTERFILE_H
#define REGISTERFILE_H

class RegisterFile{
public:
    static const unsigned int RegisterCount = 32;
private:
    int reg[RegisterCount];
public:
    RegisterFile();
    RegisterFile(const RegisterFile&);
    RegisterFile& operator=(const RegisterFile&);
    int operator[](unsigned int)const;
    int &operator[](unsigned int);
};

#endif // REGISTERFILE_H
