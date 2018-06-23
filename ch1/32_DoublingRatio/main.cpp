#include <iostream>
#include "../head/DoublingTest.h"

using namespace std;

/**
 * Prints table of running times to call {@code ThreeSum.count()}
 * for arrays of size 250, 500, 1000, 2000, and so forth, along
 * with ratios of running times between successive array sizes.
 *
 * @param args the command-line arguments
 */
int main() {
    int pre = DoublingTest::timeTrial(125);
    for (int n = 250; n <= 4000; n += n) {
        int time = DoublingTest::timeTrial(n);
        cout << "ratio: " << time / pre << " ratio" << endl;
        pre = time;
    }
}