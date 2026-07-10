#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
  
    // Creating an unordered_set of integers
    unordered_set<int> us = {1, 2, 3, 4, 5};

    for (auto x : us) 
        cout << x << " ";

    // Empty unordered set 
    unordered_set<int> us1; 
    
    // Initialize using an initializer list 
    unordered_set<int> us2 = {10, 20, 30, 40}; 
    
    // Initialize from a vector 
    vector<int> v = {1, 2, 3, 4, 5}; 
    unordered_set<int> us3(v.begin(), v.end()); 
    
    cout << "Size of us2: " << us2.size() << endl; 
    cout << "Size of us3: " << us3.size() << endl; 
    
    unordered_set<int> us5;

    us5.insert(3);
    us5.insert(1);
    us5.insert(2);

    for (auto x : us5)
        cout << x << " ";

    // Accessing third element
    auto it = next(us5.begin(), 2);
    cout << *it;        
        
    // Replace 2 with 10
    us5.erase(2);
    us5.insert(10);    

    auto it = us5.find(4);
    if (it != us5.end())
        cout << *it;
    else
        cout << "Element not Found!";

    // Delete element by value
    us5.erase(5);
    // Delete element by position
    us5.erase(us5.begin());
    for (auto x : us5)
        cout << x << " ";        
        
    return 0;
}