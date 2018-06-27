#include <iostream>
#include <fstream>
#include "../head/SequentialSearchST.h"

using namespace std;

int main() {
    SequentialSearchST<string, int> st;
    fstream file("/home/ace/AceDev/C++/algorithm/ch3/data/tinyST.txt");
    string key;
    int cnt = 0;
    // compute frequency counts
    while (file >> key) {
        st.put(key, cnt);
        cnt++;
    }

    for (auto s: st) {
        cout << s << " " << st.get(s) << endl;
    }
}