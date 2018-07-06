#include "../head/TST.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Unit tests the {@code TST} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch5/data/shellsST.txt";
    fstream in(file);
    string tmp;
    TST<int> st;
    int cnt = 0;
    vector<string> a;
    while (in >> tmp)
        st.put(tmp, cnt++);

    // print results
    if (st.size() < 100) {
        cout << "keys(\"\"):" << endl;
        auto res = st.keys();
        while (!res.empty()) {
            cout << res.front() << endl;
            res.pop();
        }
        cout << endl;
    }

    cout << "longestPrefixOf(\"shellsort\"):" << endl;
    cout << st.longestPrefixOf("shellsort") << endl;
    cout << endl;

    cout << "longestPrefixOf(\"quicksort\"):" << endl;
    cout << st.longestPrefixOf("quicksort") << endl;
    cout << endl;

    cout << "keysWithPrefix(\"shor\"):" << endl;
    auto res = st.keysWithPrefix("shor");
    while (!res.empty()) {
        cout << res.front() << endl;
        res.pop();
    }
    cout << endl;

    cout << "keysThatMatch(\".he.l.\"):" << endl;
    auto res2 = st.keysThatMatch(".he.l.");
    while (!res2.empty()) {
        cout << res2.front() << endl;
        res2.pop();
    }
    cout << endl;
}