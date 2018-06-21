#include <iostream>
#include <vector>
#include <algorithm>
#include "../head/Counter.h"

using namespace std;


const int seed = 100;

int main() {
    int n = 6;
    int trials = 60000;
    default_random_engine eng(seed);
    uniform_int_distribution<> dis(0, n - 1);
    // create n counters
    vector<Counter> hits;
    for (int i = 0; i < n; ++i)
        hits.push_back(Counter("counter" + to_string(i)));
    // increment trials counters at random
    for (int t = 0; t < trials; ++t) {
        hits[dis(eng)].increment();
    }
    // print results
    for (int i = 0; i < n; ++i)
        cout << hits[i] << endl;
}