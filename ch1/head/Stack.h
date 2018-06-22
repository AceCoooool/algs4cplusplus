#ifndef CH1_STACK_H
#define CH1_STACK_H

// TODO: add iterator support
#include <stdexcept>
#include <memory>

using std::runtime_error;
using std::unique_ptr;


/**
 *  The {@code Stack} class represents a last-in-first-out (LIFO) stack of generic items.
 *  It supports the usual <em>push</em> and <em>pop</em> operations, along with methods
 *  for peeking at the top item, testing if the stack is empty, and iterating through
 *  the items in LIFO order.
 *  <p>
 *  This implementation uses a singly linked list with a static nested class for
 *  linked-list nodes. See {@link LinkedStack} for the version from the
 *  textbook that uses a non-static nested class.
 *  See {@link ResizingArrayStack} for a version that uses a resizing array.
 *  The <em>push</em>, <em>pop</em>, <em>peek</em>, <em>size</em>, and <em>is-empty</em>
 *  operations all take constant time in the worst case.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/13stacks">Section 1.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Item> the generic type of an item in this stack
 */
template<typename T>
class Stack {
public:
    /**
     * Initializes an empty stack.
     */
    Stack() : first(nullptr), n(0) {}

    /**
     * Returns true if this stack is empty.
     *
     * @return true if this stack is empty; false otherwise
     */
    bool isEmpty() {
        return first == nullptr;
    }

    /**
     * Returns the number of items in this stack.
     *
     * @return the number of items in this stack
     */
    int size() {
        return n;
    }

    /**
     * Adds the item to this stack.
     *
     * @param  item the item to add
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
     *
     * @return the item most recently added
     * @throws NoSuchElementException if this stack is empty
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
     *
     * @return the item most recently added to this stack
     * @throws NoSuchElementException if this stack is empty
     */
    T peek() {
        if (isEmpty()) throw runtime_error("Stack underflow");
        return first->item;
    }

private:
    class Node {
    public:
        T item;
        unique_ptr<Node> next;
    };

    int n;
    unique_ptr<Node> first;
};

#endif //CH1_STACK_H
