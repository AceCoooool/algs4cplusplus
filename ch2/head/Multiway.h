#ifndef CH2_MULTIWAY_H
#define CH2_MULTIWAY_H

#include <fstream>
#include <iostream>
#include "../head/IndexMinPQ.h"

using std::fstream;
using std::string;
using std::cout;
using std::endl;

/**
 *  The {@code Multiway} class provides a client for reading in several
 *  sorted text files and merging them together into a single sorted
 *  text stream.
 *  This implementation uses a {@link IndexMinPQ} to perform the multiway
 *  merge.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Multiway {
public:
    // This class should not be instantiated.
    Multiway() = delete;

    // merge together the sorted input streams and write the sorted result to standard output
    static void merge(vector<fstream> &vec) {
        int N = vec.size();
        IndexMinPQ<string> pq(N);
        string tmp;
        for (int i = 0; i < vec.size(); ++i) {
            if (vec[i] >> tmp)
                pq.insert(i, tmp);
        }
        while (!pq.isEmpty()) {
            cout << pq.minKey() << " ";
            int i = pq.delMin();
            if (vec[i] >> tmp)
                pq.insert(i, tmp);
        }
    }
};

#endif //CH2_MULTIWAY_H
