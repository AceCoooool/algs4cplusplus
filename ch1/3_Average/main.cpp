#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const int seed = 100;

/**
* Reads in a sequence of real numbers from standard input and prints
* out their average to standard output.
*
* @param args the command-line arguments
*/
int main() {
    int count = 0;
    double sum = 0.0;
    vector<double> arr{10.0, 5.0, 6.0, 3.0, 7.0, 32.0};
    for (auto a: arr) {
        sum += a;
        count++;
    }
    double avg = sum / count;
    cout << "Average is " << avg << endl;
}