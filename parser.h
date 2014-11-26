#ifndef PARSER_H
#define PARSER_H

#include<QVector>
#include<iostream>
#include"instruction.h"
class Parser
{
public:
    QVector<Instruction> parse(std::istream = cin);
};

#endif // PARSER_H
