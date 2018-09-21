#include <iostream>
#include <vector>
#include "string.h"
#include "Util.h"
#include "input.h"
#include <cstdlib>
#include <fstream>
using namespace std;

void get_input(long long int& vertices, long long int& edges, long long int& num_sub, vector<vector<int> >& graph, string filename)
{
    vector<string> lines;
    string line;
    ifstream myfile(filename.c_str());
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(line);
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open input file";
        exit(0);
    }

    string delimiter = " ";
    vector<string> main_in;
    splitString(lines[0], delimiter, main_in);
    vertices = atoi(main_in[0].c_str());
    edges = atoi(main_in[1].c_str());
    num_sub = atoi(main_in[2].c_str());

    for(int i = 0; i<=vertices; i++){
        vector<int> vin;
        graph.push_back(vin);
    }

    for(int i = 1; i< lines.size(); i++){
        vector<string> in;
        splitString(lines[i], delimiter, in);
        graph[atoi(in[0].c_str())].push_back(atoi(in[1].c_str()));
        graph[atoi(in[1].c_str())].push_back(atoi(in[0].c_str()));
    }
}
