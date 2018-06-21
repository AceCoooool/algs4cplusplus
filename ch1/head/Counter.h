#ifndef CH1_COUNTER_H
#define CH1_COUNTER_H

#include <string>
#include <ostream>

using std::string;
using std::to_string;
using std::ostream;

/**
 *  The {@code Counter} class is a mutable data type to encapsulate a counter.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Counter {
public:
    /**
     * Initializes a new counter starting at 0, with the given id.
     * @param id the name of the counter
     */
    Counter(string id) : name(id) {}

    /**
     * Increments the counter by 1.
     */
    void increment() {
        count++;
    }

    /**
     * Returns the current value of this counter.
     *
     * @return the current value of this counter
     */
    int tally() {
        return count;
    }

    /**
     * Returns a string representation of this counter.
     *
     * @return a string representation of this counter
     */
    friend ostream &operator<<(ostream &stream, const Counter &item);

    /**
     * Compares this counter to the specified counter.
     *
     * @param  that the other counter
     * @return {@code 0} if the value of this counter equals
     *         the value of that counter; a negative integer if
     *         the value of this counter is less than the value of
     *         that counter; and a positive integer if the value
     *         of this counter is greater than the value of that
     *         counter
     */
    friend bool operator<(Counter &a1, Counter &a2);

private:
    const string name;
    int count = 0;
};

ostream &operator<<(ostream &stream, const Counter &item) {
    stream << item.count << " " << item.name;
}

bool operator<(Counter &a1, Counter &a2) {
    return a1.count < a2.count;
}

#endif //CH1_COUNTER_H
