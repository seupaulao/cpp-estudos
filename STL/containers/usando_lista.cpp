#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main(){
    list<int> myList;

    myList.push_back(10);
    myList.push_back(20);
    myList.push_front(5);

    cout << "List elements: ";
    for (int n : myList){
        cout << n << " ";
    }
    cout << endl;

    list<int> l = {3, 2};

    l.push_back(5);
    l.push_front(1);
    auto it = l.begin();
    advance(it, 2);
    l.insert(it, 4);

    for (auto i : l)
        cout << i << " ";

    cout << l.front() << endl;
    cout << l.back() << endl;
    cout << *next(l.begin(), 2);    

    l = {1, 3, 4, 2, 5};

    l.front() = 11;
    auto it = l.begin();
    advance(it, 2);
    
    *it = 10;

    for (auto i : l)
        cout << i << " ";

     // Finding 4
    auto it = find(l.begin(), l.end(), 4);
    if (it != l.end())
        cout << *it;
    else
        cout << "Element Not Found!";
        
    // Traversing using iterators
    for (auto it = l.begin(); it != l.end(); ++it)
        cout << *it << " ";
        
    l.pop_back();
    l.pop_front();
    
    auto it = l.begin();
    advance(it, 2);
    l.erase(it);

    for (auto i : l)
        cout << i << " ";    

    return 0;
}