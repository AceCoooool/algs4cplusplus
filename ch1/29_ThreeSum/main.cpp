#include <istream>
#include <fstream>
#include "../head/ThreeSum.h"
#include "../head/Stopwatch.h"

using namespace std;

/**
 * Reads in a sequence of integers from a file, specified as a command-line argument;
 * counts the number of triples sum to exactly zero; prints out the time to perform
 * the computation.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/2Kints.txt");
    vector<int> vec;
    int tmp;
    while (file >> tmp)
        vec.push_back(tmp);

    Stopwatch timer1;
    int count = ThreeSum::count(vec);
    cout << "elapsed time = " << timer1.elapsedTime() << " microseconds" << endl;
    cout << "number of count: " << count << endl;
}