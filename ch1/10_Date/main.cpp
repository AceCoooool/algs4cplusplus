#include <iostream>
#include "../head/Date.h"

using namespace std;


int main() {
    Date today(2, 25, 2004);
    cout << today << endl;
    for (int i = 0; i < 10; ++i) {
        today = today.next();
        cout << today << endl;
    }
    cout << today.isAfter(today.next()) << endl;
    cout << today.isAfter(today) << endl;
    cout << today.next().isAfter(today) << endl;

    Date birthday(10, 16, 1971);
    cout << birthday << endl;
    for (int i = 0; i < 10; ++i) {
        birthday = birthday.next();
        cout << birthday << endl;
    }
    cout << (today == birthday) << endl;
}