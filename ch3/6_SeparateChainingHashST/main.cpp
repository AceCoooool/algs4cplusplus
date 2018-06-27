#include <iostream>
#include <fstream>
#include "../head/SeparateChainingHashST.h"

using namespace std;

int main() {
    SeparateChainingHashST<string, int> st;
    fstream file("/home/ace/AceDev/C++/algorithm/ch3/data/tinyST.txt");
    string key;
    int cnt = 0;
    // compute frequency counts
    while (file >> key) {
        st.put(key, cnt);
        cnt++;
    }

    for (auto k: st)
        cout << k << " " << st.get(k) << endl;
}