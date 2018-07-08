#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/**
* Reads in a sequence of text files specified as the first command-line
* arguments, concatenates them, and writes the results to the file
* specified as the last command-line argument.
*
* @param args the command-line arguments
*/
int main() {
    ofstream out("./data/out.txt");
    vector<string> files{"./data/in1.txt", "./data/in2.txt"};
    string tmp;
    for (int i = 0; i < files.size(); ++i) {
        ifstream in(files[i]);
        while (getline(in, tmp))
            out << tmp << endl;
        in.close();
    }
    out.close();
}