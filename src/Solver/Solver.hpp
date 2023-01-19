#ifndef __SOLVER__HPP__
#define __SOLVER__HPP__
#include <vector>
#include <iostream>
#include "../Expression/Expression.hpp"

using namespace std;

class Solver
{
private:
    vector<double> num;
    vector<Expression> ops;
    void getPermutation(vector<double>::iterator vec, int vecLen);
    void swapCard(vector<double>::iterator cardA, vector<double>::iterator cardB);

public:
    Solver(double numA, double numB, double numC, double numD);
    int totalSolution;
    vector<string> solution;
    void solve();
    void solveAll();
    void displaySolutions();
};

#endif