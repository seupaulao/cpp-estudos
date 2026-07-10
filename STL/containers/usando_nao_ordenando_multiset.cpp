#include <bits/stdc++.h>
using namespace std;

int main() {
    
    // Create an empty unordered multiset
    unordered_multiset<int> ums1;
    
    // Create and initialize elements
    // using initialzer list
    unordered_multiset<int> ums2 =
                          {5, 3, 4, 1, 1};
    
    for(auto x : ums2)
        cout << x << " ";;

  unordered_multiset<int> ums;
    
    // Insert elements using insert()
    ums.insert(5);
    ums.insert(1);
    ums.insert(3);
    ums.insert(1);
    ums.insert(2);
    ums.insert(4);
    
    for (auto x : ums) cout << x << ' ';
    
     // Accessing element using iterator
    auto it = next(ums.begin(), 2);
    cout << *it;

    auto it = ums.find(2);

    // Error: elements of unordered_multiset
    // cannot be modified directly
    *it = 10;

    // Finding 3
    auto it = ums.find(3);
    
    if (it != ums.end()) cout << *it;
    else cout << "Element not Found!";    


        // Using range-based for loop
    for(auto x : ums)
        cout << x << " ";
    cout << "\n";


    // Delete all occurrences of element 1
    ums.erase(1);
    
    // Delete 2 using iterator
    ums.erase(ums.find(2));
    
   for (auto x: ums) cout << x << " ";
   cout << "\n";
    return 0;
}