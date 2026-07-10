#include <iostream>
#include <map>
using namespace std;

int main() {
    
    // Creating an empty map
    map<int, string> m1;

    // Initialize map with list
    map<int, string> m2 = {{1, "Geeks"},
              {2, "For"}, {3, "Geeks"}};

    for (auto& p : m2)
        cout << p.first << " " <<
        p.second << endl;

    map<int, string> m = {{2, "For"}, {3, "Geeks"}};
    // Inserting a key value pair
    m.insert({1, "Geeks"});

     // Accessing elements
    cout << m[1] << endl;
    cout << m.at(2);

 // Updating value
    m[0] = "Tweaks";
    m.at(1) = "By";
    
    cout << m[0] << endl;
    cout << m.at(1);
    
 // Finding element with key 2
    auto it = m.find(2);
    
    if (it != m.end())
        cout << it->first << " " << it->second;
    else cout << "Key not Found!";
    
    // Traversing using iterators
    for (auto it = m.begin(); it != m.end(); ++it) 
        cout << it->first << " " << it->second
        << endl;
        
    // Deleting by key
    m.erase(2);
    
    // Deleting by iterator
    m.erase(m.begin());
    
    for(auto i : m)
        cout << i.first << " " << i.second
        << endl;
    return 0;        

    return 0;
}