#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {2, 3, 2, 1, 5, 4, 2};

    // Count the occurrence of 2
    cout << count(v.begin(), v.end(), 2);

vector<string> v = {"Hi", "Geeks", 
                        "GeeksforGeeks", 
                        "Geeks"};

    // Count the occurrence of "Geeks"
    cout << count(v.begin(), v.end(), "Geeks");
    
  multiset<int> m= {1, 1, 2, 3, 2, 2, 2, 1};
	
    // Counting the frequency of 2 
    cout << count(m.begin(), m.end(), 2);
    
    
    vector<int> v = {2, 3, 2, 1, 5, 4, 2};
  	int val = 7;
  
  	// Count the occurrence of 7
  	int c = count(v.begin(), v.end(), val);

    // Check if the element exists
    if (c)
      	cout << c;
    else
      	cout << val << " Not Exists";
    return 0;
}