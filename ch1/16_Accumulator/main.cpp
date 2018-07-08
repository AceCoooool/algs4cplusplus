#include <iostream>
#include <vector>
#include "../head/Accumulator.h"

using namespace std;

/**
 * Unit tests the {@code Interval2D} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    Accumulator stats;
    vector<double> nums{10.0, 12.0, 14.0, 2.0};
    for (auto n: nums) {
        stats.addDataValue(n);
    }
    cout << "n = " << stats.count() << endl;
    cout << "mean = " << stats.mean() << endl;
    cout << "stddev = " << stats.stddev() << endl;
    cout << "var = " << stats.var() << endl;
    cout << stats << endl;
}