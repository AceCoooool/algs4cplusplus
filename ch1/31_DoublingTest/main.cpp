#include <istream>
#include <fstream>
#include "../head/DoublingTest.h"

using namespace std;

/**
 * Prints table of running times to call {@code ThreeSum.count()}
 * for arrays of size 250, 500, 1000, 2000, and so forth.
 *
 * @param args the command-line arguments
 */
int main() {
    for (int n = 250; n <= 4000; n += n) {
        int time = DoublingTest::timeTrial(n);
        cout << "time: " << time << " microseconds" << endl;
    }
}