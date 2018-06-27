#include <iostream>
#include <fstream>
#include "../head/BinarySearchST.h"

using namespace std;

int main() {
    BinarySearchST<string, int> st;
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