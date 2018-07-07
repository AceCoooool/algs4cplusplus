#include "../head/RabinKarp.h"
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

    RabinKarp searcher(pat);
    int offset = searcher.search(txt);

    // print results
    cout << "text:    " + txt << endl;

    // from brute force search method 1
    cout << "pattern: ";
    for (int i = 0; i < offset; i++)
        cout << " ";
    cout << pat << endl;
}