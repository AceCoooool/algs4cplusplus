#ifndef CH1_RESIZINGARRAYBAG_H
#define CH1_RESIZINGARRAYBAG_H

// TODO: use only start and finish
#include <stdexcept>

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
private:
    T *a;                     // array of items
    int length;               // capacity of array
    int n;                    // number of elements on stack

    // for iterator
    T *start;
    T *finish;

public:
    /**
     * Initializes an empty bag.
     */
    ResizingArrayBag() : n(0), a(new T[2]), length(2), start(a), finish(a) {}

    ~ResizingArrayBag() {
        delete[](a);
        start->~T();
        finish->~T();
    }

    /**
     * Is this bag empty?
     * @return true if this bag is empty; false otherwise
     */
    bool isEmpty() const {
        return n == 0;
    }

    /**
     * Returns the number of items in this bag.
     * @return the number of items in this bag
     */
    int size() const {
        return n;
    }

    /**
     * Adds the item to this bag.
     * @param item the item to add to this bag
     */
    void add(T item) {
        if (n == length) resize(2 * length);    // double size of array if necessary
        a[n++] = item;                          // add item
        finish += 1;
    }

    // iterator
    T *begin() noexcept { return start; }
    T *end() noexcept { return finish; }
    const T *begin() const noexcept { return start; }
    const T *end() const noexcept { return finish; }


private:
    // resize the underlying array holding the elements
    void resize(const int capacity) {
        if (capacity < n) throw runtime_error("illegal capacity");

        // textbook implementation
        auto temp = new T[capacity];
        for (int i = 0; i < n; i++) {
            temp[i] = a[i];
        }
        auto tmp = a;
        a = temp;
        delete[](tmp);
        length = capacity;
        start = a;
        finish = a + n;
    }

};

#endif //CH1_RESIZINGARRAYBAG_H
