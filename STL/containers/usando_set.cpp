#include <iostream>
#include <set>
using namespace std;

int main() {

    // Creating an empty set
    set<int> s1;

    // Initialize set with list 
    set<int> s2 = {1, 2, 3, 2, 1}; 

    // Traversing the set
    for (auto& x : s2)
        cout << x << " ";
    cout << endl;

    // Initialize set with values
    set<int> s = {2, 3};

    // Inserting an element
    s.insert(1);

    // Traversing the set
    for (auto x : s)
        cout << x << endl;
        
    // Accessing elements using find()
    auto it = s.find(1);
    if (it != s.end())
        cout << "Element found: " << *it << endl;

    // Accessing elements using count()
    if (s.count(2))
        cout << "2 exists in the set" << endl;

    // Accessing all elements by traversal
    cout << "All elements: ";
    for (auto x : s)
        cout << x << " ";
    cout << endl;
    

    // Traversing using iterators
    for (auto it = s.begin(); it != s.end(); ++it)
        cout << *it << endl;  
        
    // Deleting by value
    s.erase(2);

    // Deleting by iterator
    s.erase(s.begin());

    // Traversing the set
    for (auto i : s)
        cout << i << " ";
    cout << endl;        

    return 0;
}