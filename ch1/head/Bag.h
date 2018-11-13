#ifndef CH1_BAG_H
#define CH1_BAG_H

#include "LinkedBag.h"

/**
 *  The {@code Bag} class represents a bag (or multiset) of
 *  generic items. It supports insertion and iterating over the
 *  items in arbitrary order.
 *  <p>
 *  This implementation uses a singly linked list with a static nested class Node.
 *  See {@link LinkedBag} for the version from the
 *  textbook that uses a non-static nested class.
 *  See {@link ResizingArrayBag} for a version that uses a resizing array.
 *  The <em>add</em>, <em>isEmpty</em>, and <em>size</em> operations
 *  take constant time. Iteration takes time proportional to the number of items.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Item> the generic type of an item in this bag
 */
template<typename T>
class Bag {
private:
    using Node = _node<T>;
    using iterator = _link_iterator<T>;

    int n;          // number of elements in bag
    Node *first;    // beginning of bag

public:
    /**
     * Initializes an empty bag.
     */
    Bag() : first(nullptr), n(0) {}

    ~Bag() {
        while (first) {
            auto tmp = first;
            first = first->next;
            delete (tmp);
        }
    }

    /**
     * Is this bag empty?
     * @return true if this bag is empty; false otherwise
     */
    bool isEmpty() const {
        return first == nullptr;
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
        auto tmp = first;
        first = new Node();
        first->item = item;
        first->next = tmp;
        n++;
    }


    /**
     * Returns an iterator that iterates over the items in the bag in arbitrary order.
     * @return an iterator that iterates over the items in the bag in arbitrary order
     */
    iterator begin() { return _link_iterator<T>(first, 0); }
    iterator end() { return _link_iterator<T>(nullptr, n); }
    const iterator begin() const { return _link_iterator<T>(first, 0); }
    const iterator end() const { return _link_iterator<T>(nullptr, n); }
};

#endif //CH1_BAG_H
