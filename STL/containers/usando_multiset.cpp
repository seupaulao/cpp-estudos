#include <iostream>
#include <set>
using namespace std;

int main()
{
    // Creating an empty multiset of integers
    multiset<int> ms1;
    
    // Initialize with initializer list
    multiset<int> ms2 = {5, 3, 3, 1};
    
    // Print elements (automatically sorted)
    for (auto i : ms2)
        cout << i << " ";

    // Creating a multiset of integers
    multiset<int> ms;

    // Inserting elements (duplicates allowed)
    ms.insert(5);
    ms.insert(3);
    ms.insert(3);
    ms.insert(1);

    // Print elements (automatically sorted)
    for (auto i : ms)
        cout << i << " ";
        
    // Access first element
    auto it1 = ms.begin();
    cout << *it1 << " ";

    // Access third element
    auto it2 = next(it1, 2);
    cout << *it2;
    
    // Finding an element (3)
    auto it = ms.find(3);

    if (it != ms.end())
        cout << *it;
    else
        cout << "Not Found!";
       
    // Delete first element
    ms.erase(ms.begin());

    // Delete all occurrences of 3
    ms.erase(3);

    // Print remaining elements
    for (auto x : ms)
        cout << x << " ";        

    return 0;
}