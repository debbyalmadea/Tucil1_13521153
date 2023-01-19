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
    vector<string> solution;
    vector<Expression> ops;
    string input;
    double convertInput();
    int getUserInput();
    void getRandomizedInput();

public:
    Solver();
    void getInput();
    void writeSolution();
    void solve();
    void solveAll();
    void displaySolutions();
};

#endif