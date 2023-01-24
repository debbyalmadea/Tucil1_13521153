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
    int totalSolution;
    vector<string> solution;
    void getPermutation(vector<double>::iterator vec, int vecLen);
    void swapCard(vector<double>::iterator cardA, vector<double>::iterator cardB);
    int getUserInput();
    void getRandomizedInput();
    double convertInput(string input);
    void printCards();
    int writeSolution(string path = "", string filename = "24solver_result.txt");
    void solve();
    void displaySolutions();

public:
    Solver();
    void getInput();
    void solveAll();
};

#endif