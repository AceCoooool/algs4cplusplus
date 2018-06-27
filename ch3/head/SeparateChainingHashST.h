#ifndef CH3_SEPARATECHAININGHASHST_H
#define CH3_SEPARATECHAININGHASHST_H

#include <vector>
#include "../head/SequentialSearchST.h"

using std::vector;

/**
 *  The {@code SeparateChainingHashST} class represents a symbol table of generic
 *  key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  Unlike {@link java.util.Map}, this class uses the convention that
 *  values cannot be {@code null}—setting the
 *  value associated with a key to {@code null} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  This implementation uses a separate chaining hash table. It requires that
 *  the key type overrides the {@code equals()} and {@code hashCode()} methods.
 *  The expected time per <em>put</em>, <em>contains</em>, or <em>remove</em>
 *  operation is constant, subject to the uniform hashing assumption.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/34hash">Section 3.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For other implementations, see {@link ST}, {@link BinarySearchST},
 *  {@link SequentialSearchST}, {@link BST}, {@link RedBlackBST}, and
 *  {@link LinearProbingHashST},
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename Key, typename Value>
class SeparateChainingHashST {
public:
    /**
     * Initializes an empty symbol table with {@code m} chains.
     * @param m the initial number of chains
     */
    SeparateChainingHashST(int m) : m(m), st(m) {}

    /**
     * Initializes an empty symbol table.
     */
    SeparateChainingHashST() : SeparateChainingHashST(INIT_CAPACITY) {}

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
     * Returns true if this symbol table contains the specified key.
     *
     * @param  key the key
     * @return {@code true} if this symbol table contains {@code key};
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(Key key) {
        int i = hash(key);
        return st[i].contains(key);
    }

    /**
     * Returns the value associated with the specified key in this symbol table.
     *
     * @param  key the key
     * @return the value associated with {@code key} in the symbol table;
     *         {@code null} if no such value
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Value get(Key key) {
        int i = hash(key);
        return st[i].get(key);
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
        // double table size if average length of list >= 10
        if (n >= 10 * m) resize(2 * m);

        int i = hash(key);
        if (!st[i].contains(key)) n++;
        st[i].put(key, val);
    }

    /**
     * Removes the specified key and its associated value from this symbol table
     * (if the key is in this symbol table).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void delete_op(Key key) {
        int i = hash(key);
        if (st[i].contains(key)) n--;
        st[i].delete_op(key);

        // halve table size if average length of list <= 2
        if (m > INIT_CAPACITY && n <= 2 * m) resize(m / 2);
    }

private:
    // hash value between 0 and m-1
    int hash(Key key) {
        return (std::hash<Key>()(key) & 0x7fffffff) % m;
    }

    // resize the hash table to have the given number of chains,
    // rehashing all of the keys
    void resize(int chains) {
        st.resize(chains);
    }

private:
    class Iterator {
        queue<Key> q;
    public:
        Iterator(vector<SequentialSearchST<Key, Value>> &f) {
            for (auto s: f) {
                for (auto k: s)
                    q.push(k);
            }
        }

        Key &operator*() {
            return q.front();
        }

        Iterator &operator++() {
            q.pop();
            return *this;
        }

        bool operator!=(const Iterator &it) { return !q.empty(); }
    };

public:
    Iterator begin() { return {st}; };

    Iterator end() { return {st}; };

private:
    static int INIT_CAPACITY;
    int n;        // number of key-value pairs
    int m;        // hash table size
    vector<SequentialSearchST<Key, Value>> st;  // array of linked-list symbol tables
};

template<typename Key, typename Value>
int SeparateChainingHashST<Key, Value>::INIT_CAPACITY = 4;

#endif //CH3_SEPARATECHAININGHASHST_H
