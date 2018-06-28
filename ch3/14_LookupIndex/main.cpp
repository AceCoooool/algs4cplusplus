#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../head/ST.h"

using namespace std;

/**
 *  The {@code LookupIndex} class provides a data-driven client for reading in a
 *  key-value pairs from a file; then, printing the values corresponding to the
 *  keys found on standard input. Keys are strings; values are lists of strings.
 *  The separating delimiter is taken as a command-line argument. This client
 *  is sometimes known as an <em>inverted index</em>.
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
    string filename = "/home/ace/AceDev/C++/algorithm/ch3/data/aminoI.csv";
    char separator = ',';
    fstream file(filename);

    ST<string, vector<string>> st;
    ST<string, vector<string>> ts;

    string line;
    while (getline(file, line)) {
        vector<string> fields = split(line, separator);
        string key = fields[0];
        for (int i = 1; i < fields.size(); ++i) {
            string val = fields[i];
            // TODO: there is a bug
            if (!st.contains(key)) st.put(key, {val});
            else st.get(key).push_back(val);
            if (!ts.contains(val)) ts.put(val, {key});
            else ts.get(val).push_back(key);
        }
    }
    cout << "Done indexing" << endl;
    // read queries from standard input, one per line
    cout << "please input index or value: (-1 means break)" << endl;
    string query;
    while (cin >> query) {
        if (st.contains(query)) {
            for (auto vals: st.get(query))
                cout << " " << vals << endl;
        }
        if (ts.contains(query)) {
            for (auto keys: ts.get(query))
                cout << " " << keys << endl;
        }
    }
}