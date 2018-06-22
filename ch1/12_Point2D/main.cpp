#include <iostream>
#include <vector>
#include <algorithm>
#include "../head/Point2D.h"

using namespace std;


int main() {
    vector<Point2D> vec;
    vec.push_back(Point2D(1, 2));
    vec.push_back(Point2D(2.0, 3.0));
    vec.push_back(Point2D(1.1, 2.0));
    cout << "Unsorted: " << endl;
    for (auto a: vec)
        cout << a << endl;
    cout << "sorted with x: " << endl;
    sort(vec.begin(), vec.end(), Point2D::XOrder);
    for (auto a: vec)
        cout << a << endl;
}