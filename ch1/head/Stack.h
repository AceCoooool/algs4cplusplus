#ifndef CH1_STACK_H
#define CH1_STACK_H

#include <stdexcept>

using std::runtime_error;


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
private:
    // helper linked list class
    class Node {
    public:
        Node() : next(nullptr) {}
        Node(T item) : item(item), next(nullptr) {}

        T item;
        Node *next;
    };

    int n;          // size of the stack
    Node *first;    // top of stack

public:
    /**
     * Initializes an empty stack.
     */
    Stack() : first(nullptr), n(0) {}

    ~Stack() {
        while (first) {
            auto tmp = first;
            first = first->next;
            delete (tmp);
        }
    }

    /**
     * Returns true if this stack is empty.
     *
     * @return true if this stack is empty; false otherwise
     */
    bool isEmpty() const {
        return first == nullptr;
    }

    /**
     * Returns the number of items in this stack.
     *
     * @return the number of items in this stack
     */
    int size() const {
        return n;
    }

    /**
     * Adds the item to this stack.
     *
     * @param  item the item to add
     */
    void push(T &item) {
        auto tmp = first;
        first = new Node(item);
        first->next = tmp;
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
        T item = first->item;           // save item to return
        auto tmp = first;
        first = first->next;            // delete first node
        n--;
        delete (tmp);
        return item;                    // return the saved item
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
    
};

#endif //CH1_STACK_H
