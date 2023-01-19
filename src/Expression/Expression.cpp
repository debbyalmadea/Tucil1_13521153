#include <iostream>
#include "Expression.hpp"

Expression::Expression(double (*initFunc)(double, double), char initSym)
{
    func = initFunc;
    sym = initSym;
}

double Expression::eval(double a, double b)
{
    return (*func)(a, b);
}

char Expression::getSymbol()
{
    return sym;
}