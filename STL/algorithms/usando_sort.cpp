#include <bits/stdc++.h>
using namespace std;

// Implementation of bubble sort algorithm
void bubbleSort(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
              
                // Swap element if in wrong order
                swap(v[j], v[j + 1]);
            }
        }
    }
}

// Implementation of counting sort algorithm
void countingSort(vector<int>& v) {
    int m = *max_element(v.begin(), v.end());
    vector<int> count(m + 1, 0);
    for (int i : v) {
        count[i]++;
    }

    int index = 0;
    for (int i = 0; i <= m; i++) {
        while (count[i] > 0) {
            v[index++] = i;
            count[i]--;
        }
    }
}

pair<int, int> findMinDiff(vector<int>& v) {
    
    // Sort the vector
    sort(v.begin(), v.end());

    // Initialize variables to track the minimum difference and the pair
    int minDiff = INT_MAX;
    pair<int, int> res;

    // Traverse the vector to find the minimum difference
    for (auto i = 0; i < v.size() - 1; i++) {
        int diff = v[i + 1] - v[i];
        if (diff < minDiff) {
            minDiff = diff;
            res = {v[i], v[i + 1]};
        }
    }

    return res;
}


int main() {
    vector<int> v1 = {5, 3, 1, 4, 2};

    // Default ascending order
    sort(v1.begin(), v1.end());

    for (int i : v1) cout << i << " ";

     vector<int> v2 = {5, 3, 1, 4, 2};

    // Use Bubble Sort to sort vector v
    bubbleSort(v2);

    for (int i : v2) cout << i << " ";

    vector<int> v3 = {5, 3, 1, 4, 2};

    // Use Counting Sort to sort vector v
    countingSort(v3);

    for (int i : v3) cout << i << " ";


    vector<int> v4 = { 1, 3, 1, 1, 2, 3, 2, 4, 5 };

  	// Sort the vector to bring duplicate elements adjacent
    sort(v4.begin(), v4.end());

    // Use unique() to bring all the duplicates to end
    auto it = unique(v4.begin(), v4.end());

    // Remove the duplicates
    v4.erase(it, v4.end());

    for (auto& i : v4) cout << i << " ";
    
    
    //k-esimo maior elemento
    int arr[5] = {5, 3, 1, 4, 2};
  	int n = sizeof(arr)/sizeof(arr[0]);
  	int k = 3;

  	// Sort the vector
    sort(arr, arr + n);

   // kth largest element will be present at n-k index
    cout << arr[n - k];

     vector<int> v5 = {4, 2, 9, 7, 1, 5};

    // Find the pair with the minimum difference
    pair<int, int> res = findMinDiff(v5);

    cout << res.first << ", " << res.second;
  

    return 0;
}