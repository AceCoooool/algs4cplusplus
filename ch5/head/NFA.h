#ifndef CH5_NFA_H
#define CH5_NFA_H

#include <cassert>
#include "DirectedDFS.h"

using std::invalid_argument;

/**
 *  The {@code NFA} class provides a data type for creating a
 *  <em>nondeterministic finite state automaton</em> (NFA) from a regular
 *  expression and testing whether a given string is matched by that regular
 *  expression.
 *  It supports the following operations: <em>concatenation</em>,
 *  <em>closure</em>, <em>binary or</em>, and <em>parentheses</em>.
 *  It does not support <em>mutiway or</em>, <em>character classes</em>,
 *  <em>metacharacters</em> (either in the text or pattern),
 *  <em>capturing capabilities</em>, <em>greedy</em> or <em>relucantant</em>
 *  modifiers, and other features in industrial-strength implementations
 *  such as {@link java.util.regex.Pattern} and {@link java.util.regex.Matcher}.
 *  <p>
 *  This implementation builds the NFA using a digraph and a stack
 *  and simulates the NFA using digraph search (see the textbook for details).
 *  The constructor takes time proportional to <em>m</em>, where <em>m</em>
 *  is the number of characters in the regular expression.
 *  The <em>recognizes</em> method takes time proportional to <em>m n</em>,
 *  where <em>n</em> is the number of characters in the text.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/54regexp">Section 5.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class NFA {
public:
    /**
     * Initializes the NFA from the specified regular expression.
     *
     * @param  regexp the regular expression
     */
    NFA(string regexp) : regexp(regexp), m(regexp.length()) {
        stack<int> ops;
        graph = new Digraph(m + 1);
        for (int i = 0; i < m; i++) {
            int lp = i;
            if (regexp[i] == '(' || regexp[i] == '|')
                ops.push(i);
            else if (regexp[i] == ')') {
                int or_ = ops.top();
                ops.pop();

                // 2-way or operator
                if (regexp[or_] == '|') {
                    lp = ops.top();
                    ops.pop();
                    graph->addEdge(lp, or_ + 1);
                    graph->addEdge(or_, i);
                } else if (regexp[or_] == '(')
                    lp = or_;
                else
                    assert(false);
            }

            // closure operator (uses 1-character lookahead)
            if (i < m - 1 && regexp[i + 1] == '*') {
                graph->addEdge(lp, i + 1);
                graph->addEdge(i + 1, lp);
            }
            if (regexp[i] == '(' || regexp[i] == '*' || regexp[i] == ')')
                graph->addEdge(i, i + 1);
        }
        if (ops.size() != 0)
            throw invalid_argument("Invalid regular expression");
    }

    ~NFA() { delete (graph); }

    /**
     * Returns true if the text is matched by the regular expression.
     *
     * @param  txt the text
     * @return {@code true} if the text is matched by the regular expression,
     *         {@code false} otherwise
     */
    bool recognizes(string txt) {
        DirectedDFS *dfs = new DirectedDFS(*graph, 0);
        forward_list<int> pc;
        for (int v = 0; v < graph->getV(); v++)
            if (dfs->getmarked(v)) pc.push_front(v);

        // Compute possible NFA states for txt[i+1]
        for (int i = 0; i < txt.length(); i++) {
            if (txt[i] == '*' || txt[i] == '|' || txt[i] == '(' || txt[i] == ')')
                throw runtime_error("text contains the metacharacter '" + to_string(txt[i]) + "'");

            forward_list<int> match;
            for (int v : pc) {
                if (v == m) continue;
                if ((regexp[v] == txt[i]) || regexp[v] == '.')
                    match.push_front(v + 1);
            }
            auto tmp = dfs;
            vector<int> vtmp(match.begin(), match.end());
            dfs = new DirectedDFS(*graph, vtmp);
            delete (tmp);
            pc.clear();
            for (int v = 0; v < graph->getV(); v++)
                if (dfs->getmarked(v)) pc.push_front(v);

            // optimization if no states reachable
            if (distance(pc.begin(), pc.end()) == 0) return false;
        }

        // check for accept state
        for (int v : pc)
            if (v == m) return true;
        return false;
    }


private:
    Digraph *graph;   // digraph of epsilon transitions
    string regexp;   // regular expression
    int m;           // number of characters in regular expression
};

#endif //CH5_NFA_H
