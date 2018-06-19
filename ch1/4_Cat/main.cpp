#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int seed = 100;

/**
* Reads in a sequence of text files specified as the first command-line
* arguments, concatenates them, and writes the results to the file
* specified as the last command-line argument.
*
* @param args the command-line arguments
*/
int main() {
    // TODO: change to relative path
    ofstream out("/home/ace/AceDev/C++/algorithm/ch1/4_Cat/out.txt");
    vector<string> files{"/home/ace/AceDev/C++/algorithm/ch1/4_Cat/in1.txt",
                         "/home/ace/AceDev/C++/algorithm/ch1/4_Cat/in2.txt"};
    string tmp;
    for (int i = 0; i < files.size(); ++i) {
        ifstream in(files[i]);
        while (getline(in, tmp))
            out << tmp << endl;
        in.close();
    }
    out.close();
}