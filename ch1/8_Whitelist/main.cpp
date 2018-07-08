#include <iostream>
#include <fstream>
#include "../head/StaticSetofInts.h"

using namespace std;

/**
 * Reads in a sequence of integers from the whitelist file, specified as
 * a command-line argument. Reads in integers from standard input and
 * prints to standard output those integers that are not in the file.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream in("./data/tinyW.txt");
    int tmp;
    vector<int> white;
    while (in >> tmp)
        white.push_back(tmp);
    StaticSETofInts *p = new StaticSETofInts(white);
    ifstream in2("./data/tinyT.txt");
    while (in2 >> tmp) {
        if (!p->contains(tmp))
            cout << tmp << endl;
    }
}