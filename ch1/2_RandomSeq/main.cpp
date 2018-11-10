#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

random_device rd;
mt19937 g(rd());

/**
 * Reads in two command-line arguments lo and hi and prints n uniformly
 * random real numbers in [lo, hi) to standard output.
 *
 * @param args the command-line arguments
 */
int main() {
    int n;
    double lo, hi;
    cout << "Prints numbers: ";
    cin >> n;
    cout << "Range number (lo, high): ";
    cin >> lo >> hi;
    // uniform[lo, high)
    uniform_real_distribution<double> dis(lo, hi);
    for (int i = 0; i < n; ++i)
        cout << setprecision(4) << dis(g) << "  ";
    cout << endl;
}