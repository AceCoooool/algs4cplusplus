#ifndef CH1_RESIZINGARRAYBAG_H
#define CH1_RESIZINGARRAYBAG_H

#include <vector>
#include <memory>
#include <stdexcept>

using std::vector;
using std::unique_ptr;
using std::runtime_error;

/**
 *  The {@code ResizingArrayBag} class represents a bag (or multiset) of
 *  generic items. It supports insertion and iterating over the
 *  items in arbitrary order.
 *  <p>
 *  This implementation uses a resizing array.
 *  See {@link LinkedBag} for a version that uses a singly linked list.
 *  The <em>add</em> operation takes constant amortized time; the
 *  <em>isEmpty</em>, and <em>size</em> operations
 *  take constant time. Iteration takes time proportional to the number of items.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename T>
class ResizingArrayBag {
public:
    /**
     * Initializes an empty bag.
     */
    ResizingArrayBag() : n(0), a(new vector<T>(2)), length(2) {}

    /**
     * Is this bag empty?
     * @return true if this bag is empty; false otherwise
     */
    bool isEmpty() {
        return n == 0;
    }

    /**
     * Returns the number of items in this bag.
     * @return the number of items in this bag
     */
    int size() {
        return n;
    }

    /**
     * Adds the item to this bag.
     * @param item the item to add to this bag
     */
    void add(T item) {
        if (n == length) resize(2 * length);    // double size of array if necessary
        (*a.get())[n++] = item;                 // add item
    }

private:
    // an iterator
    class Iterator {
        vector<T> data;
        int pos;
        int n;
    public:
        // initial iterator
        Iterator(vector<T> &data_, int pos_, int n_) : data(data_), pos(pos_), n(n_) {}

        // get current value
        T &operator*() { return data[pos]; }

        // next iterator
        Iterator &operator++() {
            if (++pos == n)pos = 0;
            return *this;
        }

        // judge is same?
        bool operator!=(const Iterator &it) const { return pos != it.pos; }
    };

    // a const iterator
    class ConstIterator {
        vector<T> data;
        int pos;
        int n;
    public:
        // initial iterator
        ConstIterator(vector<T> &data_, int pos_, int n_) : data(data_), pos(pos_), n(n_) {}

        // get current value
        const T &operator*() { return data[pos]; }

        // next iterator
        ConstIterator &operator++() {
            if (++pos == n)pos = 0;
            return *this;
        }

        // judge is same?
        bool operator!=(const ConstIterator &it) const { return pos != it.pos; }
    };

public:
    /**
     * Returns an iterator that iterates over the items in the bag in arbitrary order.
     * @return an iterator that iterates over the items in the bag in arbitrary order
     */

    Iterator begin() { return {*a.get(), 0, n + 1}; }

    Iterator end() { return {*a.get(), n, n + 1}; }

    ConstIterator begin() const { return {*a.get(), 0, n + 1}; }

    ConstIterator end() const { return {*a.get(), n, n + 1}; }

private:
    // resize the underlying array holding the elements
    void resize(const int capacity) {
        if (capacity < n) throw runtime_error("illegal capacity");

        // textbook implementation
        auto temp = new vector<T>(capacity);
        for (int i = 0; i < n; i++) {
            (*temp)[i] = (*a.get())[i];
        }
        a.reset(temp);
        length = capacity;
    }

private:
    unique_ptr<vector<T>> a;  // array of items
    int length;               // capacity of array
    int n;                    // number of elements on stack
};

#endif //CH1_RESIZINGARRAYBAG_H
