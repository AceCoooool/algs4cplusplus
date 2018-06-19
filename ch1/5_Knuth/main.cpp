#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

std::random_device rd;
std::mt19937 gen(rd());

/**
* Rearranges an array of objects in uniformly random order
* (under the assumption that {@code Math.random()} generates independent
* and uniformly distributed numbers between 0 and 1).
* @param a the array to be shuffled
*/
template<typename T>
void shuffle_(vector<T> &a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        // choose index uniformly in [0, i]
        uniform_int_distribution<> dis(0, i);
        int r = dis(gen);
        swap(a[r], a[i]);
    }
}

template<typename T>
void shuffleAlternate_(vector<T> &a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        // choose index uniformly in [i, n-1]
        uniform_int_distribution<> dis(0, n - i);
        int r = i + dis(gen);
        swap(a[r], a[i]);
    }
}

/**
* Reads in a sequence of text files specified as the first command-line
* arguments, concatenates them, and writes the results to the file
* specified as the last command-line argument.
*
* @param args the command-line arguments
*/
int main() {
    // TODO: change to relative path
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/cards.txt");
    string tmp;
    vector<string> a;
    while (file >> tmp) {
        a.push_back(tmp);
    }
    shuffle_(a);
    for (int i = 0; i < a.size(); ++i) {
        cout << setw(6)<<left<<a[i];
        if ((i + 1) % 13 == 0)
            cout << endl;
    }
}