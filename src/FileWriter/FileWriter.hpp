#ifndef __FILEWRITER__HPP__
#define __FILEWRITER__HPP__

#include "../Solver/Solver.hpp"
#include <vector>

class FileWriter
{
private:
    vector<string> solution;

public:
    FileWriter(vector<string> initSolution);
    int writeFile(string path, string filename);
};

#endif