#include <iostream>
#include <fstream>
#include "../head/BST.h"

using namespace std;

int main() {
    BST<string, int> st;
    fstream file("/home/ace/AceDev/C++/algorithm/ch3/data/tinyST.txt");
    string key;
    int cnt = 0;
    // compute frequency counts
    while (file >> key) {
        st.put(key, cnt);
        cnt++;
    }

    vector<string> mid = st.midOrder();
    for (auto a: mid)
        cout << a << " " << st.get(a) << endl;
    cout << "----------level order-----------" << endl;
    vector<string> level = st.levelOrder();
    for (auto a:level)
        cout << a << " " << st.get(a) << endl;

}