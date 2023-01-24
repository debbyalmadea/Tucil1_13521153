#include <iostream>
#include "Expression.hpp"

Expression::Expression(double (*initFunc)(double, double), char initSym)
{
    /// @brief  konstruktor class Expression
    /// @param initFunc address dari fungsi untuk mengevaluasi ekspresi yang menerima 2 buah argumen
    /// @param initSym simbol operator dari ekspresi
    func = initFunc;
    sym = initSym;
}

double Expression::eval(double a, double b)
{
    // @return hasil evaluasi dari a op b
    return (*func)(a, b);
}

char Expression::getSymbol()
{
    // @return simbol dari operator
    return sym;
}