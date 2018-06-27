#ifndef CH3_SEQUENTIALSEARCHST_H
#define CH3_SEQUENTIALSEARCHST_H

// TODO: change to shared_ptr or unique_ptr
#include <stdexcept>
#include <queue>

using std::runtime_error;
using std::queue;

/**
 *  The {@code SequentialSearchST} class represents an (unordered)
 *  symbol table of generic key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  The class also uses the convention that values cannot be {@code null}. Setting the
 *  value associated with a key to {@code null} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  This implementation uses a singly-linked list and sequential search.
 *  It relies on the {@code equals()} method to test whether two keys
 *  are equal. It does not call either the {@code compareTo()} or
 *  {@code hashCode()} method.
 *  The <em>put</em> and <em>delete</em> operations take linear time; the
 *  <em>get</em> and <em>contains</em> operations takes linear time in the worst case.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/31elementary">Section 3.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename Key, typename Value>
class SequentialSearchST {
public:
    /**
     * Initializes an empty symbol table.
     */
    SequentialSearchST() : n(0), first(nullptr) {}

    /**
     * Returns the number of key-value pairs in this symbol table.
     *
     * @return the number of key-value pairs in this symbol table
     */
    int size() {
        return n;
    }

    /**
     * Returns true if this symbol table is empty.
     *
     * @return {@code true} if this symbol table is empty;
     *         {@code false} otherwise
     */
    bool isEmpty() {
        return size() == 0;
    }

    /**
     * Returns the value associated with the given key in this symbol table.
     *
     * @param  key the key
     * @return the value associated with the given key if the key is in the symbol table
     *     and {@code null} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Value get(Key key) {
        for (auto x = first; x != nullptr; x = x->next) {
            if (key == x->key)
                return x->val;
        }
        throw runtime_error("key is not in");
    }

    /**
     * Returns true if this symbol table contains the specified key.
     *
     * @param  key the key
     * @return {@code true} if this symbol table contains {@code key};
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(Key key) {
        for (auto x = first; x != nullptr; x = x->next) {
            if (key == x->key)
                return true;
        }
        return false;
    }

    /**
     * Inserts the specified key-value pair into the symbol table, overwriting the old
     * value with the new value if the symbol table already contains the specified key.
     * Deletes the specified key (and its associated value) from this symbol table
     * if the specified value is {@code null}.
     *
     * @param  key the key
     * @param  val the value
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void put(Key key, Value val) {
        for (auto x = first; x != nullptr; x = x->next) {
            if (key == x->key) {
                x->val = val;
                return;
            }
        }
        first = new Node(key, val, first);
        n++;
    }

    /**
     * Removes the specified key and its associated value from this symbol table
     * (if the key is in this symbol table).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void delete_op(Key key) {
        first = delete_op(first, key);
    }

private:
    // a helper linked list data type
    class Node {
    public:
        Key key;
        Value val;
        Node *next;

        Node(Key key_, Value val_, Node *next_) : key(key_), val(val_), next(next_) {}
    };

    // delete key in linked list beginning at Node x
    // warning: function call stack too large if table is large
    Node *delete_op(Node *x, Key key) {
        if (x == nullptr) return nullptr;
        if (key == x->key) {
            n--;
            auto tmp = x->next;
            delete (x);
            return tmp;
        }
        x->next = delete_op(x->next, key);
        return x;
    }

private:
    class Iterator {
        queue<Key> q;
    public:
        Iterator(Node *f) {
            for (auto x = f; x != nullptr; x = x->next)
                q.push(x->key);
        }

        Key &operator*() {
            return q.front();
        }

        Iterator &operator++() {
            q.pop();
            return *this;
        }

        bool operator!=(const Iterator &it) { return q != it.q; }
    };

public:
    Iterator begin() { return {first}; };

    Iterator end() { return {nullptr}; };

private:
    int n;          // number of key-value pairs
    Node *first;    // the linked list of key-value pairs
};

#endif //CH3_SEQUENTIALSEARCHST_H
