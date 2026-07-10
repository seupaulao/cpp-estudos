#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<int> v = {1, 3, 6, 8, 9};
    int k = 8;

    if (binary_search(v.begin(), v.end(), k))
        cout << k << " is Present";
    else
        cout << k << " is NOT Present";

//exemplo 2
    int arr[] = {1, 4, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 7;

    // Check if the element exists
    if (binary_search(arr, arr + n, k))
        cout << k << " is Present";
    else
        cout << k << " is NOT Present";
    return 0;
    
//exemplo 3 com sets

set<int> s = {1, 4, 5, 7, 9};
    int k = 8;

    // Check if the element exists
    if (binary_search(s.begin(), s.end(), k))
        cout << k << " is Present";
    else
        cout << k << " is NOT Present";
    return 0;

    return 0;
}