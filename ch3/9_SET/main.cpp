#include <iostream>
#include <fstream>
#include "../head/SET.h"

using namespace std;

int main() {
    SET<string> strset;
    cout << "set = " << strset << endl;
    cout << endl;
    // insert some keys
    strset.add("www.cs.princeton.edu");
    strset.add("www.cs.princeton.edu");    // overwrite old value
    strset.add("www.princeton.edu");
    strset.add("www.math.princeton.edu");
    strset.add("www.yale.edu");
    strset.add("www.amazon.com");
    strset.add("www.simpsons.com");
    strset.add("www.stanford.edu");
    strset.add("www.google.com");
    strset.add("www.ibm.com");
    strset.add("www.apple.com");
    strset.add("www.slashdot.com");
    strset.add("www.whitehouse.gov");
    strset.add("www.espn.com");
    strset.add("www.snopes.com");
    strset.add("www.movies.com");
    strset.add("www.cnn.com");
    strset.add("www.iitb.ac.in");

    cout << "contains (www.cs.princeton.edu): " << strset.contains("www.cs.princeton.edu") << endl;
    cout << "not contains (www.harvardsucks.com): " << !strset.contains("www.harvardsucks.com") << endl;
    cout << "contains (www.simpsons.com): " << strset.contains("www.simpsons.com") << endl;
    cout << endl;

    cout << "ceiling(www.simpsonr.com) = " << strset.ceiling("www.simpsonr.com") << endl;
    cout << "ceiling(www.simpsons.com) = " << strset.ceiling("www.simpsons.com") << endl;
    cout << "ceiling(www.simpsont.com) = " << strset.ceiling("www.simpsont.com") << endl;
    cout << "floor(www.simpsonr.com)   = " << strset.floor("www.simpsonr.com") << endl;
    cout << "floor(www.simpsons.com)   = " << strset.floor("www.simpsons.com") << endl;
    cout << "floor(www.simpsont.com)   = " << strset.floor("www.simpsont.com") << endl;
    cout << endl;

    cout << "set = " << strset << endl;
    cout << endl;

    for (auto k: strset)
        cout << k << endl;
}