#ifndef CH3_SET_H
#define CH3_SET_H

#include <set>
#include <stdexcept>
#include <ostream>
#include <sstream>

using std::set;
using std::runtime_error;
using std::ostream;
using std::ostringstream;

/**
 *  The {@code SET} class represents an ordered set of comparable keys.
 *  It supports the usual <em>add</em>, <em>contains</em>, and <em>delete</em>
 *  methods. It also provides ordered methods for finding the <em>minimum</em>,
 *  <em>maximum</em>, <em>floor</em>, and <em>ceiling</em> and set methods
 *  for <em>union</em>, <em>intersection</em>, and <em>equality</em>.
 *  <p>
 *  Even though this implementation include the method {@code equals()}, it
 *  does not support the method {@code hashCode()} because sets are mutable.
 *  <p>
 *  This implementation uses a balanced binary search tree. It requires that
 *  the key type implements the {@code Comparable} interface and calls the
 *  {@code compareTo()} and method to compare two keys. It does not call either
 *  {@code equals()} or {@code hashCode()}.
 *  The <em>add</em>, <em>contains</em>, <em>delete</em>, <em>minimum</em>,
 *  <em>maximum</em>, <em>ceiling</em>, and <em>floor</em> methods take
 *  logarithmic time in the worst case.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/35applications">Section 3.5</a> of
 *  <i>Algorithms in Java, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Key> the generic type of a key in this set
 */
template<typename Key>
class SET {
public:
    /**
     * Initializes an empty set.
     */
    SET() { set_obj.clear(); }

    /**
     * Initializes a new set that is an independent copy of the specified set.
     *
     * @param x the set to copy
     */
    SET(const SET<Key> &x) : set_obj(x.set_obj) {}

    /**
     * Adds the key to this set (if it is not already present).
     *
     * @param  key the key to add
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void add(Key key) {
        set_obj.insert(key);
    }

    /**
     * Returns true if this set contains the given key.
     *
     * @param  key the key
     * @return {@code true} if this set contains {@code key};
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(Key key) {
        return set_obj.find(key) != set_obj.end();
    }

    /**
     * Removes the specified key from this set (if the set contains the specified key).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void delete_op(Key key) {
        set_obj.erase(key);
    }

    /**
     * Returns the number of keys in this set.
     *
     * @return the number of keys in this set
     */
    int size() {
        return set_obj.size();
    }

    /**
     * Returns true if this set is empty.
     *
     * @return {@code true} if this set is empty;
     *         {@code false} otherwise
     */
    bool isEmpty() {
        return set_obj.empty();
    }

    /**
     * Returns the largest key in this set.
     *
     * @return the largest key in this set
     * @throws NoSuchElementException if this set is empty
     */
    Key max() {
        if (isEmpty()) throw runtime_error("called max() with empty set");
        return *(--set_obj.end());
    }

    /**
     * Returns the smallest key in this set.
     *
     * @return the smallest key in this set
     * @throws NoSuchElementException if this set is empty
     */
    Key min() {
        if (isEmpty()) throw runtime_error("called min() with empty set");
        return *(set_obj.begin());
    }

    /**
     * Returns the smallest key in this set greater than or equal to {@code key}.
     *
     * @param  key the key
     * @return the smallest key in this set greater than or equal to {@code key}
     * @throws IllegalArgumentException if {@code key} is {@code null}
     * @throws NoSuchElementException if there is no such key
     */
    Key ceiling(Key key) {
        auto k = set_obj.lower_bound(key);
        if (k == set_obj.end()) throw runtime_error("all keys are less than this key");
        return *k;
    }

    /**
     * Returns the largest key in this set less than or equal to {@code key}.
     *
     * @param  key the key
     * @return the largest key in this set table less than or equal to {@code key}
     * @throws IllegalArgumentException if {@code key} is {@code null}
     * @throws NoSuchElementException if there is no such key
     */
    Key floor(Key key) {
        if (key < min())
            throw runtime_error("all keys are greater than this key");
        if (key >= max())
            return max();
        return *(--set_obj.lower_bound(key));
    }

    /**
     * Returns the union of this set and that set.
     *
     * @param  that the other set
     * @return the union of this set and that set
     * @throws IllegalArgumentException if {@code that} is {@code null}
     */
    SET<Key> union_op(SET<Key> &that) {
        SET<Key> c;
        for (auto x : set_obj) {
            c.add(x);
        }
        for (auto x : that) {
            c.add(x);
        }
        return c;
    }

    /**
     * Returns the intersection of this set and that set.
     *
     * @param  that the other set
     * @return the intersection of this set and that set
     * @throws IllegalArgumentException if {@code that} is {@code null}
     */
    SET<Key> intersects(SET<Key> &that) {
        SET<Key> c;
        if (size() < that.size()) {
            for (Key x : set_obj) {
                if (that.contains(x)) c.add(x);
            }
        } else {
            for (auto x : that) {
                if (contains(x)) c.add(x);
            }
        }
        return c;
    }

    /**
     * Returns all of the keys in this set, as an iterator.
     * To iterate over all of the keys in a set named {@code set}, use the
     * foreach notation: {@code for (Key key : set)}.
     *
     * @return an iterator to all of the keys in this set
     */
    typename set<Key>::iterator begin() { return set_obj.begin(); }

    typename set<Key>::iterator end() { return set_obj.end(); }

    typename set<Key>::const_iterator begin() const { return set_obj.cbegin(); }

    typename set<Key>::const_iterator end() const { return set_obj.cend(); }

    /**
     * Returns a string representation of this set.
     *
     * @return a string representation of this set, enclosed in curly braces,
     *         with adjacent keys separated by a comma and a space
     */
    friend ostream &operator<<(ostream &stream, const SET<Key> &that) {
        ostringstream ss;
        for (auto k: that)
            ss << k << " ";
        stream << ss.str();
        return stream;
    }

private:
    set<Key> set_obj;
};


#endif //CH3_SET_H
