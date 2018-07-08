#ifndef CH1_QUEUE_H
#define CH1_QUEUE_H


// TODO: add iterator support

#include <stdexcept>

using std::runtime_error;

/**
 *  The {@code LinkedQueue} class represents a first-in-first-out (FIFO)
 *  queue of generic items.
 *  It supports the usual <em>enqueue</em> and <em>dequeue</em>
 *  operations, along with methods for peeking at the first item,
 *  testing if the queue is empty, and iterating through
 *  the items in FIFO order.
 *  <p>
 *  This implementation uses a singly linked list with a non-static nested class
 *  for linked-list nodes.  See {@link Queue} for a version that uses a static nested class.
 *  The <em>enqueue</em>, <em>dequeue</em>, <em>peek</em>, <em>size</em>, and <em>is-empty</em>
 *  operations all take constant time in the worst case.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename T>
class Queue {
public:
    /**
     * Initializes an empty queue.
     */
    Queue() : n(0), first(nullptr), last(nullptr) {}

    ~Queue() {
        while (first != last) {
            auto tmp = first;
            first = first->next;
            delete (tmp);
        }
        delete (last);
    }

    /**
     * Is this queue empty?
     * @return true if this queue is empty; false otherwise
     */
    bool isEmpty() {
        return first == nullptr;
    }

    /**
     * Returns the number of items in this queue.
     * @return the number of items in this queue
     */
    int size() {
        return n;
    }

    /**
     * Returns the item least recently added to this queue.
     * @return the item least recently added to this queue
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    T peek() {
        if (isEmpty()) throw runtime_error("Queue underflow");
        return first->item;
    }

    /**
     * Adds the item to this queue.
     * @param item the item to add
     */
    void enqueue(T item) {
        auto tmp = last;
        last = new Node(item);
        if (isEmpty()) first = last;
        else tmp->next = last;
        n++;
    }

    /**
     * Removes and returns the item on this queue that was least recently added.
     * @return the item on this queue that was least recently added
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    T dequeue() {
        if (isEmpty()) throw runtime_error("Queue underflow");
        T item = first->item;
        auto tmp = first;
        first = first->next;
        delete (tmp);
        n--;
        if (isEmpty()) last = nullptr;   // to avoid loitering
        return item;
    }

private:
    // helper linked list class
    class Node {
    public:
        Node() : next(nullptr) {}

        Node(T item) : item(item), next(nullptr) {}

        T item;
        Node *next;
    };

    int n;         // number of elements on queue
    Node *first;    // beginning of queue
    Node *last;     // end of queue
};


#endif //CH1_QUEUE_H
