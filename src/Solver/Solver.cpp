#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include "Solver.hpp"
#include <chrono>

double add(double a, double b) { return (a + b); }
double subtract(double a, double b) { return (a - b); }
double multiple(double a, double b) { return (a * b); }
double divide(double a, double b) { return (a / b); }

Solver::Solver()
{
    Expression addExpr(&add, '+');
    Expression subExpr(&subtract, '-');
    Expression mulExpr(&multiple, '*');
    Expression divExpr(&divide, '/');
    ops.push_back(addExpr);
    ops.push_back(subExpr);
    ops.push_back(mulExpr);
    ops.push_back(divExpr);
}

double Solver::convertInput()
{
    if (input.length() > 1)
    {
        if (input == "10")
            return 10;
        else
            return 0;
    }
    else
    {
        if (input[0] >= '2' && input[0] <= '9')
            return (int)(input[0]) - 48;

        if (input == "A")
            return 1;

        if (input == "J")
            return 11;

        if (input == "Q")
            return 12;

        if (input == "K")
            return 13;
    }

    return 0;
}

int Solver::getUserInput()
{

    int i;
    string inputline;
    int count = 0;

    cout << "Input 4 cards:" << endl;
    getline(cin, inputline);
    // cout << "line " << inputline << endl;

    for (auto x : inputline)
    {
        if (count > 4)
        {
            cout << "Invalid input. Too many inputs." << endl;
            return 0;
        }

        if (x == ' ')
        {
            num.push_back(convertInput());
            if (!num[count])
            {
                cout << "Invalid input. There's no " << input << " symbol in cards." << endl;
                return 0;
            }
            input = "";
            count++;
        }
        else
        {
            input = input + x;
        }
    }
    if (input != "")
    {
        num.push_back(convertInput());
        if (!num[count])
        {
            cout << "Invalid input. There's no " << input << " symbol in cards." << endl;
            return 0;
        }
        count++;
    }
    if (count < 4)
    {
        cout << "Invalid input. Too little input." << endl;
        return 0;
    }

    // for (i = 0; i < 4; i++)
    // {
    //     cin >> input;
    //     num.push_back(convertInput());
    //     if (!num[i])
    //     {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //         return 0;
    //     }
    // }

    return 1;
}

void Solver::getRandomizedInput()
{
    int i;

    srand(time(0));
    for (i = 0; i < 4; i++)
    {
        num.push_back(rand() % 13 + 1);
    }
}

void Solver::getInput()
{
    int choice = 999;

    cout << "Choose input method" << endl
         << "1. Cli Input" << endl
         << "2. Randomized Input" << endl;

    do
    {
        cin >> choice;
        if (choice == 1)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (!getUserInput())
            {
                num.clear();
                input = "";
            }
        }
        else if (choice == 2)
        {
            getRandomizedInput();
            cout << "Your 4 cards:" << endl
                 << num[0] << " " << num[1] << " " << num[2] << " " << num[3] << endl;
        }
    } while (choice > 2);
}

void Solver::writeSolution()
{
    string filename;
    cout << "Input filename (incl .txt): ";
    cin >> filename;
    ofstream MyFile("../../test/" + filename);

    for (auto sol : solution)
    {
        MyFile << sol << endl;
    }

    cout << "Solution saved in folder test" << endl;
    MyFile.close();
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
                }

                // (a op (b op c)) op d
                if (op3.eval(op1.eval(num[0], op2.eval(num[1], num[2])), num[3]) == 24)
                {
                    solution.push_back("(" + strA + " " + op1.getSymbol() + " " + "(" + strB + " " + op2.getSymbol() + " " + strC + "))" + " " + op3.getSymbol() + " " + strD);
                }

                // a op ((b op c) op d)
                if (op1.eval(num[0], op3.eval(op2.eval(num[1], num[2]), num[3])) == 24)
                {
                    solution.push_back(strA + " " + op1.getSymbol() + " " + "((" + strB + " " + op2.getSymbol() + " " + strC + ")" + " " + op3.getSymbol() + " " + strD + ")");
                }

                // a op (b op (c op d))
                // COMMENT THIS OUT TO GET THE SAME SOLUTION AS THE SOLVER ON THE WEB
                if (op1.eval(num[0], op2.eval(num[1], op3.eval(num[2], num[3]))) == 24)
                {
                    solution.push_back(strA + " " + op1.getSymbol() + " " + "(" + strB + " " + op2.getSymbol() + " " + "(" + strC + " " + op3.getSymbol() + " " + strD + "))");
                }

                // (a op b) op (c op d)
                if (op2.eval(op1.eval(num[0], num[1]), op3.eval(num[2], num[3])) == 24)
                {
                    solution.push_back("(" + strA + " " + op1.getSymbol() + " " + strB + ")" + " " + op2.getSymbol() + " " + "(" + strC + " " + op3.getSymbol() + " " + strD + ")");
                }
            }
        }
    }
}

void Solver::displaySolutions()
{
    if (solution.size() == 0)
    {
        cout << "No Solution." << endl;
    }
    else
    {
        cout << "Solution: " << solution.size() << endl;
        for (auto x : solution)
        {
            cout << x << endl;
        }
    }
}

void Solver::solveAll()
{
    int choice;
    auto start = chrono::high_resolution_clock::now();
    sort(num.begin(), num.end());

    do
    {
        solve();
        // TODO: ALTERNATES FOR NEXT PERMUTATION
    } while (next_permutation(num.begin(), num.end()));

    displaySolutions();
    auto end = chrono::high_resolution_clock::now();
    cout << "Execution time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    cout << "Save this solution? (1. YES, 2. NO)" << endl
         << "Your choice: ";
    cin >> choice;
    if (choice == 1)
    {
        writeSolution();
    }
}