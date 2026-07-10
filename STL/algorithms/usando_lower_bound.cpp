/*
A função `std::lower_bound()` é um algoritmo da STL que retorna um iterador 
apontando para o primeiro elemento maior ou igual a um determinado valor em um 
intervalo ordenado. É comumente usada para buscas, localização de posições de 
inserção e execução de operações eficientes baseadas em busca binária. 

- Retorna o primeiro elemento com valor igual ou superior a um determinado 
valor em um intervalo ordenado. 
- Sua complexidade de execução é O(log n) para contêineres de acesso aleatório. 
- Definida no cabeçalho `<algorithm>`.

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(const string &a, const string &b)
{
    return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                   [](char c1, char c2) { return tolower(c1) < tolower(c2); });
}

int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    auto it = lower_bound(v.begin(), v.end(), 30);

    cout << *it;
    return 0;

//Aplicacoes de lower_bound

//Find the Lower Bound of a Value in Array

 int arr[5] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Finding lower bound for value 35 in array arr
    cout << *lower_bound(arr, arr + n, 35);

//Case-Insensitive Search in a Vector of Strings

 vector<string> v = {"Apple", "banana", "Cherry", "date", "Elderberry"};

    // Finding lower bound of "Avocado"
    auto lb = lower_bound(v.begin(), v.end(), "Avocado", comp);

    // Checking if lower bound is found
    if (lb != v.end())
        cout << *lb;
    else
        cout << "Lower bound not found!";

//Check Whether an Element Exists
 vector<int> v1 = {10, 20, 30, 40, 50};
    int val = 40;

    // Cheking if val exists in the vector v1
    auto it = lower_bound(v1.begin(), v1.end(), val);
    if (*it == val)
        cout << val << " is found.";
    else
        cout << val << " is NOT found.";

//Count Smaller and Larger Elements

 vector<int> v2 = {10, 20, 30, 40, 50};
    int val = 35;

    // Finding lower and upper bound of val in v2
    auto lb = lower_bound(v2.begin(), v2.end(), val);

    // Finding the number of smaller elements
    cout << "No. of Smaller Elements: " << lb - v2.begin() << endl;

    // Finding the number of larger elements
    cout << "No. of Larger Elements: " << v2.size() - (lb - v2.begin());



//Insert an Element in a Sorted Vector
vector<int> v3 = {10, 20, 30, 40, 50};
    int val = 35;

    // Finding lower and upper bound of val in v3
    auto lb = lower_bound(v3.begin(), v3.end(), val);

    // Inserting 35 to its correct position
    v3.insert(lb, val);

    for (auto i : v3)
        cout << i << " ";

//Finding the Lower Bound in a Set
 set<int> s = {10, 20, 30, 40, 50};

    // Finding lower bound for value 35 in array arr
    cout << *lower_bound(s.begin(), s.end(), 35);


         

}