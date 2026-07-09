#include <iostream>
#include <queue>
using namespace std;

int main(){

    // Create a max-heap priority queue (default)
    priority_queue<int> pq;

    pq.push(30);
    pq.push(10);
    pq.push(20);
    pq.push(40);

    cout << "Elements removed from priority queue in order:\n";

    while (!pq.empty()){
        cout << pq.top() << " ";
        pq.pop();
    }

     cout << "Size after one pop: " << pq.size() << endl;

    return 0;
}