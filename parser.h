#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QFile>
#include "instruction.h"
#include "registerfile.h"

class Parser{
    void isvalid_reg(int, int);
public:
    QVector<Instruction> parse(QFile&);
};

#endif // PARSER_H
