#include <iostream>
#include <fstream>
#include "../head/QuickX.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input; quicksorts them
 * (using an optimized version of 2-way quicksort); 
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
    QuickX::sort(vec);
    QuickX::show(vec);
}