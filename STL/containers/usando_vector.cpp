#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    
    // Declares an empty vector
    vector<int> v1;
    
    // Declares vector with given size
    // and fills it with a value
    vector<int> v2(3, 5);  
    
    // Print items of v2
    for (int x : v2) {
        cout << x << " ";
    }
    
    cout << endl;
    
    // Initializes vector using 
    // initializer list.
    vector<int> v3 = {1, 2, 3};  
    
    // Print items of v3
    for (int x : v3) {
        cout << x << " ";
    }

    vector<char> v = {'a', 'f', 'd'};
  
  	// Inserting 'z' at the back
  	v.push_back('z');
  
  	// Inserting 'c' at index 1
  	v.insert(v.begin() + 1, 'c');

  	for (char i : v)
        cout << i << " ";

    vector<int> vv = {10, 20, 30};
    cout << "Original value at index 1: " << vv[1] << endl;

    // Updating the element at index i
    vv[1] = 50;

    cout << "Updated value at index 1: " << vv[1] << endl;    

    cout << "Size of vector: " << vv.size() << endl;

    vv.push_back(40); // Adds a new element at the end

    vv.push_back(60); // Adds a new element at the end

    vv.pop_back(); // Removes the last element

    vv.erase(find(vv.begin(), vv.end(), 20)); // Removes the element with value 20

    cout << "Size of vector after erasing: " << vv.size() << endl;

    vector<int>ev;
    
    // Check if the vector is empty
    if(ev.empty()){
        cout<<"Vector is empty."<<endl;
    }
    
    // Add an element
    ev.push_back(100);
    if(!ev.empty()){
        cout<<"Vector is not empty. First element "<<ev[0]<<endl;
    }

     // Declaring and Initializing a 2D vector
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Traversing using range-based loop with auto
    for (const auto &row : matrix) {
        for (const auto &val : row) {
            cout << val << " ";
        }
        cout<<endl;
    }
    
    return 0;
}