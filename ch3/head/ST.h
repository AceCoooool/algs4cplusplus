#ifndef CH3_ST_H
#define CH3_ST_H

#include <map>
#include <stdexcept>

using std::map;
using std::runtime_error;

/**
 *  The {@code ST} class represents an ordered symbol table of generic
 *  key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides ordered methods for finding the <em>minimum</em>,
 *  <em>maximum</em>, <em>floor</em>, and <em>ceiling</em>.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  Unlike {@link java.util.Map}, this class uses the convention that
 *  values cannot be {@code null}—setting the
 *  value associated with a key to {@code null} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  This implementation uses a balanced binary search tree. It requires that
 *  the key type implements the {@code Comparable} interface and calls the
 *  {@code compareTo()} and method to compare two keys. It does not call either
 *  {@code equals()} or {@code hashCode()}.
 *  The <em>put</em>, <em>contains</em>, <em>remove</em>, <em>minimum</em>,
 *  <em>maximum</em>, <em>ceiling</em>, and <em>floor</em> operations each take
 *  logarithmic time in the worst case.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/35applications">Section 3.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Key> the generic type of keys in this symbol table
 *  @param <Value> the generic type of values in this symbol table
 */
template<typename Key, typename Value>
class ST {
public:
    /**
     * Initializes an empty symbol table.
     */
    ST() : st(map<Key, Value>()) {}

    /**
     * Returns the value associated with the given key in this symbol table.
     *
     * @param  key the key
     * @return the value associated with the given key if the key is in this symbol table;
     *         {@code null} if the key is not in this symbol table
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */

    //TODO: lvalue may be a bug
    Value& get (const Key key) {
        if (st.find(key) == st.end()) throw runtime_error("key is not in symbol table!");
        return st[key];
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
        st[key] = val;
    }

    /**
     * Removes the specified key and its associated value from this symbol table
     * (if the key is in this symbol table).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void delete_op(Key key) {
        if (st.find(key) == st.end()) throw runtime_error("calls delete() with null key");
        st.erase(key);
    }

    /**
     * Returns true if this symbol table contain the given key.
     *
     * @param  key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(Key key) {
        return st.find(key) != st.end();
    }

    /**
     * Returns the number of key-value pairs in this symbol table.
     *
     * @return the number of key-value pairs in this symbol table
     */
    int size() {
        return st.size();
    }

    /**
     * Returns true if this symbol table is empty.
     *
     * @return {@code true} if this symbol table is empty and {@code false} otherwise
     */
    bool isEmpty() {
        return st.empty();
    }

    /**
     * Returns all keys in this symbol table.
     * <p>
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     *
     * @return all keys in this symbol table
     */
    // TODO:

    /**
     * Returns the smallest key in this symbol table.
     *
     * @return the smallest key in this symbol table
     * @throws NoSuchElementException if this symbol table is empty
     */
    Key min() {
        if (isEmpty()) throw runtime_error("calls min() with empty symbol table");
        return st.begin()->first;
    }

    /**
     * Returns the largest key in this symbol table.
     *
     * @return the largest key in this symbol table
     * @throws NoSuchElementException if this symbol table is empty
     */
    Key max() {
        if (isEmpty()) throw runtime_error("calls max() with empty symbol table");
        return (st.end() - 1)->first;
    }

    /**
     * Returns the smallest key in this symbol table greater than or equal to {@code key}.
     *
     * @param  key the key
     * @return the smallest key in this symbol table greater than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Key ceiling(Key key) {
        auto k = st.upper_bound(key);
        if (k == st.end()) throw runtime_error("all keys are less than this key");
        return k->first;
    }

    /**
     * Returns the largest key in this symbol table less than or equal to {@code key}.
     *
     * @param  key the key
     * @return the largest key in this symbol table less than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Key floor(Key key) {
        auto k = st.lower_bound(key);
        if (k == st.end()) throw runtime_error("all keys are greater than this key");
        return k;
    }


public:
    typename map<Key, Value>::iterator begin() { return st.begin(); }

    typename map<Key, Value>::iterator end() { return st.end(); }

    // TODO: bug here
    typename map<Key, Value>::const_iterator begin() const { return st.cbegin(); }

    typename map<Key, Value>::const_iterator end() const { return st.cend(); }


private:
    map<Key, Value> st;
};

#endif //CH3_ST_H
