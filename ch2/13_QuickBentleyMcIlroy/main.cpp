#include <iostream>
#include <fstream>
#include "../head/QuickBentleyMcIlroy.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input; quicksorts them
 * (using an optimized version of quicksort);
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
    QuickBentleyMcIlroy::sort(vec);
    QuickBentleyMcIlroy::show(vec);
}