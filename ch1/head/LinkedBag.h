#ifndef CH1_LINKEDBAG_H
#define CH1_LINKEDBAG_H


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
template<typename T>
class LinkedBag {
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
        first = new Node(item);
        first->next = tmp;
        n++;
    }

private:
    class Node {
    public:
        Node() : next(nullptr) {}

        Node(T item) : item(item), next(nullptr) {}

        T item;
        Node *next;
    };

    // an iterator
    class Iterator {
        Node *data;
        int pos;
        int n;
    public:
        // initial iterator
        Iterator(Node *data_, int pos_, int n_) : pos(pos_), n(n_), data(data_) {}

        // get current value
        T &operator*() { return data->item; }

        // next iterator
        Iterator &operator++() {
            if (++pos == n)pos = 0;
            data = data->next;
            return *this;
        }

        // judge is same?
        bool operator!=(const Iterator &it) const { return pos != it.pos; }
    };

    // a const iterator
    class ConstIterator {
        Node *data;
        int pos;
        int n;
    public:
        // initial iterator
        ConstIterator(Node *data_, int pos_, int n_) : pos(pos_), n(n_), data(data_) {}

        // get current value
        const T &operator*() { return data->item; }

        // next iterator
        ConstIterator &operator++() {
            if (++pos == n)pos = 0;
            data = data->next;
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

    Iterator begin() { return {first, 0, n + 1}; }

    Iterator end() { return {nullptr, n, n + 1}; }

    ConstIterator begin() const { return {first, 0, n + 1}; }

    ConstIterator end() const { return {nullptr, n, n + 1}; }

private:
    int n;     // number of elements in bag
    Node *first;    // beginning of bag

};

#endif //CH1_LINKEDBAG_H
