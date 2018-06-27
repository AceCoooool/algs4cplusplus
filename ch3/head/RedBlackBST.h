#ifndef CH3_REDBLACKBST_H
#define CH3_REDBLACKBST_H

#include <stdexcept>
#include <vector>

using std::runtime_error;
using std::vector;


/**
 *  The {@code BST} class represents an ordered symbol table of generic
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
 *  This implementation uses a left-leaning red-black BST. It requires that
 *  the key type implements the {@code Comparable} interface and calls the
 *  {@code compareTo()} and method to compare two keys. It does not call either
 *  {@code equals()} or {@code hashCode()}.
 *  The <em>put</em>, <em>contains</em>, <em>remove</em>, <em>minimum</em>,
 *  <em>maximum</em>, <em>ceiling</em>, and <em>floor</em> operations each take
 *  logarithmic time in the worst case, if the tree becomes unbalanced.
 *  The <em>size</em>, and <em>is-empty</em> operations take constant time.
 *  Construction takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/33balanced">Section 3.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For other implementations of the same API, see {@link ST}, {@link BinarySearchST},
 *  {@link SequentialSearchST}, {@link BST},
 *  {@link SeparateChainingHashST}, {@link LinearProbingHashST}, and {@link AVLTreeST}.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename Key, typename Value>
class RedBlackBST {
public:
    /**
     * Initializes an empty symbol table.
     */
    RedBlackBST() : root(nullptr) {}

    /**
     * Returns the number of key-value pairs in this symbol table.
     * @return the number of key-value pairs in this symbol table
     */
    int size() {
        return size(root);
    }

    /**
     * Is this symbol table empty?
     * @return {@code true} if this symbol table is empty and {@code false} otherwise
     */
    bool isEmpty() {
        return root == nullptr;
    }

    /***************************************************************************
    *  Standard BST search.
    ***************************************************************************/

    /**
     * Returns the value associated with the given key.
     * @param key the key
     * @return the value associated with the given key if the key is in the symbol table
     *     and {@code null} if the key is not in the symbol table
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Value get(Key key) {
        return get(root, key);
    }

    /**
     * Does this symbol table contain the given key?
     * @param key the key
     * @return {@code true} if this symbol table contains {@code key} and
     *     {@code false} otherwise
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    bool contains(Key key) {
        return contains(root, key);
    }

    /***************************************************************************
    *  Red-black tree insertion.
    ***************************************************************************/

    /**
     * Inserts the specified key-value pair into the symbol table, overwriting the old
     * value with the new value if the symbol table already contains the specified key.
     * Deletes the specified key (and its associated value) from this symbol table
     * if the specified value is {@code null}.
     *
     * @param key the key
     * @param val the value
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    void put(Key key, Value val) {
        root = put(root, key, val);
        root->color = BLACK;
    }

    /***************************************************************************
    *  Red-black tree deletion.
    ***************************************************************************/

    /**
     * Removes the smallest key and associated value from the symbol table.
     * @throws NoSuchElementException if the symbol table is empty
     */
    void deleteMin() {
        if (isEmpty()) throw runtime_error("BST underflow");

        // if both children of root are black, set root to red
        if (!isRed(root->left) && !isRed(root->right))
            root->color = RED;

        root = deleteMin(root);
        if (!isEmpty()) root->color = BLACK;
        // assert check();
    }

    /**
     * Removes the largest key and associated value from the symbol table.
     * @throws NoSuchElementException if the symbol table is empty
     */
    void deleteMax() {
        if (isEmpty()) throw runtime_error("BST underflow");

        // if both children of root are black, set root to red
        if (!isRed(root->left) && !isRed(root->right))
            root->color = RED;

        root = deleteMax(root);
        if (!isEmpty()) root->color = BLACK;
        // assert check();
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

        // if both children of root are black, set root to red
        if (!isRed(root->left) && !isRed(root->right))
            root->color = RED;

        root = delete_op(root, key);
        if (!isEmpty()) root->color = BLACK;
        // assert check();
    }

    /***************************************************************************
    *  Utility functions.
    ***************************************************************************/
    /**
     * Returns the height of the BST (for debugging).
     * @return the height of the BST (a 1-node tree has height 0)
     */
    int height() {
        return height(root);
    }

    /***************************************************************************
    *  Ordered symbol table methods.
    ***************************************************************************/
    /**
     * Returns the smallest key in the symbol table.
     * @return the smallest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key min() {
        if (isEmpty()) throw runtime_error("calls min() with empty symbol table");
        return min(root)->key;
    }

    /**
     * Returns the largest key in the symbol table.
     * @return the largest key in the symbol table
     * @throws NoSuchElementException if the symbol table is empty
     */
    Key max() {
        if (isEmpty()) throw runtime_error("calls max() with empty symbol table");
        return max(root)->key;
    }

    /**
     * Returns the largest key in the symbol table less than or equal to {@code key}.
     * @param key the key
     * @return the largest key in the symbol table less than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Key floor(Key key) {
        if (isEmpty()) throw runtime_error("calls floor() with empty symbol table");
        Node *x = floor(root, key);
        if (x == nullptr) throw runtime_error("illegal key");
        else return x->key;
    }

    /**
     * Returns the smallest key in the symbol table greater than or equal to {@code key}.
     * @param key the key
     * @return the smallest key in the symbol table greater than or equal to {@code key}
     * @throws NoSuchElementException if there is no such key
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    Key ceiling(Key key) {
        if (isEmpty()) throw runtime_error("calls ceiling() with empty symbol table");
        Node *x = ceiling(root, key);
        if (x == nullptr) throw runtime_error("illegal key");
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
     * @param key the key
     * @return the number of keys in the symbol table strictly less than {@code key}
     * @throws IllegalArgumentException if {@code key} is {@code null}
     */
    int rank(Key key) {
        return rank(key, root);
    }

    /***************************************************************************
    *  Range count and range search.
    ***************************************************************************/
    vector<Key> midOrder() {
        vector<Key> res;
        midOrder(root, res);
        return res;
    }

