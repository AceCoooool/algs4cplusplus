#include <iostream>
#include <vector>
#include <random>
#include "../head/Counter.h"

using namespace std;

random_device rd;
mt19937 g(rd());

/**
 * Reads two command-line integers n and trials; creates n counters;
 * increments trials counters at random; and prints results.
 *
 * @param args the command-line arguments
 */
int main() {
    int n = 6;
    int trials = 60000;
    uniform_int_distribution<> dis(0, n - 1);
    // create n counters
    vector<Counter> hits;
    for (int i = 0; i < n; ++i)
        hits.push_back(Counter("counter" + to_string(i)));
    // increment trials counters at random
    for (int t = 0; t < trials; ++t) {
        hits[dis(g)].increment();
    }
    // print results
    for (int i = 0; i < n; ++i)
        cout << hits[i] << endl;
}