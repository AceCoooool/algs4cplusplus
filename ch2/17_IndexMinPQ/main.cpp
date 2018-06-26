#include <iostream>
#include "../head/IndexMinPQ.h"

using namespace std;

/**
 * Unit tests the {@code IndexMinPQ} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    // insert a bunch of strings
    vector<string> strs{"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};
    IndexMinPQ<string> pq(strs.size());
    for (int i = 0; i < strs.size(); ++i)
        pq.insert(i, strs[i]);
    // delete and print each key
    while (!pq.isEmpty()) {
        int i = pq.delMin();
        cout << i << " " << strs[i] << endl;
    }

    // reinsert the same strings
    for (int i = 0; i < strs.size(); ++i)
        pq.insert(i, strs[i]);

    cout << "------for each form-------" << endl;
    // print each key using the iterator
    for (int i : pq) {
        cout << i << " " << strs[i] << endl;
    }
    while (!pq.isEmpty())
        pq.delMin();
}