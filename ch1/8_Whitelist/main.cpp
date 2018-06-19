#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class StaticSETofInts {
public:
    /**
     * Initializes a set of integers specified by the integer array.
     * @param keys the array of integers
     * @throws IllegalArgumentException if the array contains duplicate integers
     */
    StaticSETofInts(vector<int> keys) : a(keys) {
        sort(a.begin(), a.end());
        for (int i = 1; i < a.size(); ++i) {
            if (a[i] == a[i - 1])
                throw runtime_error("Argument arrays contains duplicate keys.");
        }
    }

    /**
     * Returns either the index of the search key in the sorted array
     * (if the key is in the set) or -1 (if the key is not in the set).
     * @param key the search key
     * @return the number of keys in this set less than the key (if the key is in the set)
     * or -1 (if the key is not in the set).
     */
    int rank(int key) {
        int lo = 0, hi = a.size() - 1;
        while (lo <= hi) {
            auto mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
        return -1;
    }

    /**
     * Is the key in this set of integers?
     * @param key the search key
     * @return true if the set of integers contains the key; false otherwise
     */
    bool contains(int key) {
        return rank(key) != -1;
    }

private:
    vector<int> a;
};

int main() {
    ifstream in("/home/ace/AceDev/C++/algorithm/ch1/data/tinyW.txt");
    int tmp;
    vector<int> white;
    while (in >> tmp)
        white.push_back(tmp);
    StaticSETofInts *p = new StaticSETofInts(white);
    ifstream in2("/home/ace/AceDev/C++/algorithm/ch1/data/tinyT.txt");
    while (in2 >> tmp) {
        if (!p->contains(tmp))
            cout << tmp << endl;
    }
}