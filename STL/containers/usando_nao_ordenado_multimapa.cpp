#include <bits/stdc++.h>
using namespace std;

/**
 * 
 * `std::unordered_multimap` é um contêiner associativo não ordenado na 
 * STL do C++ que armazena elementos como pares chave-valor usando uma tabela hash. 
 * Diferentemente de `std::unordered_map`, ele permite que múltiplos elementos 
 * tenham a mesma chave, ao mesmo tempo que oferece operações de inserção, 
 * remoção e busca eficientes no caso médio. 
 * Armazena múltiplos valores associados à mesma chave e não mantém os elementos 
 * em nenhuma ordem específica. 
 * Oferece complexidade O(1) no caso médio para operações de inserção, remoção 
 * e busca usando hashing.
 */
int main() {
    
    // Creating an empty unordered_multimap
    unordered_multimap<int, string> umm1;
    
    // Creating unordered_multimap using
    // initializer list
    unordered_multimap<int, string> umm2 =
    {{1, "Geeks"}, {2, "For"}, {1, "C++"}};

    for (auto x : umm2) 
        cout << x.first << ": " << x.second
        << endl;

//inserindo

    unordered_multimap<int, string> umm;
    
    // Insert elements using insert()
    umm.insert({2, "For"});
    umm.insert({3, "C++"});
    umm.insert({2, "Geeks"});
    
    for (auto x : umm) 
        cout << x.first << ": "
        << x.second << endl;

//acessando
   // Find 2nd element
    auto it = next(umm.begin(), 1);
    
    if (it != umm.end())
        cout << it->first << ": " <<
        it->second;
    else
        cout << "Element not found!";

//buscando
    // Searching for key '2' using find()
    auto it = umm.find(2);
    
    if (it != umm.end())
        cout << it->first << ": " <<
            it->second;
    else
        cout << "Element not Found!";

//buscando e alterando
    // Searching for key '2' using find()
    auto it = umm.find(2);
    
    // Updating value
    it->second = "Java";
    
    for (auto x: umm)
        cout << x.first << ": " << x.second
        << endl;
        
//apagando
    // Delete all elements which are 
    // associated with key 1
    umm.erase(1);
    
    // Delete first element
    // using iterator
    umm.erase(umm.begin());
    
    for(auto x: umm)
        cout << x.first << " " << x.second;

    return 0;
}