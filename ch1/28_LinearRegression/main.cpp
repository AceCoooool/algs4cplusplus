#include <iostream>
#include "../head/LinearRegression.h"

using namespace std;


int main() {
    vector<double> a{1.0, 2.0, 3.0, 4.1}, b{1.01, 2.01, 2.99, 4.0};
    LinearRegression lr(a, b);
    cout << lr << endl;
}