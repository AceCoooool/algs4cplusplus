#include <iostream>
#include <vector>
#include "../head/RectHV.h"

using namespace std;

/**
 * simple test
 * @return
 */
int main() {
    RectHV v1(1, 1, 4, 4);
    RectHV v2(2, 2, 3, 3);
    cout << v1 << endl;
    cout << v2 << endl;
    // test intersects
    cout << "intersect(v1, v2): " << v1.intersects(v2) << endl;
    // test contains
    Point2D p(2, 3);
    cout << "v1 contain p?: " << v1.contains(p) << endl;
    // test ==
    cout << "v1 == v2?: " << (v1 == v2) << endl;
}