private:
    static bool RED;
    static bool BLACK;

    // BST helper node data type
    class Node {
    public:
        Key key;            // key
        Value val;          // associated data
        Node *left, *right; // links to left and right subtrees
        bool color;         // color of parent link
        int size;           // subtree count

        Node(Key key_, Value val_, bool color_, int size_) : key(key_), val(val_), color(color_), size(size_), left(
                nullptr), right(nullptr) {}
    };

private:
    /***************************************************************************
    *  Node helper methods.
    ***************************************************************************/
    // is node x red; false if x is null ?
    bool isRed(Node *x) {
        if (x == nullptr) return false;
        return x->color == RED;
    }

    // number of node in subtree rooted at x; 0 if x is null
    int size(Node *x) {
        if (x == nullptr) return 0;
        return x->size;
    }

    /***************************************************************************
    *  Standard BST search.
    ***************************************************************************/
    // value associated with the given key in subtree rooted at x; null if no such key
    Value get(Node *x, Key key) {
        while (x != nullptr) {
            if (key < x->key) x = x->left;
            else if (key > x->key) x = x->right;
            else return x->val;
        }
        throw runtime_error("can not find this key");
    }

    // Does this symbol table contain the given key?
    bool contains(Node *x, Key key) {
        while (x != nullptr) {
            if (key < x->key) x = x->left;
            else if (key > x->key) x = x->right;
            else return true;
        }
        return false;
    }

    /***************************************************************************
    *  Red-black tree insertion.
    ***************************************************************************/
    // insert the key-value pair in the subtree rooted at h
    Node *put(Node *h, Key key, Value val) {
        if (h == nullptr) return new Node(key, val, RED, 1);

        if (key < h->key) h->left = put(h->left, key, val);
        else if (key > h->key) h->right = put(h->right, key, val);
        else h->val = val;

        // fix-up any right-leaning links (p436)
        if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
        if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
        if (isRed(h->left) && isRed(h->right)) flipColors(h);
        h->size = size(h->left) + size(h->right) + 1;

        return h;
    }


