#include <iostream>
#include <fstream>
#include <stack>
#include "../head/MinPQ.h"
#include "../head/Transaction.h"

using namespace std;

/**
 *  The {@code TopM} class provides a client that reads a sequence of
 *  transactions from standard input and prints the <em>m</em> largest ones
 *  to standard output. This implementation uses a {@link MinPQ} of size
 *  at most <em>m</em> + 1 to identify the <em>M</em> largest transactions
 *  and a {@link Stack} to output them in the proper order.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
int main() {
    int m = 5;
    auto f = [](Transaction &a1, Transaction &a2) { return a1.getamount() > a2.getamount(); };
    MinPQ<Transaction> pq(f);
    fstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tinyBatch.txt");
    string tmp;
    while (getline(file, tmp)) {
        // Create an entry from the next line and put on the PQ.
        Transaction *trans = new Transaction(tmp);
        pq.insert(*trans);
        if (pq.size() > m)
            pq.delMin();
    }
    stack<Transaction> st;
    for (Transaction trans: pq)
        st.push(trans);
    while (!st.empty()) {
        cout << st.top() << endl;
        st.pop();
    }
}