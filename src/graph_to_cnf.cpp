#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<map>
#include<cstdlib> 
#include<vector>
using namespace std;

int main(int argc, char **argv){
    if(argc!=2){
        exit(0);
    }
    string inputfilename(argv[1]);
    string outputfilename(argv[1]);
    inputfilename += ".graph";
    outputfilename += ".satinput";
    ifstream infile(inputfilename.c_str());
    ofstream outfile(outputfilename.c_str());
    if(!(infile.is_open())){
        cout << "There is no such input file" << endl;
        exit(1);
    }
    int nv,ne,nsg;
    infile >> nv >> ne >> nsg;
    bool present[nsg+1][nv+1];
    vector<pair<int, int> > edges;
    int a,b;
    for(int i=0;i<ne;i++){
        infile >> a >> b;
        edges.push_back(make_pair(a,b));
        edges.push_back(make_pair(b,a));
    }
    infile.close();
    int numVar=0;
    vector<string> clauses;
    map<pair<int, int>, int> mpresent,medges,edgepresent;
    int mapping[nsg+1][nsg+1][nv+1],mapping2[nsg+1][nsg+1][nv+1];
    string ab;
    for(int i=1;i<=nsg;i++){
        for(int j=1;j<=nv;j++){
            numVar++;
            mpresent[make_pair(i,j)] = numVar;
        }
    }
    cout << nsg << " " << nv << " " << numVar << endl;
    for(int i=1;i<=nsg;i++){
        for(int j=i+1;j<=nsg;j++){
            for(int k=1;k<=nv;k++){
                numVar++;
                mapping[i][j][k] = numVar;
                ab = "-" + to_string(numVar) + " -" + to_string(mpresent[make_pair(i,k)])  + "  0";
                clauses.push_back(ab);
                ab = "-" + to_string(numVar) + " " + to_string(mpresent[make_pair(j,k)]) + "  0";
                clauses.push_back(ab);
                ab = to_string(numVar) + " " + to_string(mpresent[make_pair(i,k)]) + " -" + to_string(mpresent[make_pair(j,k)]) + "  0";
                clauses.push_back(ab);
                numVar++;
                mapping2[i][j][k] = numVar;
                ab = "-" + to_string(numVar) + " " + to_string(mpresent[make_pair(i,k)])  + "  0";
                clauses.push_back(ab);
                ab = "-" + to_string(numVar) + " -" + to_string(mpresent[make_pair(j,k)]) + "  0";
                clauses.push_back(ab);
                ab = to_string(numVar) + " -" + to_string(mpresent[make_pair(i,k)]) + " " + to_string(mpresent[make_pair(j,k)]) + "  0";
                clauses.push_back(ab);
            }
        }
    }
    for(int i=0;i<edges.size();i++){
        numVar++;
        int a = edges.at(i).first;
        int b = edges.at(i).second;
        medges[make_pair(a,b)] = numVar;
        ab = to_string(numVar) + "  0";
        clauses.push_back(ab);
    }
    for(int i=0;i<edges.size();i++){
        ab = "";
        int a = edges.at(i).first;
        int b = edges.at(i).second;
        for(int j=1;j<=nsg;j++){
            numVar++;
            edgepresent[make_pair(i,j)] = numVar;
            ab += (to_string(numVar) + " ");
            string t1 = "-" + to_string(numVar) + " " + to_string(mpresent[make_pair(j,a)]) + "  0";
            string t2 = "-" + to_string(numVar) + " " + to_string(mpresent[make_pair(j,b)]) + "  0";
            string t3 = "-" + to_string(mpresent[make_pair(j,a)]) + " -" + to_string(mpresent[make_pair(j,b)]) + " " + to_string(numVar) + "  0";
            clauses.push_back(t1);
            clauses.push_back(t2);
            clauses.push_back(t3);
        }
        ab += " 0";
        clauses.push_back(ab);
    }
    for(int i=1;i<=nsg;i++){
        for(int j=1;j<=nv;j++){
            for(int k=j+1;k<=nv;k++){
                bool exist = false;
                for(int l=0;l<edges.size();l++){
                    if(((edges.at(l).first==j && edges.at(l).second==k)||(edges.at(l).first==k && edges.at(l).second==j))){
                        exist = true;
                        break;
                    }
                }
                if(exist==false){
                    ab = "-" + to_string(mpresent[make_pair(i,j)]) + " -" + to_string(mpresent[make_pair(i,k)]) + "  0";
                    clauses.push_back(ab);
                }
            }
        }
    }
    for(int i=1;i<=nsg;i++){
        ab = "";
        for(int j=0;j<edges.size();j++){
            ab += (to_string(edgepresent[make_pair(j,i)]) + " ");
        }
        ab += " 0";
        clauses.push_back(ab);
    }
    string bc;
    for(int i=1;i<=nsg;i++){
        for(int j=i+1;j<=nsg;j++){
            ab = "";
            bc = "";
            for(int k=1;k<=nv;k++){
                ab +=  to_string(mapping[i][j][k]) + " ";
                bc +=  to_string(mapping2[i][j][k]) + " ";
            }
            ab += " 0";
            bc += " 0";
            clauses.push_back(ab);
            clauses.push_back(bc);
        }
    }
    if(!(outfile).is_open()){
        cout << "There is no such output file" << endl;
        exit(2);
    }
    outfile << ("p cnf " + to_string(numVar) + " " + to_string(clauses.size())) << endl;
    for(int i=0;i<clauses.size();i++){
        outfile << clauses.at(i) << endl;
    }
    outfile.close();
    return 0;
}