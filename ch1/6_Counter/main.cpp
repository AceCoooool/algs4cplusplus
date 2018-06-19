#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;


class Counter {
public:
    /**
     * Initializes a new counter starting at 0, with the given id.
     * @param id the name of the counter
     */
    Counter(string id) : name(id) {}

    /**
     * Increments the counter by 1.
     */
    void increment() {
        count++;
    }

    /**
     * Returns the current value of this counter.
     *
     * @return the current value of this counter
     */
    int tally() {
        return count;
    }

    /**
     * Returns a string representation of this counter.
     *
     * @return a string representation of this counter
     */
    string toString() {
        return to_string(count) + " " + name;
    }

    bool operator<(const Counter &rhs) {
        return (this->count < rhs.count);
    }

private:
    const string name;
    int count = 0;
};

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
        cout << hits[i].toString() << endl;
}