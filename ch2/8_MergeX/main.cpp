#include <iostream>
#include <fstream>
#include "../head/MergeX.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input; mergesorts them
 * (using an optimized version of mergesort); 
 * and prints them to standard output in ascending order. 
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/words3.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    MergeX::sort(vec);
    MergeX::show(vec);
}