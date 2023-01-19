#ifndef __EXPRESSION__HPP__
#define __EXPRESSION__HPP__
#include <iostream>

class Expression
{
private:
    double (*func)(double, double);
    char sym;

public:
    Expression(double (*initFunc)(double, double), char initSym);
    double eval(double a, double b);
    char getSymbol();
};

#endif