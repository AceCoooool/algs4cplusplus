#ifndef CH2_INDEXMAXPQ_H
#define CH2_INDEXMAXPQ_H

#include <vector>
#include <stdexcept>
#include <memory>

using std::vector;
using std::runtime_error;
using std::unique_ptr;
using std::make_unique;

/**
 *  The {@code IndexMaxPQ} class represents an indexed priority queue of generic keys.
 *  It supports the usual <em>insert</em> and <em>delete-the-maximum</em>
 *  operations, along with <em>delete</em> and <em>change-the-key</em>
 *  methods. In order to let the client refer to items on the priority queue,
 *  an integer between {@code 0} and {@code maxN - 1}
 *  is associated with each key—the client
 *  uses this integer to specify which key to delete or change.
 *  It also supports methods for peeking at a maximum key,
 *  testing if the priority queue is empty, and iterating through
 *  the keys.
 *  <p>
 *  This implementation uses a binary heap along with an array to associate
 *  keys with integers in the given range.
 *  The <em>insert</em>, <em>delete-the-maximum</em>, <em>delete</em>,
 *  <em>change-key</em>, <em>decrease-key</em>, and <em>increase-key</em>
 *  operations take logarithmic time.
 *  The <em>is-empty</em>, <em>size</em>, <em>max-index</em>, <em>max-key</em>,
 *  and <em>key-of</em> operations take constant time.
 *  Construction takes time proportional to the specified capacity.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Key> the generic type of key on this priority queue
 */
template<typename T>
class IndexMaxPQ{
public:
    /**
     * Initializes an empty indexed priority queue with indices between {@code 0}
     * and {@code maxN - 1}.
     *
     * @param  maxN the keys on this priority queue are index from {@code 0} to {@code maxN - 1}
     * @throws IllegalArgumentException if {@code maxN < 0}
     */
    IndexMaxPQ(int maxN_) {
        if (maxN_ < 0) throw runtime_error("illegal size");
        maxN = maxN_;
        n = 0;
        keys.resize(maxN + 1);    // make this of length maxN??
        pq.resize(maxN + 1);
        qp.resize(maxN + 1);      // make this of length maxN??
        for (int i = 0; i <= maxN; i++)
            qp[i] = -1;
    }

    /**
     * Returns true if this priority queue is empty.
     *
     * @return {@code true} if this priority queue is empty;
     *         {@code false} otherwise
     */
    bool isEmpty() {
        return n == 0;
    }

    /**
     * Is {@code i} an index on this priority queue?
     *
     * @param  i an index
     * @return {@code true} if {@code i} is an index on this priority queue;
     *         {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= i < maxN}
     */
    bool contains(int i) {
        if (i < 0 || i >= maxN) throw runtime_error("index out of range");
        return qp[i] != -1;
    }

    /**
     * Returns the number of keys on this priority queue.
     *
     * @return the number of keys on this priority queue
     */
    int size() {
        return n;
    }

    /**
     * Associate key with index i.
     *
     * @param  i an index
     * @param  key the key to associate with index {@code i}
     * @throws IllegalArgumentException unless {@code 0 <= i < maxN}
     * @throws IllegalArgumentException if there already is an item
     *         associated with index {@code i}
     */
    void insert(int i, T key) {
        if (i < 0 || i >= maxN) throw runtime_error("index out of range");
        if (contains(i)) throw runtime_error("index is already in the priority queue");
        n++;
        qp[i] = n;
        pq[n] = i;
        keys[i] = key;
        swim(n);
    }

    /**
     * Returns an index associated with a maximum key.
     *
     * @return an index associated with a maximum key
     * @throws NoSuchElementException if this priority queue is empty
     */
    int maxIndex() {
        if (n == 0) throw runtime_error("Priority queue underflow");
        return pq[1];
    }

    /**
     * Returns a maximum key.
     *
     * @return a maximum key
     * @throws NoSuchElementException if this priority queue is empty
     */
    T maxKey() {
        if (n == 0) throw runtime_error("Priority queue underflow");
        return keys[pq[1]];
    }

    /**
     * Removes a maximum key and returns its associated index.
     *
     * @return an index associated with a maximum key
     * @throws NoSuchElementException if this priority queue is empty
     */
    int delMax() {
        if (n == 0) throw runtime_error("Priority queue underflow");
        int max = pq[1];
        exch(1, n--);
        sink(1);
        qp[max] = -1;        // delete
        pq[n + 1] = -1;      // not needed
        return max;
    }

