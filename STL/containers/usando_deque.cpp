#include <deque>
#include <iostream>
using namespace std;

int main()
{

    // Declare an empty deque of integers
    deque<int> d1;

    // Declare and initialize a deque with some values
    deque<int> d2 = {10, 20, 30, 40};
    for (int val : d2) {
        cout << val << " ";
    }
    cout << endl;

     deque<int> d;
    
    // Adding elements at the back
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    
    // Displaying elements
    cout << "Elements in deque (added using push_back): ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;

    // Adding elements at the front
    d.push_front(30);
    d.push_front(20);
    d.push_front(10);
    
    // Displaying elements
    cout << "Elements in deque (added using push_front): ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Original deque: ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;
    
    // Removing the last element
    d.pop_back();
    
    cout << "Deque after pop_back(): ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;

     cout << "Original deque: ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;
    
    // Removing the first element
    d.pop_front();
    
    cout << "Deque after pop_front(): ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;

    deque<int> deq = {100, 200, 300};
    
    // Accessing the front element
    cout << "The first element (front) is: " 
         << deq.front() << endl;

    cout << "The first element (front) is: " 
         << deq.front() << endl;

    // Accessing the last element
    cout << "The last element (back) is: " 
         << deq.back() << endl;

    cout << " The size of the deque is: " << deq.size() << endl;
    
    deque<int> de;
    if (de.empty()) {
        cout << "Deque is empty." << endl;
    } else {
        cout << "Deque is not empty." << endl;
    }
    
    // Add an element and check again
    de.push_back(100);

    if (de.empty()) {
        cout << "Deque is empty." << endl;
    } else {
        cout << "Deque is not empty." << endl;
    }

    deque<int> df = {1, 2, 3, 4, 5};
    cout << "Before clear(), size: " << df.size() << endl;
    
    // Clear all elements from deque
    df.clear();
    
    cout << "After clear(), size: " << df.size() << endl;

    if (df.empty()) {
        cout << "Deque is now empty." << endl;
    }

    return 0;
}