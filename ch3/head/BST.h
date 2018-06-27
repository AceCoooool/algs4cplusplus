#ifndef CH3_BST_H
#define CH3_BST_H

// TODO: 1. change to smart pointer, 2. add iterator form
#include <stdexcept>
#include <vector>
#include <queue>
#include <iostream>

using std::runtime_error;
using std::queue;
using std::vector;

/**
 *  The {@code BST} class represents an ordered symbol table of generic
 *  key-value pairs.
 *  It supports the usual <em>put</em>, <em>get</em>, <em>contains</em>,
 *  <em>delete</em>, <em>size</em>, and <em>is-empty</em> methods.
 *  It also provides ordered methods for finding the <em>minimum</em>,
 *  <em>maximum</em>, <em>floor</em>, <em>select</em>, <em>ceiling</em>.
 *  It also provides a <em>keys</em> method for iterating over all of the keys.
 *  A symbol table implements the <em>associative array</em> abstraction:
 *  when associating a value with a key that is already in the symbol table,
 *  the convention is to replace the old value with the new value.
 *  Unlike {@link java.util.Map}, this class uses the convention that
 *  values cannot be {@code null}—setting the
 *  value associated with a key to {@code null} is equivalent to deleting the key
 *  from the symbol table.
 *  <p>
 *  This implementation uses an (unbalanced) binary search tree. It requires that
 *  the key type implements the {@code Comparable} interface and calls the
 *  {@code compareTo()} and method to compare two keys. It does not call either
 *  {@code equals()} or {@code hashCode()}.
 *  The <em>put</em>, <em>contains</em>, <em>remove</em>, <em>minimum</em>,
 *  <em>maximum</em>, <em>ceiling</em>, <em>floor</em>, <em>select</em>, and
 *  <em>rank</em>  operations each take
 *  linear time in the worst case, if the tree becomes unbalanced.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/32bst">Section 3.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For other implementations, see {@link ST}, {@link BinarySearchST},
 *  {@link SequentialSearchST}, {@link RedBlackBST},
 *  {@link SeparateChainingHashST}, and {@link LinearProbingHashST},
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename Key, typename Value>
class BST {
public:
    /**
     * Initializes an empty symbol table.
     */
    BST() : root(nullptr) {}

    /**
     * Returns true if this symbol table is empty.
     * @return {@code true} if this symbol table is empty; {@code false} otherwise
     */
    bool isEmpty() {
        return size() == 0;
    }

    /**
     * Returns the number of key-value pairs in this symbol table.
     * @return the number of key-value pairs in this symbol table
     */
    int size() {
        return size(root);
    }

    /**
     * Does this symbol table contain the given key?
     *
     * @param  key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *         {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(Key key) {
        return contains(root, key);
    }

    /**
     * Returns the value associated with the given key.
     *
     * @param  key the key
     * @return the value associated with the given key if the key is in the symbol table
     *         and {@code null} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Value get(Key key) {
        return get(root, key);
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
        root = put(root, key, val);
    }

    /**
     * Removes the smallest key and associated value from the symbol table.
     *
     * @throws NoSuchElementException if the symbol table is empty
     */
    void deleteMin() {
        if (isEmpty()) throw runtime_error("Symbol table underflow");
        root = deleteMin(root);
    }

    /**
     * Removes the largest key and associated value from the symbol table.
     *
     * @throws NoSuchElementException if the symbol table is empty
     */
    void deleteMax() {
        if (isEmpty()) throw runtime_error("Symbol table underflow");
        root = deleteMax(root);
    }

    /**
     * Removes the specified key and its associated value from this symbol table
     * (if the key is in this symbol table).
     *
     * @param  key the key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void delete_op(Key key) {
        root = delete_op(root, key);
    }

    /**
     * Returns the smallest key in the symbol table.
     *
     * @return the smallest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key min() {
        if (isEmpty()) throw runtime_error("calls min() with empty symbol table");
        return min(root)->key;
    }

    /**
     * Returns the largest key in the symbol table.
     *
     * @return the largest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key max() {
        if (isEmpty()) throw runtime_error("calls max() with empty symbol table");
        return max(root)->key;
    }

    /**
     * Returns the largest key in the symbol table less than or equal to {@code key}.
     *
     * @param  key the key
     * @return the largest key in the symbol table less than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Key floor(Key key) {
        if (isEmpty()) throw runtime_error("calls floor() with empty symbol table");
        Node *x = floor(root, key);
        if (x == nullptr) throw runtime_error("this key out of range!");
        else return x->key;
    }

    /**
     * Returns the smallest key in the symbol table greater than or equal to {@code key}.
     *
     * @param  key the key
     * @return the smallest key in the symbol table greater than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Key ceiling(Key key) {
        if (isEmpty()) throw runtime_error("calls ceiling() with empty symbol table");
        Node *x = ceiling(root, key);
        if (x == nullptr) throw runtime_error("this key out of range!");
        else return x->key;
    }

    /**
     * Return the key in the symbol table whose rank is {@code k}.
     * This is the (k+1)st smallest key in the symbol table.
     *
     * @param  k the order statistic
     * @return the key in the symbol table of rank {@code k}
     * @throws IllegalArgumentException unless {@code k} is between 0 and
     *        <em>n</em>–1
     */
    Key select(int k) {
        if (k < 0 || k >= size()) {
            throw runtime_error("argument to select() is invalid: " + k);
        }
        Node *x = select(root, k);
        return x->key;
    }

    /**
     * Return the number of keys in the symbol table strictly less than {@code key}.
     *
     * @param  key the key
     * @return the number of keys in the symbol table strictly less than {@code key}
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    int rank(Key key) {
        return rank(key, root);
    }

    /**
     * Returns the number of keys in the symbol table in the given range.
     *
     * @param  lo minimum endpoint
     * @param  hi maximum endpoint
     * @return the number of keys in the symbol table between {@code lo}
     *         (inclusive) and {@code hi} (inclusive)
     * @throws IllegalArgumentException if either {@code lo} or {@code hi}
     *         is {@code null}
     */
    int size(Key lo, Key hi) {
        if (lo > hi) return 0;
        if (contains(hi)) return rank(hi) - rank(lo) + 1;
        else return rank(hi) - rank(lo);
    }

    /**
     * Returns the height of the BST (for debugging).
     *
     * @return the height of the BST (a 1-node tree has height 0)
     */
    int height() {
        return height(root);
    }

    /**
     * Returns all keys in the symbol table as an {@code Iterable}.
     * To iterate over all of the keys in the symbol table named {@code st},
     * use the foreach notation: {@code for (Key key : st.keys())}.
     *
     * @return all keys in the symbol table
     */
    void printKey() {
        queue<Key> q;
        Key lo = min(root), hi = max(root);
        printKey(root, q, lo, min);
    }

    vector<Key> midOrder() {
        vector<Key> res;
        midOrder(root, res);
        return res;
    }

    vector<Key> levelOrder() {
        vector<Key> res;
        levelOrder(root, res);
        return res;
    }

