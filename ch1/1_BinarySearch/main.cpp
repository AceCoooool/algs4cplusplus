#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

/**
* Returns the index of the specified key in the specified array.
*
* @param  a the array of integers, must be sorted in ascending order
* @param  key the search key
* @return index of key in array {@code a} if present; {@code -1} otherwise
*/
int indexOf(vector<int> &a, int key) {
    int lo = 0, hi = a.size() - 1;
    while (lo <= hi) {
        // Key is in a[lo..hi] or not present.
        int mid = lo + (hi - lo) / 2;
        if (key < a[mid]) hi = mid - 1;
        else if (key > a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

int main() {
    // TODO: change to relative path
    ifstream input("/home/ace/AceDev/C++/algorithm/ch1/data/tinyW.txt");
    vector<int> whitelist;
    int t;
    while (input >> t) {
        whitelist.push_back(t);
    }
    sort(whitelist.begin(), whitelist.end());
    ifstream check("/home/ace/AceDev/C++/algorithm/ch1/data/tinyT.txt");
    while (check >> t) {
        int idx = indexOf(whitelist, t);
        if (idx == -1)
            cout << t << endl;
    }
}