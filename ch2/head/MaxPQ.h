#ifndef CH2_MAXPQ_H
#define CH2_MAXPQ_H

#include <vector>
#include <stdexcept>
#include <memory>

using std::vector;
using std::swap;
using std::runtime_error;
using std::unique_ptr;

/**
 *  The {@code MaxPQ} class represents a priority queue of generic keys.
 *  It supports the usual <em>insert</em> and <em>delete-the-maximum</em>
 *  operations, along with methods for peeking at the maximum key,
 *  testing if the priority queue is empty, and iterating through
 *  the keys.
 *  <p>
 *  This implementation uses a binary heap.
 *  The <em>insert</em> and <em>delete-the-maximum</em> operations take
 *  logarithmic amortized time.
 *  The <em>max</em>, <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes time proportional to the specified capacity or the number of
 *  items used to initialize the data structure.
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
class MaxPQ {
public:
    /**
     * Initializes an empty priority queue with the given initial capacity.
     *
     * @param  initCapacity the initial capacity of this priority queue
     */
    MaxPQ(int initCapacity) : n(0) {
        pq.resize(initCapacity + 1);
        comp = [](T &a, T &b) { return a < b; };
    }

    /**
     * Initializes an empty priority queue.
     */
    MaxPQ() : MaxPQ(1) {}

    /**
     * Initializes an empty priority queue with the given initial capacity,
     * using the given comparator.
     *
     * @param  initCapacity the initial capacity of this priority queue
     * @param  comparator the order in which to compare the keys
     */
    MaxPQ(int initCapacity, bool (*cmp)(T &, T &)) {
        comp = cmp;
        pq.resize(initCapacity + 1);
        n = 0;
    }

    /**
     * Initializes an empty priority queue using the given comparator.
     *
     * @param  comparator the order in which to compare the keys
     */
    MaxPQ(bool (*cmp)(T &, T &)) : MaxPQ(1, cmp) {}

    /**
     * Initializes a priority queue from the array of keys.
     * Takes time proportional to the number of keys, using sink-based heap construction.
     *
     * @param  keys the array of keys
     */
    MaxPQ(vector<T> &keys) {
        n = keys.size();
        pq.resize(keys.size() + 1);
        comp = [](T a, T b) { return a < b; };
        for (int i = 0; i < n; i++)
            pq[i + 1] = keys[i];
        for (int k = n / 2; k >= 1; k--)
            sink(k);
    }

    MaxPQ(vector<T> &keys, bool(*cmp)(T &, T &)) {
        n = keys.size();
        pq.resize(keys.size() + 1);
        comp = cmp;
        for (int i = 0; i < n; i++)
            pq[i + 1] = keys[i];
        for (int k = n / 2; k >= 1; k--)
            sink(k);
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
     * Returns the number of keys on this priority queue.
     *
     * @return the number of keys on this priority queue
     */
    int size() {
        return n;
    }

    /**
     * Returns a largest key on this priority queue.
     *
     * @return a largest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    T max() {
        if (isEmpty()) throw runtime_error("Priority queue underflow");
        return pq[1];
    }

    /**
     * Adds a new key to this priority queue.
     *
     * @param  x the new key to add to this priority queue
     */
    void insert(T x) {
        // double size of array if necessary
        if (n == pq.size() - 1) resize(2 * pq.size());

        // add x, and percolate it up to maintain heap invariant
        pq[++n] = x;
        swim(n);
    }

    /**
     * Removes and returns a largest key on this priority queue.
     *
     * @return a largest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    T delMax() {
        if (isEmpty()) throw runtime_error("Priority queue underflow");
        T max = pq[1];
        swap(pq[1], pq[n--]);
        sink(1);
        if ((n > 0) && (n == (pq.size() - 1) / 4)) resize(pq.size() / 2);
        return max;
    }

private:
    // helper function to double the size of the heap array
    void resize(int capacity) {
        pq.resize(capacity);
    }

    /***************************************************************************
    * Helper functions to restore the heap invariant.
    ***************************************************************************/
    void swim(int k) {
        while (k > 1 && comp(pq[k / 2], pq[k])) {
            swap(pq[k], pq[k / 2]);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && comp(pq[j], pq[j + 1])) j++;
            if (!comp(pq[k], pq[j])) break;
            swap(pq[k], pq[j]);
            k = j;
        }
    }

    /***************************************************************************
    * Iterator.
    ***************************************************************************/
private:
    class Iterator {
        unique_ptr<MaxPQ<T>> p;
        int cnt;
    public:
        // initial iterator
        Iterator(vector<T> data, bool(*cmp)(T &, T &), int n_) : cnt(n_) {
            p.reset(new MaxPQ(data, cmp));
        }

        // get current value
        T operator*() { return p->max(); }

        // next iterator
        Iterator &operator++() {
            p->delMax();
            --cnt;
            return *this;
        }

        // judge is same?
        bool operator!=(const Iterator &it) const { return cnt != it.cnt; }
    };

public:
    /**
     * Returns an iterator that iterates over the keys on this priority queue
     * in descending order.
     * The iterator doesn't implement {@code remove()} since it's optional.
     *
     * @return an iterator that iterates over the keys in descending order
     */
    Iterator begin() { return {{pq.begin() + 1, pq.begin() + 1 + n}, comp, n}; }

    Iterator end() { return {{}, comp, 0}; }

private:
    vector<T> pq;       // store items at indices 1 to n
    int n;              // number of items on priority queue

    bool (*comp)(T &, T &);  // optional comparator
};

#endif //CH2_MAXPQ_H
