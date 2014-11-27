#ifndef PARSER_H
#define PARSER_H

#include<QVector>
#include<iostream>
#include"instruction.h"
class Parser
{
public:
    QVector<Instruction> parse(std::istream = std::cin);
};

#endif // PARSER_H
