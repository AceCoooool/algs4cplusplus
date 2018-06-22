#ifndef CH1_TRANSACTION_H
#define CH1_TRANSACTION_H

// TODO: may need write delete ?
#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include "../head/Date.h"

using std::vector;
using std::string;
using std::stod;
using std::isnan;
using std::isinf;
using std::unique_ptr;
using std::make_unique;

/**
 *  The {@code Transaction} class is an immutable data type to encapsulate a
 *  commercial transaction with a customer name, date, and amount.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Transaction {
public:
    /**
     * Initializes a new transaction from the given arguments.
     *
     * @param  who the person involved in this transaction
     * @param  when the date of this transaction
     * @param  amount the amount of this transaction
     * @throws IllegalArgumentException if {@code amount}
     *         is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY},
     *         or {@code Double.NEGATIVE_INFINITY}
     */
    Transaction(string who_, Date when_, double amount_) : who(who_), when(make_unique<Date>(when_)),
                                                           amount(amount_) {
        if (isnan(amount) || isinf(amount))
            throw runtime_error("Amount cannot be Nan or infinite");
    }

    /**
     * Initializes a new transaction by parsing a string of the form NAME DATE AMOUNT.
     *
     * @param  transaction the string to parse
     * @throws IllegalArgumentException if {@code amount}
     *         is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY},
     *         or {@code Double.NEGATIVE_INFINITY}
     */
    // TODO: change to regex split
    Transaction(string transaction) {
        vector<string> a = split(transaction, ' ');
        who = a[0];
        when = make_unique<Date>(a[1]);
        amount = stod(a[2]);
        if (isnan(amount) || isinf(amount))
            throw runtime_error("Amount cannot be Nan or infinite");
    }

    /**
     * Returns the name of the customer involved in this transaction.
     *
     * @return the name of the customer involved in this transaction
     */
    string getwho() {
        return who;
    }

    /**
     * Returns the date of this transaction.
     *
     * @return the date of this transaction
     */
    // TODO: modify to a more elegant form
    unique_ptr<Date> getwhen() {
        return make_unique<Date>(when->month(), when->day(), when->year());
    }

    /**
     * Returns the amount of this transaction.
     *
     * @return the amount of this transaction
     */
    double getamount() {
        return amount;
    }

    /**
     * Returns a string representation of this transaction.
     *
     * @return a string representation of this transaction
     */
    friend ostream &operator<<(ostream &stream, const Transaction &trans);

    /**
     * Compares this transaction to the specified object.
     *
     * @param  other the other transaction
     * @return true if this transaction is equal to {@code other}; false otherwise
     */
    friend bool operator==(const Transaction &trans1, const Transaction &trans2);

    /**
     * Compares two transactions by date.
     */
    static bool WhenOrder(Transaction &v, Transaction &w);

    /**
     * Compares two transactions by customer name.
     */
    static bool WhoOrder(Transaction &v, Transaction &w);

    /**
     * Compares two transactions by amount.
     */
    static bool HowMuchOrder(Transaction &v, Transaction &w);

private:
    string who;
    unique_ptr<Date> when;
    double amount;
};


ostream &operator<<(ostream &stream, const Transaction &trans) {
    stream << trans.who << " " << *trans.when << " " << trans.amount;
}

bool operator==(const Transaction &trans1, const Transaction &trans2) {
    return trans1.amount == trans2.amount && trans1.who == trans2.who && trans1.when == trans2.when;
}

bool Transaction::WhenOrder(Transaction &v, Transaction &w) {
    return *(v.when) < *(w.when);
}

bool Transaction::WhoOrder(Transaction &v, Transaction &w) {
    return v.who < w.who;
}

bool Transaction::HowMuchOrder(Transaction &v, Transaction &w) {
    return v.amount < w.amount;
}


#endif //CH1_TRANSACTION_H
