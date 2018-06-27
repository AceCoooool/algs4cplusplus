#include <iostream>
#include <fstream>
#include "../head/ST.h"

using namespace std;

int main() {
    int distinct = 0, words = 0;
    int minlen = 8;
    ST<string, int> st;
    fstream file("/home/ace/AceDev/C++/algorithm/ch3/data/tale.txt");
    string key;
    // compute frequency counts
    while (file >> key) {
        if (key.length() < minlen)
            continue;
        words++;
        if (st.contains(key))
            st.put(key, st.get(key) + 1);
        else {
            st.put(key, 1);
            distinct++;
        }
    }
    string max;
    int vmax = 0;
    // find a key with the highest frequency count
    for (auto s: st) {
        if (s.second > vmax) {
            max = s.first;
            vmax = s.second;
        }
    }
    cout << max << " " << vmax << " times" << endl;
    cout << "distinct = " << distinct << endl;
    cout << "words = " << words << endl;

}