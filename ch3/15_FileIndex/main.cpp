#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../head/ST.h"
#include "../head/SET.h"

// TODO: add a fstream to filename map
using namespace std;

/**
 *  The {@code FileIndex} class provides a client for indexing a set of files,
 *  specified as command-line arguments. It takes queries from standard input
 *  and prints each file that contains the given query.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/35applications">Section 3.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

auto split = [](string s, char delim) {
    vector<string> tokens;
    stringstream ss(s);
    string tmp;
    while (getline(ss, tmp, delim)) {
        if (tmp != "")
            tokens.push_back(tmp);
    }
    return tokens;
};

int main() {
    vector<string> files{"/home/ace/AceDev/C++/algorithm/ch3/data/ex1.txt",
                         "/home/ace/AceDev/C++/algorithm/ch3/data/ex2.txt",
                         "/home/ace/AceDev/C++/algorithm/ch3/data/ex3.txt",
                         "/home/ace/AceDev/C++/algorithm/ch3/data/ex4.txt"};
    string tmp;
    ST<string, SET<string>> st;
    for (auto file: files) {
        fstream f(file);
        while (f >> tmp) {
            if (!st.contains(tmp)) st.put(tmp, SET<string>());
            st.get(tmp).add(file);
        }
    }
    cout << "please input query (-1 means break): " << endl;
    string query;
    while (cin >> query) {
        if (query == "-1")
            break;
        if (st.contains(query)) {
            for (auto f: st.get(query)) {
                cout << f << endl;
            }
        }
    }
}