#ifndef CH1_LINKEDSTACK_H
#define CH1_LINKEDSTACK_H

// TODO: add iterator support
#include <stdexcept>
#include <memory>

using std::runtime_error;
using std::unique_ptr;


/**
 *  The {@code LinkedStack} class represents a last-in-first-out (LIFO) stack of
 *  generic items.
 *  It supports the usual <em>push</em> and <em>pop</em> operations, along with methods
 *  for peeking at the top item, testing if the stack is empty, and iterating through
 *  the items in LIFO order.
 *  <p>
 *  This implementation uses a singly linked list with a non-static nested class for
 *  linked-list nodes. See {@link Stack} for a version that uses a static nested class.
 *  The <em>push</em>, <em>pop</em>, <em>peek</em>, <em>size</em>, and <em>is-empty</em>
 *  operations all take constant time in the worst case.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename T>
class LinkedStack {
public:
    /**
     * Initializes an empty stack.
     */
    LinkedStack() : n(0), first(nullptr) {}

    /**
     * Is this stack empty?
     * @return true if this stack is empty; false otherwise
     */
    bool isEmpty() {
        return first == nullptr;
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
        auto oldfirst = move(first);
        first.reset(new Node());
        first->item = item;
        first->next = move(oldfirst);
        n++;
    }

    /**
     * Removes and returns the item most recently added to this stack.
     * @return the item most recently added
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    T pop() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        T item = first->item;        // save item to return
        first = move(first->next);            // delete first node
        n--;
        return item;                   // return the saved item
    }

    /**
     * Returns (but does not remove) the item most recently added to this stack.
     * @return the item most recently added to this stack
     * @throws java.util.NoSuchElementException if this stack is empty
     */
    T peek() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        return first->item;
    }

private:
    // helper linked list class
    class Node {
    public:
        T item;
        unique_ptr<Node> next;
    };

private:
    int n;        // size of the stack
    unique_ptr<Node> first;   // top of stack
};

#endif //CH1_LINKEDSTACK_H
