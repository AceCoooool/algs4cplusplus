#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "../head/BinarySearch.h"

using namespace std;

int main() {
    // TODO: change to relative path
    ifstream input("/home/ace/AceDev/C++/algorithm/ch1/data/tinyW.txt");
    vector<int> whitelist;
    int t;
    while (input >> t) {
        whitelist.push_back(t);
    }
    sort(whitelist.begin(), whitelist.end());
    ifstream check("/home/ace/AceDev/C++/algorithm/ch1/data/tinyT.txt");
    while (check >> t) {
        int idx = BinarySearch::indexOf(whitelist, t);
        if (idx == -1)
            cout << t << endl;
    }
}