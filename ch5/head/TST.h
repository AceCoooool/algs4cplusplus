#ifndef CH5_TST_H
#define CH5_TST_H

#include <string>
#include <queue>
#include <stdexcept>

using std::string;
using std::queue;
using std::invalid_argument;
using std::runtime_error;

/**
 *  The {@code TST} class represents an symbol table of key-value
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
 *  This implementation uses a ternary search trie.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/52trie">Section 5.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 */
template<typename Value>
class TST {
private:
    class Node {
    public:
        Node() : left(nullptr), mid(nullptr), right(nullptr), isString(false) {}

        ~Node() {
            if (left) delete (left);
            if (mid) delete (mid);
            if (right) delete (right);
        }

        unsigned char c;         // character
        bool isString;
        Node *left, *mid, *right;  // left, middle, and right subtries
        Value val;               // value associated with string
    };

public:
    /**
     * Initializes an empty string symbol table.
     */
    TST() : root(nullptr), n(0) {}

    ~TST() {
        delete (root);
    }

    /**
     * Returns the number of key-value pairs in this symbol table.
     * @return the number of key-value pairs in this symbol table
     */
    int size() {
        return n;
    }

    /**
     * Does this symbol table contain the given key?
     * @param key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *     {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(string key) {
        if (key.empty()) {
            throw invalid_argument("argument to contains() is null");
        }
        return get(root, key, 0) != nullptr;
    }

    /**
     * Returns the value associated with the given key.
     * @param key the key
     * @return the value associated with the given key if the key is in the symbol table
     *     and {@code null} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Value get(string key) {
        if (key.empty()) {
            throw invalid_argument("calls get() with null argument");
        }
        Node *x = get(root, key, 0);
        if (x == nullptr) throw runtime_error("this key not in this table");
        return x->val;
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
        if (key.empty()) {
            throw invalid_argument("calls put() with null key");
        }
        if (!contains(key)) n++;
        root = put(root, key, val, 0);
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
        if (query.length() == 0) return "";
        int length = 0;
        Node *x = root;
        int i = 0;
        while (x != nullptr && i < query.length()) {
            char c = query[i];
            if (c < x->c) x = x->left;
            else if (c > x->c) x = x->right;
            else {
                i++;
                if (x->isString) length = i;
                x = x->mid;
            }
        }
        return query.substr(0, length);
    }

    /**
     * Returns all keys in the symbol table as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     * @return all keys in the symbol table as an {@code Iterable}
     */
    queue<string> keys() {
        queue<string> queue1;
        string tmp = "";
        collect(root, tmp, queue1);
        return queue1;
    }

    /**
     * Returns all of the keys in the set that start with {@code prefix}.
     * @param prefix the prefix
     * @return all of the keys in the set that start with {@code prefix},
     *     as an iterable
     * @throws IllegalArgumentException if {@code prefix} is {@code null}
     */
    queue<string> keysWithPrefix(string prefix) {
        if (prefix.empty()) {
            throw invalid_argument("calls keysWithPrefix() with null argument");
        }
        queue<string> queue;
        Node *x = get(root, prefix, 0);
        if (x == nullptr) return queue;
        if (x->isString) queue.push(prefix);
        collect(x->mid, prefix, queue);
        return queue;
    }

    /**
     * Returns all of the keys in the symbol table that match {@code pattern},
     * where . symbol is treated as a wildcard character.
     * @param pattern the pattern
     * @return all of the keys in the symbol table that match {@code pattern},
     *     as an iterable, where . is treated as a wildcard character.
     */
    queue<string> keysThatMatch(string pattern) {
        queue<string> queue;
        string prefix = "";
        collect(root, prefix, 0, pattern, queue);
        return queue;
    }

private:
    // return subtrie corresponding to given key
    Node *get(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (key.length() == 0) throw invalid_argument("key must have length >= 1");
        unsigned char c = key[d];
        if (c < x->c) return get(x->left, key, d);
        else if (c > x->c) return get(x->right, key, d);
        else if (d < key.length() - 1) return get(x->mid, key, d + 1);
        else return x;
    }


    Node *put(Node *x, string key, Value val, int d) {
        char c = key[d];
        if (x == nullptr) {
            x = new Node();
            x->c = c;
        }
        if (c < x->c) x->left = put(x->left, key, val, d);
        else if (c > x->c) x->right = put(x->right, key, val, d);
        else if (d < key.length() - 1) x->mid = put(x->mid, key, val, d + 1);
        else {
            x->val = val;
            x->isString = true;
        }
        return x;
    }

    // all keys in subtrie rooted at x with given prefix
    void collect(Node *x, string &prefix, queue<string> &queue) {
        if (x == nullptr) return;
        collect(x->left, prefix, queue);
        if (x->isString) {
            prefix.push_back(x->c);
            queue.push(prefix);
            prefix.pop_back();
        }
        prefix.push_back(x->c);
        collect(x->mid, prefix, queue);
        prefix.pop_back();
        collect(x->right, prefix, queue);
    }

    void collect(Node *x, string &prefix, int i, string &pattern, queue <string> &queue) {
        if (x == nullptr) return;
        char c = pattern[i];
        if (c == '.' || c < x->c) collect(x->left, prefix, i, pattern, queue);
        if (c == '.' || c == x->c) {
            if (i == pattern.length() - 1 && x->isString) {
                prefix.push_back(x->c);
                queue.push(prefix);
            }
            if (i < pattern.length() - 1) {
                prefix.push_back(x->c);
                collect(x->mid, prefix, i + 1, pattern, queue);
                prefix.pop_back();
            }
        }
        if (c == '.' || c > x->c) collect(x->right, prefix, i, pattern, queue);
    }


private:
    int n;       // size
    Node *root;  // root of TST
};

#endif //CH5_TST_H
