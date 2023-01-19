#include "Solver/Solver.hpp"
#include "FileWriter/FileWriter.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <chrono>

using namespace std;

double convertInput(string input)
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

int getUserInput(vector<double> *num)
{
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
            (*num).push_back(convertInput(input));
            if (!(*num)[count])
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
        (*num).push_back(convertInput(input));
        if (!(*num)[count])
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

void getRandomizedInput(vector<double> *num)
{
    int i;

    srand(time(0));
    for (i = 0; i < 4; i++)
    {
        (*num).push_back(rand() % 13 + 1);
    }
}

vector<double> getInput()
{
    int choice = 999;
    vector<double> num;
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
            while (!getUserInput(&num))
            {
                num.clear();
                cout << endl;
            }
            cout << endl;
        }
        else if (choice == 2)
        {
            getRandomizedInput(&num);
            cout << "Your 4 cards are:" << endl
                 << num[0] << " " << num[1] << " " << num[2] << " " << num[3] << endl
                 << endl;
        }
    } while (choice > 2);

    return num;
}

int main()
{
    vector<double> num;
    int choice = 999;

    num = getInput();
    Solver solver(num[0], num[1], num[2], num[3]);

    auto start = chrono::high_resolution_clock::now();
    solver.solveAll();
    auto end = chrono::high_resolution_clock::now();
    cout << endl
         << "Execution time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

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
            FileWriter fileWriter(solver.solution);
            string filename;

            cout << ">> Input filename (incl .txt): ";
            cin >> filename;

            while (!fileWriter.writeFile("../test/", filename))
            {
                cout << ">> Input filename (incl .txt): ";
                cin >> filename;
            }

            cout << "File saved in folder test!" << endl;
        }

    } while (choice > 2);
    return 0;
}