#ifndef INPUT1_H
#define	INPUT1_H

#include "string.h"
#include <vector>
#include <cstdlib>
using namespace std;

void get_input(long long int& vertices, long long int& edges, long long int& num_sub, vector<vector<int> >& graph, string filename);
void get_input_sat(vector<int>& satout, string filename, bool& sat);
void output_to_sat(vector<vector<int> >& clauses, long long int num_variables, string filename);
void final_output(vector<vector<int> >& subgraphs, bool sat, string filename);

#endif