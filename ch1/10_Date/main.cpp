#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

auto split = [](string s, char delim) {
    vector<string> tokens;
    stringstream ss(s);
    string tmp;
    while (getline(ss, tmp, delim))
        tokens.push_back(tmp);
    return tokens;
};

class Date {
public:
    /**
     * Initializes a new date from the month, day, and year.
     * @param month the month (between 1 and 12)
     * @param day the day (between 1 and 28-31, depending on the month)
     * @param year the year
     * @throws IllegalArgumentException if this date is invalid
     */
    Date(int m, int d, int y) : month_(m), day_(d), year_(y) {
        if (!isValid(month_, day_, year_))
            throw runtime_error("Invalid date");
    }

    /**
     * Initializes new date specified as a string in form MM/DD/YYYY.
     * @param date the string representation of this date
     * @throws IllegalArgumentException if this date is invalid
     */
    Date(string date) {
        vector<string> fields = split(date, '/');
        if (fields.size() != 3)
            throw runtime_error("Invalid data");
        month_ = stoi(fields[0]);
        day_ = stoi(fields[1]);
        year_ = stoi(fields[2]);
        if (!isValid(month_, day_, year_))
            throw runtime_error("Invalid data");
    }

    /**
     * Return the month.
     * @return the month (an integer between 1 and 12)
     */
    int month() {
        return month_;
    }

    /**
     * Returns the day.
     * @return the day (an integer between 1 and 31)
     */
    int day() {
        return day_;
    }

    /**
     * Returns the year.
     * @return the year
     */
    int year() {
        return year_;
    }

    /**
     * Returns the next date in the calendar.
     *
     * @return a date that represents the next day after this day
     */
    Date next() {
        if (isValid(month_, day_ + 1, year_)) return Date(month_, day_ + 1, year_);
        else if (isValid(month_ + 1, 1, year_)) return Date(month_ + 1, 1, year_);
        else return Date(1, 1, year_ + 1);
    }

    /**
     * Compares two dates chronologically.
     *
     * @param  that the other date
     * @return {@code true} if this date is after that date; {@code false} otherwise
     */
    bool isAfter(Date &that) {
        return compareTo(that) > 0;
    }

    /**
     * Compares two dates chronologically.
     *
     * @param  that the other date
     * @return {@code true} if this date is before that date; {@code false} otherwise
     */
    bool isBefore(Date that) {
        return compareTo(that) < 0;
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

    /**
    * Compares two dates chronologically.
    *
    * @return the value {@code 0} if the argument date is equal to this date;
    *         a negative integer if this date is chronologically less than
    *         the argument date; and a positive ineger if this date is chronologically
    *         after the argument date
    */
    int compareTo(Date &that) {
        if (year_ < that.year_) return -1;
        if (year_ > that.year_) return +1;
        if (month_ < that.month_) return -1;
        if (month_ > that.month_) return +1;
        if (day_ < that.day_) return -1;
        if (day_ > that.day_) return +1;
        return 0;
    }

private:
    const static vector<int> DAYS;
    int month_;   // month (between 1 and 12)
    int day_;     // day   (between 1 and DAYS[month]
    int year_;    // year
};

const vector<int> Date::DAYS = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    auto v = split("10/20/30", '/');
    for (auto a: v)
        cout << a << " ";
    cout << endl;
}