    /**
     * Returns the key associated with index {@code i}.
     *
     * @param  i the index of the key to return
     * @return the key associated with index {@code i}
     * @throws IllegalArgumentException unless {@code 0 <= i < maxN}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    T keyOf(int i) {
        if (i < 0 || i >= maxN) throw runtime_error("illegal index");
        if (!contains(i)) throw runtime_error("index is not in the priority queue");
        else return keys[i];
    }

    /**
     * Change the key associated with index {@code i} to the specified value.
     *
     * @param  i the index of the key to change
     * @param  key change the key associated with index {@code i} to this key
     * @throws IllegalArgumentException unless {@code 0 <= i < maxN}
     */
    void changeKey(int i, T key) {
        if (i < 0 || i >= maxN) throw runtime_error("index out of range");
        if (!contains(i)) throw runtime_error("index is not in the priority queue");
        keys[i] = key;
        swim(qp[i]);
        sink(qp[i]);
    }

    /**
     * Decrease the key associated with index {@code i} to the specified value.
     *
     * @param  i the index of the key to decrease
     * @param  key decrease the key associated with index {@code i} to this key
     * @throws IllegalArgumentException unless {@code 0 <= i < maxN}
     * @throws IllegalArgumentException if {@code key >= keyOf(i)}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    void decreaseKey(int i, T key) {
        if (i < 0 || i >= maxN) throw runtime_error("index out of range");
        if (!contains(i)) throw runtime_error("index is not in the priority queue");
        if (keys[i] <= key)
            throw runtime_error("Calling decreaseKey() with given argument would not strictly decrease the key");
        keys[i] = key;
        sink(qp[i]);
    }

    /**
     * Increase the key associated with index {@code i} to the specified value.
     *
     * @param  i the index of the key to increase
     * @param  key increase the key associated with index {@code i} to this key
     * @throws IllegalArgumentException unless {@code 0 <= i < maxN}
     * @throws IllegalArgumentException if {@code key <= keyOf(i)}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    void increaseKey(int i, T key) {
        if (i < 0 || i >= maxN) throw runtime_error("index out of range");
        if (!contains(i)) throw runtime_error("index is not in the priority queue");
        if (keys[i] >= key)
            throw runtime_error("Calling increaseKey() with given argument would not strictly increase the key");
        keys[i] = key;
        swim(qp[i]);
    }

    /**
     * Remove the key on the priority queue associated with index {@code i}.
     *
     * @param  i the index of the key to remove
     * @throws IllegalArgumentException unless {@code 0 <= i < maxN}
     * @throws NoSuchElementException no key is associated with index {@code i}
     */
    void delete_op(int i) {
        if (i < 0 || i >= maxN) throw runtime_error("illegal index");
        if (!contains(i)) throw runtime_error("index is not in the priority queue");
        int index = qp[i];
        exch(index, n--);
        swim(index);
        sink(index);
        qp[i] = -1;
    }
    /***************************************************************************
    * Iterators.
    ***************************************************************************/
private:
    class Iterator {
        unique_ptr<IndexMaxPQ<T>> tmp;
        int cnt;
    public:
        Iterator(vector<int> &pq_t, vector<T> &key_t, int n_t) : cnt(n_t) {
            tmp = make_unique<IndexMaxPQ>(pq_t.size() - 1);
            for (int i = 1; i <= n_t; ++i) {
                tmp->insert(pq_t[i], key_t[pq_t[i]]);
            }
        }

        // get current value
        int operator*() { return tmp->maxIndex(); }

        // next iterator
        Iterator &operator++() {
            tmp->delMax();
            --cnt;
            return *this;
        }

        // judge is same?
        bool operator!=(const Iterator &it) const { return cnt != it.cnt; }
    };

public:
    /**
     * Returns an iterator that iterates over the keys on the
     * priority queue in ascending order.
     * The iterator doesn't implement {@code remove()} since it's optional.
     *
     * @return an iterator that iterates over the keys in ascending order
     */
    Iterator begin() { return {pq, keys, n}; }

    Iterator end() { return {pq, keys, 0}; }

private:
    /***************************************************************************
    * General helper functions.
    ***************************************************************************/
    void exch(int i, int j) {
        int swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

    bool less(int i, int j) {
        return keys[pq[i]] < keys[pq[j]];
    }

    /***************************************************************************
    * Heap helper functions.
    ***************************************************************************/
    void swim(int k) {
        while (k > 1 && less(k / 2, k)) {
            exch(k, k / 2);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && less(j, j + 1)) j++;
            if (!less(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

    // pq---索引对应的位置, qp---各位置对应的索引, keys---各位置的值
private:
    int maxN;              // maximum number of elements on PQ
    int n;                 // number of elements on PQ
    vector<int> pq;        // binary heap using 1-based indexing
    vector<int> qp;        // inverse of pq - qp[pq[i]] = pq[qp[i]] = i
    vector<T> keys;        // keys[i] = priority of i
};

#endif //CH2_INDEXMAXPQ_H
