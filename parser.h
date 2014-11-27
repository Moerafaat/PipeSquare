#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QFile>
#include "instruction.h"
class Parser{
public:
    QVector<Instruction> parse(const QFile&);
};

#endif // PARSER_H
