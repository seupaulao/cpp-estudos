#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v1 = {1, 3, 6, 2, 9};

    // Sorting the vector
    sort(v1.begin(), v1.end());

    // Search for element 6
    auto it = find(v1.begin(), v1.end(), 6);

    // Print index
    cout << distance(v1.begin(), it);

    int arr[5] = {1, 3, 6, 2, 9};

    // Search an element 6
    auto it = find(arr, arr + 5, 6);

	// Print index
    // cout << distance(arr, it);    

    vector<int> v2 = {1, 3, 6, 2, 9};

    // Search an element 22
    auto it = find(v2.begin(), v2.end(), 22);
	
  	// Check if element is present
  	if (it != v2.end())
      
    	// Print index
        cout << distance(v2.begin(), it);
    else
        cout << "Not Present";    

    return 0;
}