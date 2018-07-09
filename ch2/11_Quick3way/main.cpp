#include <iostream>
#include <fstream>
#include "../head/Quick3way.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input; 3-way
 * quicksorts them; and prints them to standard output in ascending order. 
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
    Quick3way::sort(vec);
    Quick3way::show(vec);
}