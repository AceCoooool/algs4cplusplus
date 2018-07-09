#include <iostream>
#include <fstream>
#include "../head/Shell.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input; Shellsorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    Shell::sort(vec);
    Shell::show(vec);
}