private:
    class Node {
    public:
        Key key;           // sorted by key
        Value val;         // associated data
        Node *left, *right;   // left and right subtrees
        int size;             // number of nodes in subtree
        Node(Key key, Value val, int size) : key(key), val(val), size(size), left(nullptr), right(nullptr) {}
    };

private:
    // return number of key-value pairs in BST rooted at x
    int size(Node *x) {
        if (x == nullptr) return 0;
        else return x->size;
    }

    // Returns the value associated with the given key.
    Value get(Node *x, Key key) {
        if (x == nullptr) throw runtime_error("this key is not in the tree!");
        if (key < x->key) return get(x->left, key);
        else if (key > x->key) return get(x->right, key);
        else return x->val;
    }

    // Does this symbol table contain the given key?
    bool contains(Node *x, Key key) {
        if (x == nullptr) return false;
        if (key < x->key) return get(x->left, key);
        else if (key > x->key) return get(x->right, key);
        else return true;
    }

    //Inserts the specified key-value pair into the symbol table, overwriting the old ,
    // value with the new value if the symbol table already contains the specified key.
    Node *put(Node *x, Key key, Value val) {
        if (x == nullptr) return new Node(key, val, 1);
        if (key < x->key) x->left = put(x->left, key, val);
        else if (key > x->key) x->right = put(x->right, key, val);
        else x->val = val;
        x->size = 1 + size(x->left) + size(x->right);
        return x;
    }

    // Removes the smallest key and associated value from the symbol table.
    Node *deleteMin(Node *x) {
        if (x->left == nullptr) {
            Node *tmp = x->right;
            delete (x);
            return tmp;
        }
        x->left = deleteMin(x->left);
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }

    // Removes the largest key and associated value from the symbol table.
    Node *deleteMax(Node *x) {
        if (x->right == nullptr) {
            Node *tmp = x->left;
            delete (x);
            return tmp;
        }
        x->right = deleteMax(x->right);
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }

    // Removes the specified key and its associated value from this symbol table (if the key is in this symbol table).
    Node *delete_op(Node *x, Key key) {
        if (x == nullptr) return nullptr;

        if (key < x->key) x->left = delete_op(x->left, key);
        else if (key > x->key) x->right = delete_op(x->right, key);
        else {
            if (x->right == nullptr) {  // simple way
                auto tmp = x->left;
                delete (x);
                return tmp;
            }
            if (x->left == nullptr) {
                auto tmp = x->right;
                delete (x);
                return tmp;
            }
            Node *tmp = x;
            x = min(tmp->right);
            x->right = deleteMin(tmp->right);
            x->left = tmp->left;
            delete (tmp);
        }
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }

    // Returns the smallest key in the symbol table.
    Node *min(Node *x) {
        if (x->left == nullptr) return x;
        else return min(x->left);
    }

    // Returns the largest key in the symbol table.
    Node *max(Node *x) {
        if (x->right == nullptr) return x;
        else return max(x->right);
    }

    // returns the largest key in the symbol table less than or equal to {@code key}.
    Node *floor(Node *x, Key key) {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key < x->key) return floor(x->left, key);
        Node *t = floor(x->right, key);
        if (t != nullptr) return t;
        else return x;
    }

    // Returns the smallest key in the symbol table greater than or equal to {@code key}.
    Node *ceiling(Node *x, Key key) {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key < x->key) {
            Node *t = ceiling(x->left, key);
            if (t != nullptr) return t;
            else return x;
        }
        return ceiling(x->right, key);
    }

    // Return key of rank k.
    Node *select(Node *x, int k) {
        if (x == nullptr) return nullptr;
        int t = size(x->left);
        if (t > k) return select(x->left, k);
        else if (t < k) return select(x->right, k - t - 1);
        else return x;
    }

    // Number of keys in the subtree less than key.
    int rank(Key key, Node *x) {
        if (x == nullptr) return 0;
        if (key < x->key) return rank(key, x->left);
        else if (key > x->key) return 1 + size(x->left) + rank(key, x->right);
        else return size(x->left);
    }

    // Returns the height of the BST (for debugging).
    int height(Node *x) {
        if (x == nullptr) return -1;
        return 1 + std::max(height(x->left), height(x->right));
    }

    // return all keys in the symbol table
    void printKey(Node *x, queue<Key> &q, Key lo, Key hi) {
        if (x == nullptr) return;
        if (lo < x->key) printKey(x->left, q, lo, hi);
        if (lo <= x->key && hi >= x->key) q.push(x->key);
        if (hi > x->key) printKey(x->right, q, lo, hi);
    }

    void midOrder(Node *x, vector<Key> &res) {
        if (x == nullptr) return;
        if (x->left == nullptr && x->right == nullptr) {
            res.push_back(x->key);
            return;
        }
        if (x->left) midOrder(x->left, res);
        res.push_back(x->key);
        if (x->right) midOrder(x->right, res);
    }

    void levelOrder(Node *x, vector<Key> &res) {
        if (x == nullptr) return;
        queue<Node *> q;
        q.push(x);
        while (!q.empty()) {
            int s = q.size();
            for (int i = 0; i < s; ++i) {
                auto tmp = q.front();
                res.push_back(tmp->key);
                q.pop();
                if(tmp->left) q.push(tmp->left);
                if(tmp->right) q.push(tmp->right);
            }
        }
    }

private:
    Node *root;
};

#endif //CH3_BST_H
