#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <cstring>
using namespace std;

int main() {

  // construction uses aggregate initialization
  // double-braces required
  array<int, 5> ar1{{3, 4, 5, 1, 2}};
  array<int, 5> ar2 = {1, 2, 3, 4, 5};
  array<string, 2> ar3 = {{string("a"), "b"}};

  cout << "Sizes of arrays are" << endl;
  cout << ar1.size() << endl;
  cout << ar2.size() << endl;
  cout << ar3.size() << endl;
  
  cout << "\nInitial ar1 : ";
  for (auto i : ar1)
    cout << i << ' ';

  // container operations are supported
  sort(ar1.begin(), ar1.end());

  cout << "\nsorted ar1 : ";
  for (auto i : ar1)
    cout << i << ' ';

  // Filling ar2 with 10
  ar2.fill(10);

  cout << "\nFilled ar2 : ";
  for (auto i : ar2)
    cout << i << ' ';


  // ranged for loop is supported
  cout << "\nar3 : ";
  for (auto &s : ar3)
    cout << s << ' ';

  array <int , 3> arr={'G','f','G'};  // ASCII val of 'G' =71 
    cout<<arr.front() <<" "<<arr.back();
    
    array <int , 3> arr={'G','f','G'};  // ASCII val of 'G' =71 
    array <int , 3> arr1={'M','M','P'}; // ASCII val of 'M' = 77 and 'P' = 80
    arr.swap(arr1);  // now arr = {M,M,P}
    cout<<arr.front() <<" "<<arr.back();
    
  bool x = arr.empty(); // false ( not empty)
    cout<<boolalpha<<(x);
    
    cout<< arr.at(2) <<" " << arr1.at(2);
    //cout<< arr.at(3); // exception{Abort signal from abort(3) (SIGABRT)}

     array <int , 5> arr;
    arr.fill(1);
    for(int i: arr)
       cout<<arr[i]<<" ";


  array <int , 10> arr;    
    cout<<arr.size()<<'\n'; // total num of indexes
    cout<<arr.max_size()<<'\n'; // total num of indexes
    cout<<sizeof(arr); // total size of array
    
    
   const char* str = "GeeksforGeeks";
  array<char,13> arr;
  memcpy (arr.data(),str,13);
  cout << arr.data() << '\n';
  
  
      array<int, 5> arr = {5, 4, 3, 2, 1};

    sort(arr.begin(), arr.end());

    for (auto x : arr)
        cout << x << " ";

  return 0;
}