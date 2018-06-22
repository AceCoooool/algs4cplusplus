#ifndef CH1_BAG_H
#define CH1_BAG_H

#include <memory>

using std::unique_ptr;


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
public:
    /**
     * Initializes an empty bag.
     */
    Bag() : first(nullptr), n(0) {}

    /**
     * Is this bag empty?
     * @return true if this bag is empty; false otherwise
     */
    bool isEmpty() {
        return first == nullptr;
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
        auto oldfirst = move(first);
        first.reset(new Node());
        first->item = item;
        first->next = move(oldfirst);
        n++;
    }

private:
    class Node {
    public:
        T item;
        unique_ptr<Node> next;
    };

    // an iterator
    class Iterator {
        unique_ptr<Node> data;
        int pos;
        int n;
    public:
        // initial iterator
        Iterator(Node *data_, int pos_, int n_) : pos(pos_), n(n_) { data.reset(data_); }

        // get current value
        T &operator*() { return data.get()->item; }

        // next iterator
        Iterator &operator++() {
            if (++pos == n)pos = 0;
            data = move(data->next);
            return *this;
        }

        // judge is same?
        bool operator!=(const Iterator &it) const { return pos != it.pos; }
    };

    // a const iterator
    class ConstIterator {
        unique_ptr<Node> data;
        int pos;
        int n;
    public:
        // initial iterator
        ConstIterator(Node *data_, int pos_, int n_) : pos(pos_), n(n_) {
            data.reset(data_);
        }

        // get current value
        const T &operator*() { return data.get()->item; }

        // next iterator
        ConstIterator &operator++() {
            if (++pos == n)pos = 0;
            data = move(data->next);
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

    Iterator begin() { return {first.get(), 0, n + 1}; }

    Iterator end() { return {nullptr, n, n + 1}; }

    ConstIterator begin() const { return {first.get(), 0, n + 1}; }

    ConstIterator end() const { return {nullptr, n, n + 1}; }

private:
    int n;     // number of elements in bag
    unique_ptr<Node> first;    // beginning of bag

};

#endif //CH1_BAG_H
