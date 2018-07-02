#include <iostream>
#include "../head/SymbolGraph.h"
#include "../head/BreadthFirstPaths.h"

using namespace std;

/**
 *  The {@code DegreesOfSeparation} class provides a client for finding
 *  the degree of separation between one distinguished individual and
 *  every other individual in a social network.
 *  As an example, if the social network consists of actors in which
 *  two actors are connected by a link if they appeared in the same movie,
 *  and Kevin Bacon is the distinguished individual, then the client
 *  computes the Kevin Bacon number of every actor in the network.
 *  <p>
 *  The running time is proportional to the number of individuals and
 *  connections in the network. If the connections are given implicitly,
 *  as in the movie network example (where every two actors are connected
 *  if they appear in the same movie), the efficiency of the algorithm
 *  is improved by allowing both movie and actor vertices and connecting
 *  each movie to all of the actors that appear in that movie.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/routes.txt";
    char delimiter = ' ';
    string source = "JFK";

    SymbolGraph sg(filename, delimiter);
    Graph *graph = sg.getgraph();
    if (!sg.contains(source)) {
        cout << source << " not in database" << endl;
        return -1;
    }

    int s = sg.indexOf(source);
    BreadthFirstPaths bfs(*graph, s);

    string sink;
    cout << "Input destination: (-1 means break)" << endl;
    while (cin >> sink) {
        if (sink == "-1")
            break;
        if (sg.contains(sink)) {
            int t = sg.indexOf(sink);
            if (bfs.hasPathTo(t)) {
                for (auto v: bfs.pathTo(t))
                    cout << " " << sg.nameOf(v) << endl;
            } else
                cout << "Not connected" << endl;
        } else
            cout << " Not in database" << endl;
    }
}