#include "../head/NFA.h"
#include <iostream>

using namespace std;

/**
 * Unit tests the {@code NFA} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string regexp = "(A*B|AC)D";
    string txt = "AAAACD";

    NFA nfa(regexp);
    cout << nfa.recognizes(txt) << endl;
}