#include <iostream>
#include <fstream>
#include "../head/ST.h"

using namespace std;

int main() {
    ST<string, int> st;
    fstream file("/home/ace/AceDev/C++/algorithm/ch3/data/tinyST.txt");
    string tmp;
    int cnt = 0;
    while (file >> tmp) {
        st.put(tmp, cnt++);
    }
    for (auto s: st)
        cout << s.first << " " << s.second << endl;
}