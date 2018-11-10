#include <iostream>
#include "../head/StaticSetofInts.h"

using namespace std;

/**
 * simple test
 *
 */
int main() {
    const StaticSETofInts *s = new StaticSETofInts({4, 2, 3, 6, 5});
    cout << s->contains(5) << endl;
}