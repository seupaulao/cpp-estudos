#include <bits/stdc++.h>
using namespace std;

void printFL(forward_list<int>& fl) {
    for (auto i : fl)
        cout << i << " ";
    cout << '\n';
}

int main() {
    
    forward_list<int> fl1;
    forward_list<int> fl2(3, 4);
    forward_list<int> fl3 = {1, 5, 3, 4};
    
    printFL(fl2);
    printFL(fl3);

     forward_list<int> fl = {1, 5, 3, 4};

    // Access the first element
    cout << fl.front() << endl;
    
    // Access third element
    auto it = next(fl.begin(), 2);
    cout << *it;

    // Inserting Element at front
    fl.push_front(1);
    
    // Insert 3 after the second element
    auto it = fl.begin();
    advance(it, 1);
    fl.insert_after(it, 3);

    // Updating first element
    fl.front() = 111;
    cout << fl.front() << endl;
    
    // Updating third element
    auto it = next(fl.begin(), 2);
    *it = 333;
    cout << *it;

     // Finding 3
    auto it = find(fl.begin(), fl.end(), 3);
    
    if (it != fl.end()) cout << *it;
    else cout << "Element not Found";

    // Traversing using range-based for loop
    for(auto i : fl)
        cout << i << " ";
    cout << endl;

    // Delete first element
    fl.pop_front();
    
    // Delete third element
    auto it = fl.begin();
    advance(it, 1);
    fl.erase_after(it);
    
    for (auto x: fl) cout << x << " ";

    int size = distance(fl.begin(),fl.end());
    cout<<"Size of forward_list: "<<size<<endl;

    forward_list<int> flist;

    if (flist.empty()) {
        cout << "The forward_list is empty." << endl;
    }

    flist.push_front(10);

    if (!flist.empty()) {
        cout << "The forward_list is not empty." << endl;
    }

    return 0;
}