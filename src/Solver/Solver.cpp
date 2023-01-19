#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <chrono>
#include "Solver.hpp"

double add(double a, double b) { return (a + b); }
double subtract(double a, double b) { return (a - b); }
double multiple(double a, double b) { return (a * b); }
double divide(double a, double b) { return (a / b); }

Solver::Solver(double numA, double numB, double numC, double numD)
{
    num.push_back(numA);
    num.push_back(numB);
    num.push_back(numC);
    num.push_back(numD);

    Expression addExpr(&add, '+');
    Expression subExpr(&subtract, '-');
    Expression mulExpr(&multiple, '*');
    Expression divExpr(&divide, '/');
    ops.push_back(addExpr);
    ops.push_back(subExpr);
    ops.push_back(mulExpr);
    ops.push_back(divExpr);

    totalSolution = 0;
}

void Solver::solve()
{
    string strA, strB, strC, strD;
    strA = to_string((int)num[0]);
    strB = to_string((int)num[1]);
    strC = to_string((int)num[2]);
    strD = to_string((int)num[3]);

    for (auto op1 : ops)
    {
        for (auto op2 : ops)
        {
            for (auto op3 : ops)
            {
                // ((a op b) op c) op d
                if (op3.eval(op2.eval(op1.eval(num[0], num[1]), num[2]), num[3]) == 24)
                {
                    solution.push_back("((" + strA + " " + op1.getSymbol() + " " + strB + ")" + " " + op2.getSymbol() + " " + strC + ")" + " " + op3.getSymbol() + " " + strD + ")");
                    totalSolution++;
                }

                // (a op (b op c)) op d
                if (op3.eval(op1.eval(num[0], op2.eval(num[1], num[2])), num[3]) == 24)
                {
                    solution.push_back("(" + strA + " " + op1.getSymbol() + " " + "(" + strB + " " + op2.getSymbol() + " " + strC + "))" + " " + op3.getSymbol() + " " + strD);
                    totalSolution++;
                }

                // a op ((b op c) op d)
                if (op1.eval(num[0], op3.eval(op2.eval(num[1], num[2]), num[3])) == 24)
                {
                    solution.push_back(strA + " " + op1.getSymbol() + " " + "((" + strB + " " + op2.getSymbol() + " " + strC + ")" + " " + op3.getSymbol() + " " + strD + ")");
                    totalSolution++;
                }

                // a op (b op (c op d))
                // COMMENT THIS OUT TO GET THE SAME SOLUTION AS THE SOLVER ON THE WEB
                if (op1.eval(num[0], op2.eval(num[1], op3.eval(num[2], num[3]))) == 24)
                {
                    solution.push_back(strA + " " + op1.getSymbol() + " " + "(" + strB + " " + op2.getSymbol() + " " + "(" + strC + " " + op3.getSymbol() + " " + strD + "))");
                    totalSolution++;
                }

                // (a op b) op (c op d)
                if (op2.eval(op1.eval(num[0], num[1]), op3.eval(num[2], num[3])) == 24)
                {
                    solution.push_back("(" + strA + " " + op1.getSymbol() + " " + strB + ")" + " " + op2.getSymbol() + " " + "(" + strC + " " + op3.getSymbol() + " " + strD + ")");
                    totalSolution++;
                }
            }
        }
    }
}

void Solver::displaySolutions()
{
    if (totalSolution == 0)
    {
        cout << "No Solution." << endl;
    }
    else
    {
        cout << "Total solution: " << totalSolution << endl
             << "List of solution(s):" << endl;
        for (auto x : solution)
        {
            cout << x << endl;
        }
    }
}

void Solver::swapCard(vector<double>::iterator cardA, vector<double>::iterator cardB)
{
    double tempA = *(cardA);
    *(cardA) = *(cardB);
    *(cardB) = tempA;
}

void Solver::getPermutation(vector<double>::iterator vec, int vecLen)
{
    bool visited[13];
    for (int i = 0; i < 13; i++)
    {
        visited[i] = false;
    }

    if (vecLen == 1)
    {
        solve();
    }
    else
    {
        for (int i = 0; i < vecLen; i++)
        {
            if (!visited[(int)*(vec + i)])
            {
                visited[(int)*(vec + i)] = true;
                swapCard(vec, (vec + i));
                getPermutation(vec + 1, vecLen - 1);
                swapCard(vec, (vec + i));
            }
        }
    }
}

void Solver::solveAll()
{
    getPermutation(num.begin(), 4);
    displaySolutions();
}