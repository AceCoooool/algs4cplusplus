#include "../head/NFA.h"
#include <iostream>

using namespace std;

/**
 * Interprets the command-line argument as a regular expression
 * (supporting closure, binary or, parentheses, and wildcard)
 * reads in lines from standard input; writes to standard output
 * those lines that contain a substring matching the regular
 * expression.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/tinyL.txt");
    string regexp = "(.*(A*B|AC)D.*)";
    string line;
    NFA nfa(regexp);
    while (file >> line) {
        if (nfa.recognizes(line))
            cout << line << endl;
    }
}