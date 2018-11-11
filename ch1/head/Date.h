#ifndef CH1_DATE_H
#define CH1_DATE_H

#include <stdexcept>
#include <vector>
#include <ostream>
#include <sstream>
#include <string>

using std::runtime_error;
using std::string;
using std::vector;
using std::ostream;
using std::stringstream;
using std::getline;


auto split = [](string s, char delim) {
    vector<string> tokens;
    stringstream ss(s);
    string tmp;
    while (getline(ss, tmp, delim))
        tokens.push_back(tmp);
    return tokens;
};

/**
 *  The {@code Date} class is an immutable data type to encapsulate a
 *  date (day, month, and year).
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Date {
private:
    const static vector<int> DAYS;
    int month;   // month (between 1 and 12)
    int day;     // day   (between 1 and DAYS[month]
    int year;    // year

public:
    // some friend function
    friend ostream &operator<<(ostream &stream, const Date &item);
    friend bool operator==(const Date &d1, const Date &d2);
    friend bool operator<(const Date &d1, const Date &d2);
    friend bool operator>(const Date &d1, const Date &d2);

public:
    /**
     * Initializes a new date from the month, day, and year.
     * @param month the month (between 1 and 12)
     * @param day the day (between 1 and 28-31, depending on the month)
     * @param year the year
     * @throws IllegalArgumentException if this date is invalid
     */
    Date(int m, int d, int y) : month(m), day(d), year(y) {
        if (!isValid(month, day, year))
            throw runtime_error("Invalid date");
    }

    /**
     * Initializes new date specified as a string in form MM/DD/YYYY.
     * @param date the string representation of this date
     * @throws IllegalArgumentException if this date is invalid
     */
    explicit Date(string date) {
        vector<string> fields = split(date, '/');
        if (fields.size() != 3)
            throw runtime_error("Invalid data");
        month = stoi(fields[0]);
        day = stoi(fields[1]);
        year = stoi(fields[2]);
        if (!isValid(month, day, year))
            throw runtime_error("Invalid data");
    }

    Date(const Date &date) : month(date.month), year(date.year), day(date.day) {}

    /**
     * Return the month.
     * @return the month (an integer between 1 and 12)
     */
    int month_() const noexcept {
        return month;
    }

    /**
     * Returns the day.
     * @return the day (an integer between 1 and 31)
     */
    int day_() const noexcept {
        return day;
    }

    /**
     * Returns the year.
     * @return the year
     */
    int year_() const noexcept {
        return year;
    }

    /**
     * Returns the next date in the calendar.
     *
     * @return a date that represents the next day after this day
     */
    Date next() {
        if (isValid(month, day + 1, year)) return Date(month, day + 1, year);
        else if (isValid(month + 1, 1, year)) return Date(month + 1, 1, year);
        else return Date(1, 1, year + 1);
    }


    /**
     * Compares two dates chronologically.
     *
     * @param  that the other date
     * @return {@code true} if this date is after that date; {@code false} otherwise
     */
    bool isAfter(const Date &that) const {
        return (*this) > that;
    }

    /**
     * Compares two dates chronologically.
     *
     * @param  that the other date
     * @return {@code true} if this date is before that date; {@code false} otherwise
     */
    bool isBefore(const Date &that) const {
        return (*this) < that;
    }


private:
    // is the given date valid?
    static bool isValid(int m, int d, int y) {
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > DAYS[m]) return false;
        if (m == 2 && d == 29 && !isLeapYear(y)) return false;
        return true;
    }

    // is y a leap year?
    static bool isLeapYear(int y) {
        if (y % 400 == 0) return true;
        if (y % 100 == 0) return false;
        return y % 4 == 0;
    }

};

const vector<int> Date::DAYS = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
 * Returns a string representation of this date.
 *
 * @return the string representation in the format MM/DD/YYYY
 */
ostream &operator<<(ostream &stream, const Date &item) {
    stream << item.month << "/" << item.day << "/" << item.year;
}

/**
 * Compares this date to the specified date.
 *
 * @param  other the other date
 * @return {@code true} if this date equals {@code other}; {@code false} otherwise
 */
bool operator==(const Date &d1, const Date &d2) {
    return (d1.month == d2.month) && (d1.day == d2.day) && (d1.year == d2.year);
}

/**
 * Compares two dates chronologically.
 *
 * @return the value {@code 0} if the argument date is equal to this date;
 *         a negative integer if this date is chronologically less than
 *         the argument date; and a positive ineger if this date is chronologically
 *         after the argument date
 */
bool operator<(const Date &d1, const Date &d2) {
    if (d1.year < d2.year) return true;
    if (d1.year > d2.year) return false;
    if (d1.month < d2.month) return true;
    if (d1.month > d2.month) return false;
    if (d1.day < d2.day) return true;
    if (d1.day > d2.day) return false;
    return false;
}

bool operator>(const Date &d1, const Date &d2) {
    if (d1.year > d2.year) return true;
    if (d1.year < d2.year) return false;
    if (d1.month > d2.month) return true;
    if (d1.month < d2.month) return false;
    if (d1.day > d2.day) return true;
    if (d1.day < d2.day) return false;
    return false;
}

#endif //CH1_DATE_H
