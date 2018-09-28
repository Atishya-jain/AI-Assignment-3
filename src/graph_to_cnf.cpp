#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<map>
#include<cstdlib> 
#include<vector>
#include<ctime>
#include<algorithm>
using namespace std;

int main(int argc, char **argv){
    clock_t n1= clock(),n2,n3,n4,n5;
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
        cout << "There is no such input file" << "\n";
        exit(1);
    }
    int nv,ne,nsg;
    infile >> nv >> ne >> nsg;
    bool present[nsg+1][nv+1];
    vector<pair<int, int> > edges;
    int a,b;
    int edd[nv+1][nv+1];
    for(int i=0;i<ne;i++){
        infile >> a >> b;
        edges.push_back(make_pair(a,b));
        //edges.push_back(make_pair(b,a));
        edd[a][b] = 1;
        edd[b][a] = 1;
    }
    infile.close();
    int numVar=0;
    vector<string> clauses;
    map<pair<int, int>, int> mpresent,edgepresent;
    int mapping[nsg+1][nsg+1][nv+1],mapping2[nsg+1][nsg+1][nv+1];

    string ab;
    for(int i=1;i<=nsg;i++){
        for(int j=1;j<=nv;j++){
            numVar++;
            mpresent[make_pair(i,j)] = numVar;
        }
    }
    for(int i=1;i<=nsg;i++){
        for(int j=i+1;j<=nsg;j++){
            for(int k=1;k<=nv;k++){
                numVar++;
                string opti = to_string(numVar);
                string optii = to_string(mpresent[make_pair(i,k)]);
                string optij = to_string(mpresent[make_pair(j,k)]);
                mapping[i][j][k] = numVar;
                ab = "-";
                ab += opti;
                ab += " -";
                ab += optii;
                ab += "  0";
                //ab = "-" + opti + " -" + optii  + "  0";
                clauses.push_back(ab);

                ab = "-";
                ab += opti;
                ab += " ";
                ab += optij;
                ab += "  0";
                //ab = "-" + opti + " " + optij + "  0";
                clauses.push_back(ab);

                ab = opti;
                ab += " ";
                ab += optii;
                ab += " -";
                ab += optij;
                ab += "  0";
                //ab = opti + " " + optii + " -" + optij + "  0";
                clauses.push_back(ab);
                numVar++;
                opti = to_string(numVar);
                mapping2[i][j][k] = numVar;
                ab = "-";
                ab += opti;
                ab += " ";
                ab += optii;
                ab += "  0";
                //ab = "-" + opti + " " + optii  + "  0";
                clauses.push_back(ab);

                ab = "-";
                ab += opti;
                ab += " -";
                ab += optij;
                ab += "  0";
                //ab = "-" + opti + " -" + optij + "  0";
                clauses.push_back(ab);

                ab = opti;
                ab += " -";
                ab += optii;
                ab += " ";
                ab += optij;
                ab += "  0";
                //ab = opti + " -" + optii + " " + optij + "  0";
                clauses.push_back(ab);
            }
        }
    }

    for(int i=0;i<edges.size();i++){
        numVar++;
        int a = edges.at(i).first;
        int b = edges.at(i).second;
        ab = to_string(numVar) + "  0";
        clauses.push_back(ab);
    }
    n3= clock();
    for(int i=0;i<edges.size();i++){
        ab = "";
        int a = edges.at(i).first;
        int b = edges.at(i).second;
        for(int j=1;j<=nsg;j++){
            numVar++;
            string opti = to_string(numVar);
            string optia = to_string(mpresent[make_pair(j,a)]);
            string optib = to_string(mpresent[make_pair(j,b)]);
            edgepresent[make_pair(i,j)] = numVar;
            ab += opti;
            ab += " ";
            //string t1 = "-" + opti + " " + optia + "  0";
            string t1 = "-";
            t1 += opti;
            t1 += " ";
            t1 += optia;
            t1 += "  0";
            //string t2 = "-" + opti + " " + optib + "  0";
            string t2 = "-";
            t2 += opti;
            t2 += " ";
            t2 += optib;
            t2 += "  0";
            //string t3 = "-" + optia + " -" + optib + " " + opti + "  0";
            string t3 = "-";
            t3 += optia;
            t3 += " -";
            t3 += optib;
            t3 += " ";
            t3 += opti;
            t3 += "  0";
            clauses.push_back(t1);
            clauses.push_back(t2);
            clauses.push_back(t3);
        }
        ab += " 0";
        clauses.push_back(ab);
    }
    n4= clock();
    cout << "4: " <<((double)(n4 - n3)/(CLOCKS_PER_SEC)) << "\n";
    for(int j=1;j<=nv;j++){
        for(int k=j+1;k<=nv;k++){
            if(!(edd[j][k]==1)){
                for(int i=1;i<=nsg;i++){
                    //ab = "-" + to_string(mpresent[make_pair(i,j)]) + " -" + to_string(mpresent[make_pair(i,k)]) + "  0";
                    ab = "-";
                    ab += to_string(mpresent[make_pair(i,j)]);
                    ab += " -";
                    ab += to_string(mpresent[make_pair(i,k)]);
                    ab += "  0";
                    clauses.push_back(ab);
                }
            }
        }
    }
    n5= clock();
    cout << "5: " <<((double)(n5 - n4)/(CLOCKS_PER_SEC)) << "\n";
    for(int i=1;i<=nsg;i++){
        ab = "";
        for(int j=0;j<edges.size();j++){
            ab += to_string(edgepresent[make_pair(j,i)]);
            ab += " ";
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
                ab +=  to_string(mapping[i][j][k]) ;
                ab += " ";
                bc +=  to_string(mapping2[i][j][k]) ;
                bc += " ";
            }
            ab += " 0";
            bc += " 0";
            clauses.push_back(ab);
            clauses.push_back(bc);
        }
    }
    if(!(outfile).is_open()){
        cout << "There is no such output file" << "\n";
        exit(2);
    }
    outfile << ("p cnf " + to_string(numVar) + " " + to_string(clauses.size())) << "\n";
    for(int i=0;i<clauses.size();i++){
        outfile << clauses.at(i) << "\n";
    }
    outfile.close();
    n2= clock();
    cout << ((double)(n2 - n1)/(CLOCKS_PER_SEC)) << "\n";
    return 0;
}