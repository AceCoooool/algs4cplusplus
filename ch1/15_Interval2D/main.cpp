#include <iostream>
#include <vector>
#include <algorithm>
#include "../head/Interval2D.h"

using namespace std;

/**
 * Unit tests the {@code Interval2D} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    Interval1D v1(1, 3), v2(1, 3);
    Interval2D d1(v1, v2);

    Interval1D v3(2, 4), v4(2, 4);
    Interval2D d2(v3, v4);

    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;

    // test intersects
    cout << "intersects(v1, v2)? : " << d1.intersects(d2) << endl;
    // test contains
    Point2D p(2, 4);
    cout << "d1 contains p? : " << d1.contains(p) << endl;
    // test area
    cout << "area of d1: " << d1.area() << endl;
    // test ==
    cout << "d1 equal d2? ：" << (d1 == d2) << endl;
}