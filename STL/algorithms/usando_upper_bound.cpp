#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool comp(const string &a, const string &b)
{
    return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                   [](char c1, char c2) { return tolower(c1) < tolower(c2); });
}

int main()
{
    vector<int> v = {10, 20, 30, 40, 50};

    // Finding upper bound for value 30 in vector v
    cout << *upper_bound(v.begin(), v.end(), 30);

//upper bound no array
 int arr[5] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Finding upper bound for value 30 in array arr
    cout << *upper_bound(arr, arr + n, 30);

    //upper bound no string
 vector<string> v = {"Apple", "banana", "Cherry", "date", "Elderberry"};

    // Finding upper bound of "Avocado"
    auto ub = upper_bound(v.begin(), v.end(), "Avocado", comp);

    if (ub != v.end())
        cout << *ub;
    else
        cout << "Upper bound not found!";
        
//Check for an Element in a Sorted Vector
 vector<int> v = {10, 20, 30, 40, 50};
    int val = 40;

    // Finding the upper bound
    auto it = upper_bound(v.begin(), v.end(), val);

    // Chekcing if val exists or not
    if (it != v.begin() && *(--it) == val)
        cout << val << " is found.";
    else
        cout << val << " is NOT found.";
        
//Count Elements Smaller and Larger than a Value
 vector<int> v = {10, 20, 30, 40, 50};
    int val = 30;

    // Finding the upper bound of val in v
    auto ub = upper_bound(v.begin(), v.end(), val);

    // Finding the number of smaller elements
    cout << "No. of Smaller Elements: " << ub - v.begin() << endl;

    // Finding the number of larger elements
    cout << "No. of Larger Elements: " << v.end() - ub;

//Finding Upper Bound in a Set
  set<int> s = {1, 2, 4, 4, 6, 8};

    // Recommended: O(log n)
    auto it1 = s.upper_bound(4);

    if (it1 != s.end())
        cout << "set::upper_bound -> " << *it1 << endl;
    else
        cout << "set::upper_bound -> Not found" << endl;

    // Not recommended: O(n) for set
    auto it2 = upper_bound(s.begin(), s.end(), 4);

    if (it2 != s.end())
        cout << "std::upper_bound -> " << *it2 << endl;
    else
        cout << "std::upper_bound -> Not found" << endl;

    return 0;
}