#include "FileWriter.hpp"
#include <fstream>
#include <iostream>

using namespace std;
FileWriter::FileWriter(vector<string> initSolution)
{
    solution = initSolution;
}

int FileWriter::writeFile(string path = "", string filename = "24solver_result.txt")
{
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