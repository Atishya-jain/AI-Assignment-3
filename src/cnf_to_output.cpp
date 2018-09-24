#include <iostream>
#include "string.h"
#include "input.h"
using namespace std;

void cnf_to_output(vector<vector<int> >& subgraphs, vector<vector<int> >& graph, vector<int>& satout, long long int vertices, long long int edges, long long int num_sub);

int main(int argc, char **argv){ 
    string inputfile1name(argv[1]);	
    string inputfile2name(argv[1]);	
    string outputfilename(argv[1]);
    inputfile1name += ".graph";
    inputfile2name += ".satoutput";
    outputfilename += ".subgraphs";
    vector<vector<int> > graph;
    long long int vertices, edges, num_sub;
    get_input(vertices, edges, num_sub, graph, inputfile1name);
    vector<int> satout;
    bool sat;
    get_input_sat(satout, inputfile2name, sat);
    vector<vector<int> > subgraphs;
    if(sat){
	    cnf_to_output(subgraphs, graph, satout, vertices, edges, num_sub);
    }
	final_output(subgraphs, sat, outputfilename);

    for(int i = 0; i<graph.size(); i++){
    	cout << i << ": ";
    	for(int j = 0; j< graph[i].size(); j++){
    		cout << graph[i][j] << " ";
    	}
    	cout << endl;
    }cout << endl;

    for(int i = 0; i<satout.size(); i++){
    	cout << satout[i] << " ";
    }cout << endl;
    
    return 0;
}

void cnf_to_output(vector<vector<int> >& subgraphs, vector<vector<int> >& graph, vector<int>& satout, long long int vertices, long long int edges, long long int num_sub){
    for(int i = 0; i<3; i++){
        vector<int> v;
        subgraphs.push_back(v);
    }

    subgraphs[0].push_back(1);
    subgraphs[0].push_back(2);
    subgraphs[0].push_back(3);
    subgraphs[1].push_back(1);
    subgraphs[1].push_back(4);
    subgraphs[1].push_back(5);
    subgraphs[1].push_back(2);
    subgraphs[2].push_back(3);
    subgraphs[2].push_back(4);
}