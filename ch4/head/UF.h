#ifndef CH1_UF_H
#define CH1_UF_H

#include <vector>
#include <stdexcept>

using std::vector;
using std::runtime_error;
using std::to_string;

/**
 *  The {@code UF} class represents a <em>union–find data type</em>
 *  (also known as the <em>disjoint-sets data type</em>).
 *  It supports the <em>union</em> and <em>find</em> operations,
 *  along with a <em>connected</em> operation for determining whether
 *  two sites are in the same component and a <em>count</em> operation that
 *  returns the total number of components.
 *  <p>
 *  The union–find data type models connectivity among a set of <em>n</em>
 *  sites, named 0 through <em>n</em>–1.
 *  The <em>is-connected-to</em> relation must be an
 *  <em>equivalence relation</em>:
 *  <ul>
 *  <li> <em>Reflexive</em>: <em>p</em> is connected to <em>p</em>.
 *  <li> <em>Symmetric</em>: If <em>p</em> is connected to <em>q</em>,
 *       then <em>q</em> is connected to <em>p</em>.
 *  <li> <em>Transitive</em>: If <em>p</em> is connected to <em>q</em>
 *       and <em>q</em> is connected to <em>r</em>, then
 *       <em>p</em> is connected to <em>r</em>.
 *  </ul>
 *  <p>
 *  An equivalence relation partitions the sites into
 *  <em>equivalence classes</em> (or <em>components</em>). In this case,
 *  two sites are in the same component if and only if they are connected.
 *  Both sites and components are identified with integers between 0 and
 *  <em>n</em>–1.
 *  Initially, there are <em>n</em> components, with each site in its
 *  own component.  The <em>component identifier</em> of a component
 *  (also known as the <em>root</em>, <em>canonical element</em>, <em>leader</em>,
 *  or <em>set representative</em>) is one of the sites in the component:
 *  two sites have the same component identifier if and only if they are
 *  in the same component.
 *  <ul>
 *  <li><em>union</em>(<em>p</em>, <em>q</em>) adds a
 *      connection between the two sites <em>p</em> and <em>q</em>.
 *      If <em>p</em> and <em>q</em> are in different components,
 *      then it replaces
 *      these two components with a new component that is the union of
 *      the two.
 *  <li><em>find</em>(<em>p</em>) returns the component
 *      identifier of the component containing <em>p</em>.
 *  <li><em>connected</em>(<em>p</em>, <em>q</em>)
 *      returns true if both <em>p</em> and <em>q</em>
 *      are in the same component, and false otherwise.
 *  <li><em>count</em>() returns the number of components.
 *  </ul>
 *  <p>
 *  The component identifier of a component can change
 *  only when the component itself changes during a call to
 *  <em>union</em>—it cannot change during a call
 *  to <em>find</em>, <em>connected</em>, or <em>count</em>.
 *  <p>
 *  This implementation uses weighted quick union by rank with path compression
 *  by halving.
 *  Initializing a data structure with <em>n</em> sites takes linear time.
 *  Afterwards, the <em>union</em>, <em>find</em>, and <em>connected</em>
 *  operations take logarithmic time (in the worst case) and the
 *  <em>count</em> operation takes constant time.
 *  Moreover, the amortized time per <em>union</em>, <em>find</em>,
 *  and <em>connected</em> operation has inverse Ackermann complexity.
 *  For alternate implementations of the same API, see
 *  {@link QuickUnionUF}, {@link QuickFindUF}, and {@link WeightedQuickUnionUF}.
 *
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/15uf">Section 1.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

class UF {
public:
    /**
     * Initializes an empty union–find data structure with {@code n} sites
     * {@code 0} through {@code n-1}. Each site is initially in its own
     * component.
     *
     * @param  n the number of sites
     * @throws IllegalArgumentException if {@code n < 0}
     */
    UF(int n) : count(n) {
        count = n;
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    /**
     * Returns the component identifier for the component containing site {@code p}.
     *
     * @param  p the integer representing one site
     * @return the component identifier for the component containing site {@code p}
     * @throws IllegalArgumentException unless {@code 0 <= p < n}
     */
    int find(int p) {
        validate(p);
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];    // path compression by halving
            p = parent[p];
        }
        return p;
    }

    /**
     * Returns the number of components.
     *
     * @return the number of components (between {@code 1} and {@code n})
     */
    int getcount() {
        return count;
    }

    /**
     * Returns true if the the two sites are in the same component.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     * @return {@code true} if the two sites {@code p} and {@code q} are in the same component;
     *         {@code false} otherwise
     * @throws IllegalArgumentException unless
     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
     */
    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    /**
     * Merges the component containing site {@code p} with the
     * the component containing site {@code q}.
     *
     * @param  p the integer representing one site
     * @param  q the integer representing the other site
     * @throws IllegalArgumentException unless
     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
     */
    void union_op(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        // make root of smaller rank point to root of larger rank
        if (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
        else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
        else {
            parent[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }

private:
    // validate that p is a valid index
    void validate(int p) {
        int n = parent.size();
        if (p < 0 || p >= n) {
            throw runtime_error("index " + to_string(p) + " is not between 0 and " + to_string(n - 1));
        }
    }

private:
    vector<int> parent;  // parent[i] = parent of i
    vector<char> rank;   // rank[i] = rank of subtree rooted at i (never more than 31)
    int count;           // number of components
};

#endif //CH1_UF_H
