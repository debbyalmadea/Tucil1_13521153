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

Solver::Solver()
{
    // @brief konstruktor untuk class Solver

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

double Solver::convertInput(string input)
{
    // @brief mengubah input menjadi angka yang dapat dioperasikan
    /* @return 0 jika input tidak valid, 1 jika input valid
    dan berhasil diubah */
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

        if (input == "A" || input == "a")
            return 1;

        if (input == "J" || input == "j")
            return 11;

        if (input == "Q" || input == "q")
            return 12;

        if (input == "K" || input == "k")
            return 13;
    }

    return 0;
}

void Solver::printCards()
{
    // @brief mencetak kartu dengan format A B C D
    for (int i = 0; i < 4; i++)
    {
        if (num[i] == 1)
            cout << "A";
        else if (num[i] == 11)
            cout << "J";
        else if (num[i] == 12)
            cout << "Q";
        else if (num[i] == 13)
            cout << "K";
        else
            cout << num[i];

        cout << " ";
    }
}

int Solver::getUserInput()
{
    // @brief mendapatkan input dari user melalui cli
    // @return 0 jika input tidak valid, 1 jika valid
    int i;
    string inputline;
    string input = "";
    int count = 0;

    cout << ">> Input 4 cards: ";
    getline(cin, inputline);

    for (auto x : inputline)
    {
        if (count > 4)
        {
            cout << "Invalid input. Too many inputs." << endl;
            return 0;
        }

        if (x == ' ')
        {
            (num).push_back(convertInput(input));
            if (!(num)[count])
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
        (num).push_back(convertInput(input));
        if (!(num)[count])
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

    return 1;
}

void Solver::getRandomizedInput()
{
    // @brief mendapatkan input secara random
    int i;

    srand(time(0));
    for (i = 0; i < 4; i++)
    {
        (num).push_back(rand() % 13 + 1);
    }
}

void Solver::getInput()
{
    // @brief interface untuk memperoleh input kartu
    int choice = 999;
    cout << "Welcome to 24 Solver!" << endl;
    cout << "====================" << endl;
    cout << "Choose input method" << endl
         << "1. Cli Input" << endl
         << "2. Randomized Input" << endl;
    cout << "====================" << endl;
    do
    {
        cout << ">> Your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (!getUserInput())
            {
                num.clear();
                cout << endl;
            }
            cout << endl;
        }
        else if (choice == 2)
        {
            getRandomizedInput();
            cout << "Your 4 cards are:" << endl;
            printCards();
            cout << endl
                 << endl;
        }
    } while (choice > 2);
}

int Solver::writeSolution(string path, string filename)
{
    // @brief menulis solusi pada file
    // @param path path dari file
    // @param filename nama dari file, termasuk extensionnya
    // @return 0 jika gagal menulis file, 1 jika berhasil
    try
    {
        ofstream MyFile(path + filename);
        for (auto sol : solution)
        {
            MyFile << sol << endl;
        }
        MyFile.close();
        return 1;
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
        return 0;
    }
}

void Solver::solve()
{
    // @brief mendapatkan solusi untuk 1 buah permutasi kartu
    string strA, strB, strC, strD;
    double eps = 1e-9;
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
                // ((a op1 b) op2 c) op3 d
                if (abs(op3.eval(op2.eval(op1.eval(num[0], num[1]), num[2]), num[3]) - 24) < eps)
                {
                    solution.push_back("((" + strA + " " + op1.getSymbol() + " " + strB + ")" + " " + op2.getSymbol() + " " + strC + ")" + " " + op3.getSymbol() + " " + strD + ")");
                    totalSolution++;
                }

                // (a op1 (b op2 c)) op3 d
                if (abs(op3.eval(op1.eval(num[0], op2.eval(num[1], num[2])), num[3]) - 24) < eps)
                {
                    solution.push_back("(" + strA + " " + op1.getSymbol() + " " + "(" + strB + " " + op2.getSymbol() + " " + strC + "))" + " " + op3.getSymbol() + " " + strD);
                    totalSolution++;
                }

                // a op1 ((b op2 c) op3 d)
                if (abs(op1.eval(num[0], op3.eval(op2.eval(num[1], num[2]), num[3])) - 24) < eps)
                {
                    solution.push_back(strA + " " + op1.getSymbol() + " " + "((" + strB + " " + op2.getSymbol() + " " + strC + ")" + " " + op3.getSymbol() + " " + strD + ")");
                    totalSolution++;
                }

                // a op1 (b op2 (c op3 d))
                if (abs(op1.eval(num[0], op2.eval(num[1], op3.eval(num[2], num[3]))) - 24) < eps)
                {
                    solution.push_back(strA + " " + op1.getSymbol() + " " + "(" + strB + " " + op2.getSymbol() + " " + "(" + strC + " " + op3.getSymbol() + " " + strD + "))");
                    totalSolution++;
                }

                // (a op1 b) op2 (c op3 d)
                if (abs(op2.eval(op1.eval(num[0], num[1]), op3.eval(num[2], num[3])) - 24) < eps)
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
    // @brief mencetak semua solusi
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
    // @brief menukar urutan 2 buah kartu cardA dan cardB
    double tempA = *(cardA);
    *(cardA) = *(cardB);
    *(cardB) = tempA;
}

void Solver::getPermutation(vector<double>::iterator vec, int vecLen)
{
    /* @brief mencari semua permutasi dari kartu sekaligus
    memanggil prosedur solve untuk mendapatkan solusi
    dari permutasi tersebut */
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
            if (!visited[(int)*(vec + i) - 1])
            {
                visited[(int)*(vec + i) - 1] = true;
                swapCard(vec, (vec + i));
                getPermutation(vec + 1, vecLen - 1);
                swapCard(vec, (vec + i));
            }
        }
    }
}

void Solver::solveAll()
{
    /* @brief mencari semua solusi dari semua permutasi dari
     permainan kartu 24 */
    int choice = 999;
    auto start = chrono::high_resolution_clock::now();
    getPermutation(num.begin(), 4);
    auto end = chrono::high_resolution_clock::now();
    displaySolutions();
    cout << endl
         << "Elapsed time: " << (double)(chrono::duration_cast<chrono::microseconds>(end - start).count()) / 1000 << "ms" << endl;

    cout << endl
         << "===================" << endl
         << "Save this solution?" << endl
         << "1. Yes" << endl
         << "2. No" << endl
         << "===================" << endl;
    do
    {
        cout << ">> Your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            string filename;

            cout << ">> Input filename (incl .txt): ";
            cin >> filename;

            while (!writeSolution("../test/", filename))
            {
                cout << ">> Input filename (incl .txt): ";
                cin >> filename;
            }

            cout << "File saved in folder test!" << endl;
        }

    } while (choice > 2);
}