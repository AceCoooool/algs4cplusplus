#include <iostream>
#include "../head/SparseVector.h"

// TODO: add a fstream to filename map
using namespace std;

/**
 * Unit tests the {@code SparseVector} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    SparseVector a(10);
    SparseVector b(10);
    a.put(3, 0.50);
    a.put(9, 0.75);
    a.put(6, 0.11);
    a.put(6, 0.00);
    b.put(3, 0.60);
    b.put(4, 0.90);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a dot b = " << a.dot(b) << endl;
    SparseVector c = a.plus(b);
    cout << "a + b = " << c << endl;
}