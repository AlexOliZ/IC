//g++ ex5.cpp -o ex5
//./ex5 <nome do ficheiro a analisar> (por exemplo: ./ex5 lusiadas.epub)

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc,char **argv){
    string r;
    map <char, int> histogram;
    char x;

    if(argc < 2)
    {
        cout << "Error: Should write <input filename>" << endl;
        return EXIT_FAILURE;
    } 

    ifstream ifs(argv[1]);
    ofstream ofs("histogram.txt");
   
    while(ifs.get(x)){
        if (histogram.find(x)!= histogram.end()){ //if the element exists
            histogram[x]++; //increase the number of elements
        }else{
            histogram[x]=1; //add an element
        }
    }

    //print to file
    for (auto it = histogram.begin(); it!=histogram.end();++it){
        ofs <<it->first<< "-" <<it->second << endl;
    }
    ofs.close();

    return 0;
}

