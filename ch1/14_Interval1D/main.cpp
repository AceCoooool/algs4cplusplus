#include <iostream>
#include <vector>
#include <algorithm>
#include "../head/Interval1D.h"

using namespace std;

/**
 * Unit tests the {@code Interval1D} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    vector<Interval1D> intervals;
    intervals.push_back(Interval1D(15.0, 33.0));
    intervals.push_back(Interval1D(45.0, 66.0));
    intervals.push_back(Interval1D(20.0, 70.0));
    intervals.push_back(Interval1D(46.0, 55.0));

    cout << "Unsorted" << endl;
    for (auto inter: intervals)
        cout << inter << endl;

    cout << "Sort by min endpoint" << endl;
    sort(intervals.begin(), intervals.end(), Interval1D::MinEndpointComparator);
    for (auto inter: intervals)
        cout << inter << endl;

    cout << "Sort by max endpoint" << endl;
    sort(intervals.begin(), intervals.end(), Interval1D::MaxEndpointComparator);
    for (auto inter: intervals)
        cout << inter << endl;

    cout << "Sort by length" << endl;
    sort(intervals.begin(), intervals.end(), Interval1D::LengthComparator);
    for (auto inter: intervals)
        cout << inter << endl;
}