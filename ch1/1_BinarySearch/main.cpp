#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "../head/BinarySearch.h"

using namespace std;

// Note: use relative path (clion need to change working directory)

/**
 * Reads in a sequence of integers from the whitelist file, specified as
 * a command-line argument; reads in integers from standard input;
 * prints to standard output those integers that do <em>not</em> appear in the file.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream input("./data/tinyW.txt");
    vector<int> whitelist;
    int t;
    while (input >> t) {
        whitelist.push_back(t);
    }
    sort(whitelist.begin(), whitelist.end());
    ifstream check("./data/tinyT.txt");
    while (check >> t) {
        int idx = BinarySearch::indexOf(whitelist, t);
        if (idx == -1)
            cout << t << endl;
    }
}