#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main(int argc, char **argv){
    if(argc!=2){
        exit(0);
    }
    string inputfilename1(argv[1]);
    string inputfilename2(argv[1]);
    string outputfilename(argv[1]);
    inputfilename1 += ".graph";
    inputfilename2 += ".satoutput";
    outputfilename += ".subgraphs";
    ifstream infile1(inputfilename1.c_str());
    ifstream infile2(inputfilename2.c_str());
    ofstream outfile(outputfilename.c_str());
    if(!(infile1.is_open())){
        cout << "There is no such input file" << endl;
        exit(1);
    }
    if(!(infile2.is_open())){
        cout << "There is no such input file" << endl;
        exit(2);
    }
    if(!(outfile).is_open()){
        cout << "There is no such output file" << endl;
        exit(3);
    }
    string ans;
    infile2 >> ans;
    ans = ans.substr(0,2);
    if(ans.compare("UN")==0){
        outfile << 0 << endl;
        outfile.close();
    }
    else{
        int nv,ne,nsg;
        infile1 >> nv >> ne >> nsg;
        infile1.close();
        for(int i=1;i<=nsg;i++){
            outfile << "#" + to_string(i) + " ";
            int a,count = 0;
            string s = "";
            for(int j=1;j<=nv;j++){
                infile2 >> a;
                if(a>0){
                    count++;
                    s += to_string(j) + " ";
                }
            }
            outfile << count << endl;
            outfile << s.substr(0,s.length() - 1) << endl;
        }
        outfile.close();    
    }
    return 0;
}