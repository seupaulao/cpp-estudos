// C++ program to demonstrate the use of std::unique
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Defining the BinaryFunction
bool Pred(char a, char b)
{
    // Checking if both the arguments are same and equal
    // to 'G' then only they are considered same
    // and duplicates are removed
    if (a == b && a == 'G') {
        return 1;
    }
    else {
        return 0;
    }
}

int main()
{
    vector<int> v = { 1, 1, 3, 3, 3, 10, 1, 3, 3, 7, 7, 8 };

    vector<int>::iterator ip;

    // Using std::unique
    ip = std::unique(v.begin(), v.begin() + 12);
    // Now v becomes {1 3 10 1 3 7 8 * * * * *}
    // * means undefined

    // Resizing the vector so as to remove the undefined
    // terms
    v.resize(std::distance(v.begin(), ip));

    // Displaying the vector after applying std::unique
    for (ip = v.begin(); ip != v.end(); ++ip) {
        cout << *ip << " ";
    }
    //-----------------------------------------
     // Declaring a string
    string s = "You arre vvvisiting GGGGFGGGG";

    // Using std::unique to remove the consecutive
    // G in the word
    auto ip = std::unique(s.begin(), s.end(), Pred);

    // Displaying the corrected string
    cout << string(s.begin(), ip);

    //---------------------------------------------------------
    //remover todas as duplicatas de um container, não apenas as consecutivas, podemos usar o algoritmo `std::unique()` em conjunto com `std::sort()`. Primeiro, ordenamos o contêiner e, em seguida, aplicamos `std::unique()` para remover os elementos duplicados. Aqui está um exemplo:
   vector<int> v = { 1, 2, 3, 3, 3, 10, 1, 2, 3, 7, 7, 8 };

    vector<int>::iterator ip;

    // Sorting the array
    std::sort(v.begin(), v.end());
    // Now v becomes 1 1 2 2 3 3 3 3 7 7 8 10

    // Using std::unique
    ip = std::unique(v.begin(), v.begin() + 12);
    // Now v becomes {1 2 3 7 8 10 * * * * * *}
    // * means undefined

    // Resizing the vector so as to remove the undefined
    // terms
    v.resize(std::distance(v.begin(), ip));

    // Displaying the vector after applying std::unique
    for (ip = v.begin(); ip != v.end(); ++ip) {
        cout << *ip << " ";
    }
 //--------------------------------------------------------
 //contar elementos unicos
  vector<int> v = { 1, 1, 3, 3, 3, 10, 1, 3, 3, 7, 7, 8 };

    vector<int>::iterator ip;

    int count;
    sort(v.begin(), v.end());

    // Using std::unique and std::distance to count
    // unique elements in a container
    count = std::distance(
        v.begin(), std::unique(v.begin(), v.begin() + 12));

    // Displaying the value of count
    cout << "Total no. of unique elements = " << count;       

    return 0;
}