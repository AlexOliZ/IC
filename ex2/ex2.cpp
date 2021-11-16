#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc,char **argv){
    char x;

    if(argc < 3){
        cout << "Error: Should write <input filename> <output filename>" << endl;
        return 0; 
    }
  
    //0 argumento -> ./a.out
    //1 argumento -> read file
    //2 argumento -> writable file
    
    ifstream ifs(argv[1]); //read from a file
    ofstream ofs(argv[2]); //write from a file

    while(ifs.get(x)){ //read from character to character and write to a file
        ofs<<x;
    }

    ofs.close();
    return 0;
}
