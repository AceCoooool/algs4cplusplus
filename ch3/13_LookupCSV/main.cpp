#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../head/ST.h"

using namespace std;

/**
 *  The {@code LookupCSV} class provides a data-driven client for reading in a
 *  key-value pairs from a file; then, printing the values corresponding to the
 *  keys found on standard input. Both keys and values are strings.
 *  The fields to serve as the key and value are taken as command-line arguments.
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
    int keyField = 0;
    int valField = 3;
    // symbol table
    ST<string, string> st;
    // read in the data from csv file
    fstream file("/home/ace/AceDev/C++/algorithm/ch3/data/amino.csv");
    string tmp;
    while (getline(file, tmp)) {
        vector<string> tokens = split(tmp, ',');
        string key = tokens[keyField];
        string val = tokens[valField];
        st.put(key, val);
    }

    string s;
    cout << "Please input the seeking key: (-1 mains break)" << endl;
    while (cin >> s) {
        if (s == "-1")
            break;
        if (st.contains(s))
            cout << st.get(s) << endl;
        else
            cout << "Not found" << endl;
    }
}