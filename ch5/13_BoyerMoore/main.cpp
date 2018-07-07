#include "../head/BoyerMoore.h"
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

    BoyerMoore boyermoore1(pat);
    BoyerMoore boyermoore2(pattern, 256);
    int offset1 = boyermoore1.search(txt);
    int offset2 = boyermoore2.search(text);

    // print results
    cout << "text:    " + txt << endl;

    cout << "pattern: ";
    for (int i = 0; i < offset1; i++)
        cout << " ";
    cout << pat << endl;

    cout << "pattern: ";
    for (int i = 0; i < offset2; i++)
        cout << " ";
    cout << pat << endl;

}