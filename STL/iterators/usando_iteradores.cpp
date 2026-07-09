#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1,2,3,4,5};
    
    // Get the iterator of first element of the vector
    vector<int>::iterator it = v.begin();
    
    // Print the content of location which is 
    // pointed by iterator (it)
    cout << *it;
    return 0;
}