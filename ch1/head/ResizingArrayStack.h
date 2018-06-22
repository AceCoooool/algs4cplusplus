#ifndef CH1_RESIZINGARRAYSTACK_H
#define CH1_RESIZINGARRAYSTACK_H

// TODO: add iterator support
#include <vector>
#include <stdexcept>
#include <memory>

using std::unique_ptr;
using std::runtime_error;
using std::vector;

/**
 *  The {@code ResizingArrayStack} class represents a last-in-first-out (LIFO) stack
 *  of generic items.
 *  It supports the usual <em>push</em> and <em>pop</em> operations, along with methods
 *  for peeking at the top item, testing if the stack is empty, and iterating through
 *  the items in LIFO order.
 *  <p>
 *  This implementation uses a resizing array, which double the underlying array
 *  when it is full and halves the underlying array when it is one-quarter full.
 *  The <em>push</em> and <em>pop</em> operations take constant amortized time.
 *  The <em>size</em>, <em>peek</em>, and <em>is-empty</em> operations takes
 *  constant time in the worst case.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename T>
class ResizingArrayStack {
public:
    /**
     * Initializes an empty stack.
     */
    ResizingArrayStack() : n(0), a(new vector<T>(2)) {}

    /**
     * Is this stack empty?
     * @return true if this stack is empty; false otherwise
     */
    bool isEmpty() {
        return n == 0;
    }

    /**
     * Returns the number of items in the stack.
     * @return the number of items in the stack
     */
    int size() {
        return n;
    }

    /**
     * Adds the item to this stack.
     * @param item the item to add
     */
    void push(T item) {
        if (n == length) resize(2 * length);    // double size of array if necessary
        (*a.get())[n++] = item;                            // add item
    }

    /**
     * Removes and returns the item most recently added to this stack.
     * @return the item most recently added
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    T pop() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        T item = (*a.get())[n - 1];
        n--;
        // shrink size of array if necessary
        if (n > 0 && n == length / 4) resize(length / 2);
        return item;
    }

    /**
     * Returns (but does not remove) the item most recently added to this stack.
     * @return the item most recently added to this stack
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    T peek() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        return (*a.get())[n - 1];
    }


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
    unique_ptr<vector<T>> a;
    int length = 2;
    int n;          // number of elements on stack
};

#endif //CH1_RESIZINGARRAYSTACK_H
