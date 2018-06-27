#ifndef CH3_LINEARPROBINGHASHST_H
#define CH3_LINEARPROBINGHASHST_H

#include <vector>
#include <stdexcept>
#include <queue>

using std::vector;
using std::runtime_error;
using std::queue;

/**
 *  The {@code LinearProbingHashST} class represents a symbol table of generic
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
 *  This implementation uses a linear probing hash table. It requires that
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
 *  {@link SeparateChainingHashST},
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename Key, typename Value>
class LinearProbingHashST {
public:
    /**
     * Initializes an empty symbol table with the specified initial capacity.
     *
     * @param capacity the initial capacity
     */
    LinearProbingHashST(int capacity) : m(capacity), n(0), keys(capacity), vals(capacity), flags(capacity, true) {}

    /**
     * Initializes an empty symbol table.
     */
    LinearProbingHashST() : LinearProbingHashST(INIT_CAPACITY) {}

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
        for (int i = hash(key); !flags[i]; i = (i + 1) % m)
            if (keys[i] == key)
                return true;
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
        // double table size if 50% full
        if (n >= m / 2) resize(2 * m);

        int i;
        for (i = hash(key); !flags[i]; i = (i + 1) % m) {
            if (keys[i] == key) {
                vals[i] = val;
                return;
            }
        }
        keys[i] = key;
        vals[i] = val;
        flags[i] = false;
        n++;
    }

    /**
     * Returns the value associated with the specified key.
     * @param key the key
     * @return the value associated with {@code key};
     *         {@code null} if no such value
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Value get(Key key) {
        for (int i = hash(key); !flags[i]; i = (i + 1) % m)
            if (keys[i] == key)
                return vals[i];
        throw runtime_error("illegal key");
    }

    /**
     * Removes the specified key and its associated value from this symbol table
     * (if the key is in this symbol table).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void delete_op(Key key) {
        if (!contains(key)) return;

        // find position i of key
        int i = hash(key);
        while (key != keys[i]) {
            i = (i + 1) % m;
        }

        // delete key and associated value
        flags[i] = true;

        // rehash all keys in same cluster
        i = (i + 1) % m;
        while (!flags[i]) {
            // delete keys[i] an vals[i] and reinsert
            Key keyToRehash = keys[i];
            Value valToRehash = vals[i];
            flags[i] = true;
            n--;
            put(keyToRehash, valToRehash);
            i = (i + 1) % m;
        }
        n--;
        // halves size of array if it's 12.5% full or less
        if (n > 0 && n <= m / 8) resize(m / 2);
    }

private:
    class Iterator {
        queue<Key> q;
    public:
        Iterator(vector<Key> &k, vector<bool> &flag, int m) {
            for (int i = 0; i < m; ++i) {
                if (!flag[i])
                    q.push(k[i]);
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
    Iterator begin() { return {keys, flags, m}; };

    Iterator end() { return {keys, flags, m}; };

private:
    // hash function for keys - returns value between 0 and M-1
    int hash(Key key) {
        return (std::hash<Key>()(key) & 0x7fffffff) % m;
    }

    // resizes the hash table to the given capacity by re-hashing all of the keys
    void resize(int capacity) {
        vector<bool> tf(flags.begin(), flags.end());
        int tmp = m;
        keys.resize(capacity);
        vals.resize(capacity);
        flags.resize(capacity);
        flags.assign(capacity, true);
        m = capacity;
        for (int i = 0; i < tmp; ++i) {
            if (!tf[i]) {
                this->put(keys[i], vals[i]);
            }
        }
    }

private:
    static int INIT_CAPACITY;
    int n;        // number of key-value pairs in the symbol table
    int m;        // size of linear probing table
    vector<Key> keys;     // the keys
    vector<Value> vals;   // the values
    vector<bool> flags;   // to tell whether this position is "usable"
};

template<typename Key, typename Value>
int LinearProbingHashST<Key, Value>::INIT_CAPACITY = 4;

#endif //CH3_LINEARPROBINGHASHST_H
