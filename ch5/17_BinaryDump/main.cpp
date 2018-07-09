#include <iostream>
#include <fstream>

using namespace std;

/**
 * Reads in a sequence of bytes from standard input and writes
 * them to standard output in binary, k bits per line,
 * where k is given as a command-line integer (defaults
 * to 16 if no integer is specified); also writes the number
 * of bits.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/abra.txt", ios::binary);
    int bitsPerLine = 16;
    char tmp;
    int cnt = 0;
    while (file >> tmp) {
        for (int i = 7; i >= 0; --i) {
            cout << ((tmp >> i) & 1);
            cnt++;
            if (cnt % bitsPerLine == 0 && cnt != 0)cout << endl;
        }
    }
    if (bitsPerLine != 0) cout << endl;
    cout << cnt << " bits" << endl;
}