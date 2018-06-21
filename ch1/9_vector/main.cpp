#include <iostream>
#include "../head/Vector.h"

using namespace std;


int main() {
    vector<double> xdata{1.0, 2.0, 3.0, 4.0};
    vector<double> ydata{5.0, 2.0, 4.0, 1.0};
    Vector x(xdata), y(ydata);
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    Vector z = x.plus(y);
    cout << "z = " << z << endl;

    z = z.scale(10.0);
    cout << "10z = " << z << endl;

    cout << "|x| = " << x.magnitude() << endl;
    cout << "<x, y> = " << x.dot(y) << endl;
    cout << "dist(x,y) = " << x.distanceTo(y) << endl;
    cout << "dir(x) = " << x.direction() << endl;
}