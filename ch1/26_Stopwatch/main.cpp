#include <iostream>
#include <cmath>
#include "../head/Stopwatch.h"

using namespace std;

/**
 * Unit tests the {@code Bag} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    int n = 10000;
    // sum of square roots of integers from 1 to n using Math.sqrt(x).
    Stopwatch timer1;
    double sum1 = 0.0;
    for (int i = 1; i <= n; ++i)
        sum1 += sqrt(i);
    int time1 = timer1.elapsedTime();
    cout << sum1 << " costs " << time1 << " microseconds" << endl;

    // sum of square roots of integers from 1 to n using Math.pow(x, 0.5).
    Stopwatch timer2;
    double sum2 = 0.0;
    for (int i = 1; i <= n; i++) {
        sum2 += pow(i, 0.5);
    }
    int time2 = timer2.elapsedTime();
    cout << sum2 << " costs " << time2 << " microseconds" << endl;

}