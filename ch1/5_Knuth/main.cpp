#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "../head/Knuth.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input, shuffles
 * them, and prints out the results.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/cards.txt");
    string tmp;
    vector<string> a;
    while (file >> tmp) {
        a.push_back(tmp);
    }
    Knuth::shuffle(a);
    for (int i = 0; i < a.size(); ++i) {
        cout << setw(6) << left << a[i];
        if ((i + 1) % 13 == 0)
            cout << endl;
    }
}