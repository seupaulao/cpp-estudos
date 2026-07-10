#include <bits/stdc++.h>
using namespace std;

int main() {
    
    // Creating an empty multimap
    multimap<int, string> mm1;
    
    // Creating multimap using initializer list
    multimap<int, string> mm2 = {{1, "Geeks"},
                      {2, "For"}, {1, "C++"}};

    for (auto i : mm2)
        cout << i.first << ": " << i.second
        << endl;


    //inserindo    
    multimap<int, string> mm;
    
    // Inserting key-value pairs
    mm.insert({1, "Geeks"});
    mm.insert({2, "For"});
    mm.insert({1, "C++"});        

 // Accessing 1st element
    auto f = mm.begin();
    cout << f->first << ": " << f->second<< endl;
                     
    // Accessing 2nd element
    auto it = next(f, 1);
    cout << it->first << ": " << it->second;
    
    // Updating 2nd element value
    auto it = next(mm.begin(), 1);
    it->second = "Java";
    
    for (auto x: mm)
        cout << x.first << ": " << x.second<< endl;
        
    // Find element with key 2
    auto it = mm.find(2);
    
    cout << it->first << ": " << it->second;
    
    // Delete element using key
    mm.erase(2);
    
    // Delete element using iterator
    mm.erase(mm.find(1));

    for (auto x: mm)
        cout << x.first << ": " << x.second;
        
        
    return 0;
}