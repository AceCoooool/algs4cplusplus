#include <iostream>
#include <fstream>
#include "../head/SET.h"

using namespace std;

/**
 *  The {@code DeDup} class provides a client for reading in a sequence of
 *  words from standard input and printing each word, removing any duplicates.
 *  It is useful as a test client for various symbol table implementations.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/35applications">Section 3.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
int main() {
    SET<string> st;
    fstream file("/home/ace/AceDev/C++/algorithm/ch3/data/tinyTale.txt");
    string key;
    while (file >> key) {
        if (!st.contains(key)) {
            st.add(key);
            cout << key << endl;
        }
    }
}