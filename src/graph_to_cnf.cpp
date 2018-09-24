#include <iostream>
#include "string.h"
#include "input.h"
using namespace std;

void graph_to_cnf(vector<vector<int> >& graph, vector<vector<int> >& clauses, long long int& num_variables, long long int vertices, long long int edges, long long int num_sub);

int main(int argc, char **argv){ 
    string inputfilename(argv[1]);
    string outputfilename(argv[1]);
    inputfilename += ".graph";
    outputfilename += ".satinput";
    vector<vector<int> > graph;
    long long int vertices, edges, num_sub;
    get_input(vertices, edges, num_sub, graph, inputfilename);
    vector<vector<int> > clauses;
    long long int num_variables = 0;
    graph_to_cnf(graph, clauses, num_variables, vertices, edges, num_sub);
    output_to_sat(clauses, num_variables, outputfilename);

    for(int i = 0; i<graph.size(); i++){
    	cout << i << ": ";
    	for(int j = 0; j< graph[i].size(); j++){
    		cout << graph[i][j] << " ";
    	}
    	cout << endl;
    }

    return 0;
}

void graph_to_cnf(vector<vector<int> >& graph, vector<vector<int> >& clauses, long long int& num_variables, long long int vertices, long long int edges, long long int num_sub){
    for(int i = 0; i<3; i++){
        vector<int> v;
        clauses.push_back(v);
    }
    num_variables = 5;

    clauses[0].push_back(1);
    clauses[0].push_back(-5);
    clauses[0].push_back(4);
    clauses[1].push_back(-1);
    clauses[1].push_back(5);
    clauses[1].push_back(3);
    clauses[1].push_back(4);
    clauses[2].push_back(-3);
    clauses[2].push_back(-4);
}