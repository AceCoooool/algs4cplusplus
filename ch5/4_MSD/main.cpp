#include "../head/MSD.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Reads in a sequence of extended ASCII strings from standard input;
 * MSD radix sorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch5/data/shells.txt";
    fstream in(file);
    string tmp;
    vector<string> a;
    while (in >> tmp)
        a.push_back(tmp);

    int n = a.size();
    int w = a[0].length();

    // sort the strings
    MSD::sort(a);

    // print results
    for (int i = 0; i < n; ++i)
        cout << a[i] << endl;
}