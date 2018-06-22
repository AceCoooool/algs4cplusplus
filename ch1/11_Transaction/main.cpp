#include <iostream>
#include <algorithm>
#include "../head/Transaction.h"

using namespace std;


int main() {
    vector<Transaction> a;
    a.push_back(Transaction("Turing 6/17/1990 644.08"));
    a.push_back(Transaction("Tarjan 3/26/2002 4121.85"));
    a.push_back(Transaction("Dijkstra 8/22/2007 2678.40"));

    cout << "Unsorted" << endl;
    for (int i = 0; i < a.size(); ++i)
        cout << a[i] << endl;

    cout << "Sorted by date" << endl;
    sort(a.begin(), a.end(), Transaction::WhenOrder);
    for (int i = 0; i < a.size(); ++i)
        cout << a[i] << endl;

    cout << "Sorted by customer" << endl;
    sort(a.begin(), a.end(), Transaction::WhoOrder);
    for (int i = 0; i < a.size(); ++i)
        cout << a[i] << endl;

    cout << "Sorted by amount" << endl;
    sort(a.begin(), a.end(), Transaction::HowMuchOrder);
    for (int i = 0; i < a.size(); ++i)
        cout << a[i] << endl;
}