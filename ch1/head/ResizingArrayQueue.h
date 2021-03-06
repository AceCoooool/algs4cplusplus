#ifndef CH1_RESIZINGARRAYQUEUE_H
#define CH1_RESIZINGARRAYQUEUE_H

#include <stdexcept>

using std::runtime_error;

/**
 *  The {@code ResizingArrayQueue} class represents a first-in-first-out (FIFO)
 *  queue of generic items.
 *  It supports the usual <em>enqueue</em> and <em>dequeue</em>
 *  operations, along with methods for peeking at the first item,
 *  testing if the queue is empty, and iterating through
 *  the items in FIFO order.
 *  <p>
 *  This implementation uses a resizing array, which double the underlying array
 *  when it is full and halves the underlying array when it is one-quarter full.
 *  The <em>enqueue</em> and <em>dequeue</em> operations take constant amortized time.
 *  The <em>size</em>, <em>peek</em>, and <em>is-empty</em> operations takes
 *  constant time in the worst case.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename T>
class ResizingArrayQueue {
private:
    T *q;                     // queue elements
    int length;               // capacity of q
    int n;                    // number of elements on queue
    int first;                // index of first element of queue
    int last;                 // index of next available slot

public:
    /**
     * Initializes an empty queue.
     */
    ResizingArrayQueue() : q(new T[2]), n(0), first(0), last(0), length(2) {}

    ~ResizingArrayQueue() { delete[](q); }

    /**
     * Is this queue empty?
     * @return true if this queue is empty; false otherwise
     */
    bool isEmpty() const {
        return n == 0;
    }

    /**
     * Returns the number of items in this queue.
     * @return the number of items in this queue
     */
    int size() const {
        return n;
    }

    /**
     * Adds the item to this queue.
     * @param item the item to add
     */
    void enqueue(T &item) {
        // double size of array if necessary and recopy to front of array
        if (n == length) resize(2 * length);   // double size of array if necessary
        q[last++] = item;                      // add item
        if (last == length) last = 0;          // wrap-around
        n++;
    }

    /**
     * Removes and returns the item on this queue that was least recently added.
     * @return the item on this queue that was least recently added
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    T dequeue() {
        if (isEmpty()) throw runtime_error("Queue underflow");
        T item = q[first];
        n--;
        first++;
        if (first == length) first = 0;           // wrap-around
        // shrink size of array if necessary
        if (n > 0 && n == length / 4) resize(length / 2);
        return item;
    }

    /**
     * Returns the item least recently added to this queue.
     * @return the item least recently added to this queue
     * @throws java.util.NoSuchElementException if this queue is empty
     */
    T peek() const {
        if (isEmpty()) throw runtime_error("Queue underflow");
        return q[first];
    }


private:
    // resize the underlying array
    void resize(int capacity) {
        if (capacity < n) throw runtime_error("illegal capacity");
        auto tmp = new T[capacity];
        for (int i = 0; i < n; i++) {
            tmp[i] = q[(first + i) % length];
        }
        auto temp = q;
        q = tmp;
        delete[] (temp);
        first = 0;
        last = n;
        length = capacity;
    }
};


#endif //CH1_RESIZINGARRAYQUEUE_H
