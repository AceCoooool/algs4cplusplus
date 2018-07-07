#include "../head/KMP.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Takes a pattern string and an input string as command-line arguments;
 * searches for the pattern string in the text string; and prints
 * the first occurrence of the pattern string in the text string.
 *
 * @param args the command-line arguments
 */
int main() {
    string pat = "abracadabra";
    string txt = "abacadabrabracabracadabrabrabracad";
    vector<char> pattern(pat.c_str(), pat.c_str() + pat.size());
    vector<char> text(txt.c_str(), txt.c_str() + txt.size());

    KMP kmp1(pat);
    int offset1 = kmp1.search(txt);

    KMP kmp2(pattern, 256);
    int offset2 = kmp2.search(text);

    // print results
    cout << "text:    " << txt << endl;

    cout << "pattern: ";
    for (int i = 0; i < offset1; i++)
        cout << " ";
    cout << pat << endl;

    cout << "pattern: ";
    for (int i = 0; i < offset2; i++)
        cout << " ";
    cout << pat << endl;
}