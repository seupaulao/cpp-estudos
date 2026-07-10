#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    // Reversing the vector
    reverse(v.begin(), v.end());

    for (int i : v) cout << i << " ";

    //reverse the array
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

  	// Reverse the array arr
    reverse(arr, arr + n);

    for (int i : arr) cout << i << " ";    

    string s = "abcd";

  	// Reverse the string s
    reverse(s.begin(), s.end());

    cout << s;

    //rotate a vetor com reverse
    vector<int> v = {1, 3, 6, 2, 9};
    int n = v.size();
    int d = 2;

    // Left rotate the vector by d place
    reverse(v.begin(), v.begin() + d);
    reverse(v.begin() + d, v.end());
    reverse(v.begin(), v.end());

    for (auto i : v)
        cout << i << " ";    

    return 0;
}