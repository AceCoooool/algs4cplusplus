#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "../head/Knuth.h"

using namespace std;

/**
* Reads in a sequence of text files specified as the first command-line
* arguments, concatenates them, and writes the results to the file
* specified as the last command-line argument.
*
* @param args the command-line arguments
*/
int main() {
    // TODO: change to relative path
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/cards.txt");
    string tmp;
    vector<string> a;
    while (file >> tmp) {
        a.push_back(tmp);
    }
    Knuth::shuffle(a);
    for (int i = 0; i < a.size(); ++i) {
        cout << setw(6) << left << a[i];
        if ((i + 1) % 13 == 0)
            cout << endl;
    }
}