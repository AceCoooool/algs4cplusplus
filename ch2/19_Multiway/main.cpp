#include <iostream>
#include <random>
#include <fstream>
#include "../head/Multiway.h"

using namespace std;

/**
 *  Reads sorted text files specified as command-line arguments;
 *  merges them together into a sorted output; and writes
 *  the results to standard output.
 *  Note: this client does not check that the input files are sorted.
 *
 * @param args the command-line arguments
 */
int main() {
    vector<string> files{"./data/m1.txt",
                         "./data/m2.txt",
                         "./data/m3.txt"};
    vector<fstream> streams;
    for (auto f: files)
        streams.push_back(fstream(f));
    Multiway::merge(streams);
}