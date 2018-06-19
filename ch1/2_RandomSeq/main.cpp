#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const int seed = 100;

/**
 * Reads in two command-line arguments lo and hi and prints n uniformly
 * random real numbers in [lo, hi) to standard output.
 *
 * @param args the command-line arguments
 */
int main() {
    int n = 10;
    double lo = 0.0, hi = 1.0;
    // uniform[0.0, 1.0)
    default_random_engine e(seed);
    uniform_real_distribution<double> dis(0.0, 1.0);
    cout << fixed;
    for (int i = 0; i < n; ++i)
        cout << setprecision(4) << dis(e) << "  ";
    cout << endl;
    // uniform[lo, high)
    lo = 2.5, hi = 3.0;
    uniform_real_distribution<double> dis2(lo, hi);
    for (int i = 0; i < n; ++i)
        cout << setprecision(4) << dis2(e) << "  ";
    cout << endl;
}