#include <iostream>
#include <fstream>
#include "../head/Inversions.h"

using namespace std;

/**
 * Reads a sequence of integers from standard input and
 * prints the number of inversions to standard output.
 *
 * @param args the command-line arguments
 */
int main() {
    vector<int> a{2, 4, 1, 6, 3};
    cout << Inversions::count(a) << endl;
}