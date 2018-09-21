#include <iostream>
#include "string.h"
#include "input.h"
using namespace std;

int main(int argc, char **argv){ 
    string inputfilename(argv[1]);
    string outputfilename(argv[1]);
    inputfilename += ".graph";
    outputfilename += ".satinput";
    vector<vector<int> > graph;
    long long int vertices, edges, num_sub;
    get_input(vertices, edges, num_sub, graph, inputfilename);

    for(int i = 0; i<graph.size(); i++){
    	cout << i << ": ";
    	for(int j = 0; j< graph[i].size(); j++){
    		cout << graph[i][j] << " ";
    	}
    	cout << endl;
    }
    return 0;
}
