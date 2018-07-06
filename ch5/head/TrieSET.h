#ifndef CH5_TRIESET_H
#define CH5_TRIESET_H

#include <vector>
#include <string>
#include <queue>
#include <stdexcept>

using std::invalid_argument;
using std::vector;
using std::string;
using std::queue;

/**
 *  The {@code TrieSET} class represents an ordered set of strings over
 *  the extended ASCII alphabet.
 *  It supports the usual <em>add</em>, <em>contains</em>, and <em>delete</em>
 *  methods. It also provides character-based methods for finding the string
 *  in the set that is the <em>longest prefix</em> of a given prefix,
 *  finding all strings in the set that <em>start with</em> a given prefix,
 *  and finding all strings in the set that <em>match</em> a given pattern.
 *  <p>
 *  This implementation uses a 256-way trie.
 *  The <em>add</em>, <em>contains</em>, <em>delete</em>, and
 *  <em>longest prefix</em> methods take time proportional to the length
 *  of the key (in the worst case). Construction takes constant time.
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/52trie">Section 5.2</a> of
 *  <i>Algorithms in Java, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class TrieSET {
private:
    class Node {
    public:
        Node() : next(R, nullptr), isString(false) {}

        ~Node() {
            for (int i = 0; i < R; ++i)
                if (next[i]) delete (next[i]);
        }

        vector<Node *> next;
        bool isString;
    };

public:
    /**
     * Initializes an empty set of strings.
     */
    TrieSET() : root(nullptr), n(0) {}

    ~TrieSET() { delete (root); }

    /**
     * Does the set contain the given key?
     * @param key the key
     * @return {@code true} if the set contains {@code key} and
     *     {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(string key) {
        if (key.empty()) throw invalid_argument("argument to contains() is null");
        Node *x = get(root, key, 0);
        if (x == nullptr) return false;
        return x->isString;
    }

    /**
     * Adds the key to the set if it is not already present.
     * @param key the key to add
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void add(string key) {
        if (key.empty()) throw invalid_argument("argument to add() is null");
        root = add(root, key, 0);
    }

    /**
     * Returns the number of strings in the set.
     * @return the number of strings in the set
     */
    int size() {
        return n;
    }

    /**
     * Is the set empty?
     * @return {@code true} if the set is empty, and {@code false} otherwise
     */
    bool isEmpty() {
        return size() == 0;
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
     * Returns all of the keys in the set that match {@code pattern},
     * where . symbol is treated as a wildcard character.
     * @param pattern the pattern
     * @return all of the keys in the set that match {@code pattern},
     *     as an iterable, where . is treated as a wildcard character.
     */
    queue<string> keysThatMatch(string pattern) {
        queue<string> results;
        collect(root, "", pattern, results);
        return results;
    }

    /**
     * Returns the string in the set that is the longest prefix of {@code query},
     * or {@code null}, if no such string.
     * @param query the query string
     * @return the string in the set that is the longest prefix of {@code query},
     *     or {@code null} if no such string
     * @throws IllegalArgumentException if {@code query} is {@code null}
     */
    string longestPrefixOf(string query) {
        if (query.empty()) throw invalid_argument("argument to longestPrefixOf() is null");
        int length = longestPrefixOf(root, query, 0, -1);
        if (length == -1) return "";
        return query.substr(0, length);
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

    /**
     * Returns all of the keys in the set, as an iterator.
     * To iterate over all of the keys in a set named {@code set}, use the
     * foreach notation: {@code for (Key key : set)}.
     * @return an iterator to all of the keys in the set
     */
    queue<string> keys() {
        return keysWithPrefix("");
    }

private:
    Node *get(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) return x;
        char c = key[d];
        return get(x->next[c], key, d + 1);
    }

    Node *add(Node *x, string key, int d) {
        if (x == nullptr) x = new Node();
        if (d == key.length()) {
            if (!x->isString) n++;
            x->isString = true;
        } else {
            char c = key[d];
            x->next[c] = add(x->next[c], key, d + 1);
        }
        return x;
    }

    void collect(Node *x, string prefix, queue<string> &results) {
        if (x == nullptr) return;
        if (x->isString) results.push(prefix);
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
        if (d == pattern.length() && x->isString)
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
    // found a prefix match of length length
    int longestPrefixOf(Node *x, string query, int d, int length) {
        if (x == nullptr) return length;
        if (x->isString) length = d;
        if (d == query.length()) return length;
        char c = query[d];
        return longestPrefixOf(x->next[c], query, d + 1, length);
    }

    // TODO: bug of memory leaky
    Node *delete_(Node *x, string key, int d) {
        if (x == nullptr) return nullptr;
        if (d == key.length()) {
            if (x->isString) n--;
            x->isString = false;
        } else {
            char c = key[d];
            x->next[c] = delete_(x->next[c], key, d + 1);
        }

        // remove subtrie rooted at x if it is completely empty
        if (x->isString) return x;
        for (int c = 0;; c++) {
            if (x->next[c] != nullptr)
                return x;
            if (c == R - 1) break;
        }
        return nullptr;
    }

private:
    Node *root;  // root of trie
    int n;       // number of keys in trie
    static const int R;
};

const int TrieSET::R = 256;

#endif //CH5_TRIESET_H
