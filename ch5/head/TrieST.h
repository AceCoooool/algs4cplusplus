#ifndef CH5_TRIEST_H
#define CH5_TRIEST_H

#include <vector>
#include <string>
#include <queue>
#include <stdexcept>
#include <numeric>
#include <limits>

using std::queue;
using std::vector;
using std::string;
using std::to_string;
using std::invalid_argument;
using std::runtime_error;
using std::numeric_limits;


/**
 *  The {@code TrieST} class represents an symbol table of key-value
 *  pairs, with string keys and generic values.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides character-based methods for finding the string
 *  in the symbol table that is the <em>longest prefix</em> of a given prefix,
 *  finding all strings in the symbol table that <em>start with</em> a given prefix,
 *  and finding all strings in the symbol table that <em>match</em> a given pattern.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  Unlike {@link java.util.Map}, this class uses the convention that
 *  values cannot be {@code null}—setting the
 *  value associated with a key to {@code null} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  This implementation uses a 256-way trie.
 *  The <em>put</em>, <em>contains</em>, <em>delete</em>, and
 *  <em>longest prefix</em> operations take time proportional to the length
 *  of the key (in the worst case). Construction takes constant time.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/52trie">Section 5.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 */
template<typename Value>
class TrieST {
private:
    class Node {
    public:
        Node() : next(256, nullptr), flag(false), val(0) {}

        ~Node() {
            for (int i = 0; i < R; ++i)
                if (next[i]) delete (next[i]);
        }

        Value val;
        bool flag;
        vector<Node *> next;
    };

public:
    TrieST() : n(0), root(nullptr) {}

    ~TrieST() { delete (root); }

    /**
     * Returns the value associated with the given key.
     * @param key the key
     * @return the value associated with the given key if the key is in the symbol table
     *     and {@code null} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Value get(string key) {
        if (key.empty()) throw invalid_argument("argument to get() is null");
        Node *x = get(root, key, 0);
        if (x == nullptr) throw runtime_error("without this key");
        return x->val;
    }

    /**
     * Does this symbol table contain the given key?
     * @param key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *     {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(string key) {
        if (key.empty()) throw invalid_argument("argument to contains() is null");
        return get(key) != nullptr;
    }

    /**
     * Inserts the key-value pair into the symbol table, overwriting the old value
     * with the new value if the key is already in the symbol table.
     * If the value is {@code null}, this effectively deletes the key from the symbol table.
     * @param key the key
     * @param val the value
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void put(string key, Value val) {
        if (key.empty()) throw invalid_argument("first argument to put() is null");
        else root = put(this->root, key, val, 0);
    }

    /**
     * Returns the number of key-value pairs in this symbol table.
     * @return the number of key-value pairs in this symbol table
     */
    int size() {
        return n;
    }

    /**
     * Is this symbol table empty?
     * @return {@code true} if this symbol table is empty and {@code false} otherwise
     */
    bool isEmpty() {
        return size() == 0;
    }

    /**
     * Returns all keys in the symbol table as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     * @return all keys in the symbol table as an {@code Iterable}
     */
    queue<string> keys() {
        return keysWithPrefix("");
    }

    /**
     * Returns all of the keys in the set that start with {@code prefix}.
     * @param prefix the prefix
     * @return all of the keys in the set that start with {@code prefix},
     *     as an iterable
     */
    queue<string> keysWithPrefix(string prefix) {
        queue<string> results;
        Node *x = get(root, prefix, 0);
        collect(x, prefix, results);
        return results;
    }

    /**
     * Returns all of the keys in the symbol table that match {@code pattern},
     * where . symbol is treated as a wildcard character.
     * @param pattern the pattern
     * @return all of the keys in the symbol table that match {@code pattern},
     *     as an iterable, where . is treated as a wildcard character.
     */
    queue<string> keysThatMatch(string pattern) {
        queue<string> results;
        collect(root, "", pattern, results);
        return results;
    }

    /**
     * Returns the string in the symbol table that is the longest prefix of {@code query},
     * or {@code null}, if no such string.
     * @param query the query string
     * @return the string in the symbol table that is the longest prefix of {@code query},
     *     or {@code null} if no such string
     * @throws IllegalArgumentException if {@code query} is {@code null}
     */
    string longestPrefixOf(string query) {
        if (query.empty()) throw invalid_argument("argument to longestPrefixOf() is null");
        int length = longestPrefixOf(root, query, 0, -1);
        if (length == -1) return "";
        else return query.substr(0, length);
    }

    /**
     * Removes the key from the set if the key is present.
     * @param key the key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void delete_(string key) {
        if (key.empty()) throw invalid_argument("argument to delete() is null");
        root = delete_(root, key, 0);
    }

private:
    Node *get(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

    Node *put(Node *x, string key, Value val, int d) {
        if (x == nullptr) x = new Node();
        if (d == key.length()) {
            x->val = val;
            x->flag = true;
            return x;
        }
        char c = key[d];
        x->next[c] = put(x->next[c], key, val, d + 1);
        return x;
    }

    void collect(Node *x, string prefix, queue<string> &results) {
        if (x == nullptr) return;
        if (x->flag) results.push(prefix);
        for (unsigned char c = 0;; c++) {
            prefix.push_back(c);
            collect(x->next[c], prefix, results);
            prefix.pop_back();
            if (c == R - 1) break;
        }
    }

    void collect(Node *x, string prefix, string pattern, queue<string> &results) {
        if (x == nullptr) return;
        int d = prefix.length();
        if (d == pattern.length() && x->flag)
            results.push(prefix);
        if (d == pattern.length())
            return;
        char c = pattern[d];
        if (c == '.') {
            for (unsigned char ch = 0;; ch++) {
                prefix.push_back(ch);
                collect(x->next[ch], prefix, pattern, results);
                prefix.pop_back();
                if (ch == R - 1) break;
            }
        } else {
            prefix.push_back(c);
            collect(x->next[c], prefix, pattern, results);
            prefix.pop_back();
        }
    }

    // returns the length of the longest string key in the subtrie
    // rooted at x that is a prefix of the query string,
    // assuming the first d character match and we have already
    // found a prefix match of given length (-1 if no such match)
    int longestPrefixOf(Node *x, string query, int d, int length) {
        if (x == nullptr) return length;
        if (x->flag) length = d;
        if (d == query.length()) return length;
        char c = query[d];
        return longestPrefixOf(x->next[c], query, d + 1, length);
    }

    Node *delete_(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) {
            if (x->flag) n--;
            x->flag = false;
        } else {
            char c = key[d];
            x->next[c] = delete_(x->next[c], key, d + 1);
        }

        // remove subtrie rooted at x if it is completely empty
        if (x->flag) return x;
        for (int c = 0; c < R; c++)
            if (x->next[c] != nullptr)
                return x;
        return nullptr;
    }


private:
    static const int R;
    Node *root;   // root of trie
    int n;        // number of keys in trie
};

template<typename Value>
const int TrieST<Value>::R = 256;

#endif //CH5_TRIEST_H
