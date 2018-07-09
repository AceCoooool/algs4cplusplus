#include <iostream>
#include <fstream>
#include "../head/Quick.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input; quicksorts them; 
 * and prints them to standard output in ascending order. 
 * Shuffles the array and then prints the strings again to
 * standard output, but this time, using the select method.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    Quick::sort(vec);
    for (auto a: vec)
        cout << a << " ";
    cout << endl;
    // shuffle
    shuffle(vec.begin(), vec.end(), g);
    cout << "select kth large in array: " << endl;
    for (auto a: vec)
        cout << a << " ";
    cout << endl;
    for (int i = 0; i < vec.size(); ++i) {
        auto str = Quick::select(vec, i);
        cout << i << " th: " << str << endl;
    }
}