#ifndef CH1_LINKEDBAG_H
#define CH1_LINKEDBAG_H

// TODO: move iterator out class

/**
 *  The {@code LinkedBag} class represents a bag (or multiset) of
 *  generic items. It supports insertion and iterating over the
 *  items in arbitrary order.
 *  <p>
 *  This implementation uses a singly linked list with a non-static nested class Node.
 *  See {@link Bag} for a version that uses a static nested class.
 *  The <em>add</em>, <em>isEmpty</em>, and <em>size</em> operations
 *  take constant time. Iteration takes time proportional to the number of items.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
// helper linked list class
template<typename T>
struct _node {
    T item;
    _node *next;
};

// iterator
template<typename T>
struct _link_iterator {
    _node<T> *data;
    int n;

    // initial iterator
    _link_iterator(_node<T> *data_, int n_) : data(data_), n(n_) {}

    // get current value
    T &operator*() { return data->item; }

    // next iterator
    _link_iterator &operator++() {
        n++;
        if (data) data = data->next;
        return *this;
    }

    // judge is same?
    bool operator!=(const _link_iterator &it) const { return n != it.n; }
};

template<typename T>
class LinkedBag {
private:
    int n;          // number of elements in bag
    _node<T> *first;    // beginning of bag

public:
    /**
     * Initializes an empty bag.
     */
    LinkedBag() : first(nullptr), n(0) {}

    ~LinkedBag() {
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
        first = new _node<T>();
        first->item = item;
        first->next = tmp;
        n++;
    }

    /**
     * Returns an iterator that iterates over the items in the bag in arbitrary order.
     * @return an iterator that iterates over the items in the bag in arbitrary order
     */
    _link_iterator<T> begin() { return _link_iterator<T>(first, 0); }
    _link_iterator<T> end() { return _link_iterator<T>(nullptr, n); }
    const _link_iterator<T> begin() const { return _link_iterator<T>(first, 0); }
    const _link_iterator<T> end() const { return _link_iterator<T>(nullptr, n); }
};

#endif //CH1_LINKEDBAG_H
