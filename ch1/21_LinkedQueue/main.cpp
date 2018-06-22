#include <iostream>
#include <fstream>
#include "../head/LinkedQueue.h"

#include <memory>

using namespace std;


int main() {
//    unique_ptr<int> p(nullptr);
//    cout << (p == nullptr) << endl;
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/tobe.txt");
    LinkedQueue<string> queue;
    string tmp;
    while (file >> tmp) {
        if (tmp != "-") queue.enqueue(tmp);
        else if (!queue.isEmpty()) cout << queue.dequeue() << " ";
    }
    cout << "(" << queue.size() << " left on queue)" << endl;
}