private:
    /***************************************************************************
    *  Red-black tree helper functions.
    ***************************************************************************/
    // make a left-leaning link lean to the right (p434)
    Node *rotateRight(Node *h) {
        if (!isRed(h->left) || h == nullptr) throw runtime_error("illegal rotate right");
        Node *x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = x->right->color;
        x->right->color = RED;
        x->size = h->size;
        h->size = size(h->left) + size(h->right) + 1;
        return x;
    }

    // make a right-leaning link lean to the left (p434)
    Node *rotateLeft(Node *h) {
        if (h == nullptr || !isRed(h->right)) throw runtime_error("illegal rotate left");
        Node *x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = x->left->color;
        x->left->color = RED;
        x->size = h->size;
        h->size = size(h->left) + size(h->right) + 1;
        return x;
    }

    // flip the colors of a node and its two children (p436)
    void flipColors(Node *h) {
        // h must have opposite color of its two children
//        if (!((h != nullptr) && (h->left != nullptr) && (h->right != nullptr)))
//            throw runtime_error("illegal inputs");
//        if (!((!isRed(h) && isRed(h->left) && isRed(h->right)) || (isRed(h) && !isRed(h->left) && !isRed(h->right))))
//            throw runtime_error("illegal inputs");
        h->color = !h->color;
        h->left->color = !h->left->color;
        h->right->color = !h->right->color;
    }

    // TODO
    // Assuming that h is red and both h.left and h.left.left
    // are black, make h.left or one of its children red.
    Node *moveRedLeft(Node *h) {
//        if (h == nullptr) throw runtime_error("illegal input");
//        if (!(isRed(h) && !isRed(h->left) && !isRed(h->left->left)) throw runtime_error("illegal input");

        flipColors(h);
        if (isRed(h->right->left)) {
            h->right = rotateRight(h->right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    // Assuming that h is red and both h.right and h.right.left
    // are black, make h.right or one of its children red.
    Node *moveRedRight(Node *h) {
        // assert (h != null);
        // assert isRed(h) && !isRed(h.right) && !isRed(h.right.left);
        flipColors(h);
        if (isRed(h->left->left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    // restore red-black tree invariant
    Node *balance(Node *h) {
        // assert (h != null);

        if (isRed(h->right)) h = rotateLeft(h);
        if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
        if (isRed(h->left) && isRed(h->right)) flipColors(h);

        h->size = size(h->left) + size(h->right) + 1;
        return h;
    }

    /***************************************************************************
     *  Red-black tree deletion.
     ***************************************************************************/
    // delete the key-value pair with the minimum key rooted at h
    Node *deleteMin(Node *h) {
        if (h->left == nullptr)
            return nullptr;

        if (!isRed(h->left) && !isRed(h->left->left))
            h = moveRedLeft(h);

        h->left = deleteMin(h->left);
        return balance(h);
    }

    // delete the key-value pair with the maximum key rooted at h
    Node *deleteMax(Node *h) {
        if (isRed(h->left))
            h = rotateRight(h);

        if (h->right == nullptr)
            return nullptr;

        if (!isRed(h->right) && !isRed(h->right->left))
            h = moveRedRight(h);

        h->right = deleteMax(h->right);

        return balance(h);
    }

    // delete the key-value pair with the given key rooted at h
    Node *delete_op(Node *h, Key key) {
        // assert get(h, key) != null;

        if (key < h->key) {
            if (!isRed(h->left) && !isRed(h->left->left))
                h = moveRedLeft(h);
            h->left = delete_op(h->left, key);
        } else {
            if (isRed(h->left))
                h = rotateRight(h);
            if ((key == h->key) && (h->right == nullptr))
                return nullptr;
            if (!isRed(h->right) && !isRed(h->right->left))
                h = moveRedRight(h);
            if (key == h->key) {
                Node *x = min(h->right);
                h->key = x->key;
                h->val = x->val;
                // h.val = get(h.right, min(h.right).key);
                // h.key = min(h.right).key;
                h->right = deleteMin(h->right);
            } else h->right = delete_op(h->right, key);
        }
        return balance(h);
    }

    /***************************************************************************
    *  Utility functions.
    ***************************************************************************/
    // Returns the height of the BST (for debugging).
    int height(Node *x) {
        if (x == nullptr) return -1;
        return 1 + std::max(height(x->left), height(x->right));
    }

    /***************************************************************************
    *  Ordered symbol table methods.
    ***************************************************************************/
    // the smallest key in subtree rooted at x; null if no such key
    Node *min(Node *x) {
        // assert x != null;
        if (x->left == nullptr) return x;
        else return min(x->left);
    }

    // the largest key in the subtree rooted at x; null if no such key
    Node *max(Node *x) {
        // assert x != null;
        if (x->right == nullptr) return x;
        else return max(x->right);
    }

    // the largest key in the subtree rooted at x less than or equal to the given key
    Node *floor(Node *x, Key key) {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key < x->key) return floor(x->left, key);
        Node *t = floor(x->right, key);
        if (t != nullptr) return t;
        else return x;
    }

    // the smallest key in the subtree rooted at x greater than or equal to the given key
    Node *ceiling(Node *x, Key key) {
        if (x == nullptr) return nullptr;
        if (key == x->key) return x;
        if (key > x->key) return ceiling(x->right, key);
        Node *t = ceiling(x->left, key);
        if (t != nullptr) return t;
        else return x;
    }

    // the key of rank k in the subtree rooted at x
    Node *select(Node *x, int k) {
        // assert x != null;
        // assert k >= 0 && k < size(x);
        int t = size(x->left);
        if (t > k) return select(x->left, k);
        else if (t < k) return select(x->right, k - t - 1);
        else return x;
    }

    // number of keys less than key in the subtree rooted at x
    int rank(Key key, Node *x) {
        if (x == nullptr) return 0;
        if (key < x->key) return rank(key, x->left);
        else if (key > x->key) return 1 + size(x->left) + rank(key, x->right);
        else return size(x->left);
    }

    /***************************************************************************
    *  Range count and range search.
    ***************************************************************************/
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

private:
    Node *root;      // root of the BST
};

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::RED = true;
template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::BLACK = false;

#endif //CH3_REDBLACKBST_H
