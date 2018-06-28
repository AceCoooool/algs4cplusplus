#include <iostream>
#include <fstream>
#include "../head/SET.h"

using namespace std;

/**
 *  The {@code WhiteFilter} class provides a client for reading in a <em>whitelist</em>
 *  of words from a file; then, reading in a sequence of words from standard input,
 *  printing out each word that appears in the file.
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
    fstream filter("/home/ace/AceDev/C++/algorithm/ch3/data/list.txt");
    string key;
    while (filter >> key) {
        if (!st.contains(key)) {
            st.add(key);
        }
    }
    string tmp;
    while (getline(file, key)) {
        stringstream ss(key);
        while (ss >> tmp) {
            if (st.contains(tmp))
                cout << tmp << " ";
        }
        cout << endl;
    }
}