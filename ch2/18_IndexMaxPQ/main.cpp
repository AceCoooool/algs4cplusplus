#include <iostream>
#include <random>
#include <algorithm>
#include "../head/IndexMaxPQ.h"

using namespace std;
random_device rd;
mt19937 g(rd());
uniform_real_distribution<double> dis(0, 1);

/**
 * Unit tests the {@code IndexMinPQ} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    // insert a bunch of strings
    vector<string> strs{"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};
    IndexMaxPQ<string> pq(strs.size());
    for (int i = 0; i < strs.size(); ++i)
        pq.insert(i, strs[i]);

    // print each key using the iterator
    for (int i : pq) {
        cout << i << " " << strs[i] << endl;
    }
    cout << "-----after random increase and decrease-------" << endl;
    // increase or decrease the key
    for (int i = 0; i < strs.size(); i++) {
        if (dis(g) < 0.5)
            pq.increaseKey(i, strs[i] + strs[i]);
        else
            pq.decreaseKey(i, strs[i].substr(0, 1));
    }
    // delete and print each key
    while (!pq.isEmpty()) {
        string key = pq.maxKey();
        int i = pq.delMax();
        cout << i << " " << key << endl;
    }
    cout << "-----delete in random order-------" << endl;
    // reinsert the same strings
    for (int i = 0; i < strs.size(); i++) {
        pq.insert(i, strs[i]);
    }
    // delete them in random order
    vector<int> perm(strs.size());
    for (int i = 0; i < strs.size(); i++)
        perm[i] = i;
    shuffle(perm.begin(), perm.end(), g);
    for (int i = 0; i < perm.size(); i++) {
        string key = pq.keyOf(perm[i]);
        pq.delete_op(perm[i]);
        cout << perm[i] << " " << key << endl;
    }
}