#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/**
 * As funções `accumulate()` e `partial_sum()` são usadas para encontrar a soma ou qualquer outro valor acumulado obtido pela adição ou qualquer outra operação binária nos elementos do intervalo fornecido. Ambas as funções fazem parte da Biblioteca Numérica da STL e estão definidas no cabeçalho `<numeric>`.
 */

int multiply(int a, int b) {
    return a * b;
} 

int main() {
    vector<int> vec = {5, 10, 15};

    // Compute sum of all elements
    int sum = accumulate(vec.begin(), vec.end(), 0);

    cout << sum << endl; 

    vector<int> vec1 = {5, 10, 15};

    // Compute product using custom function
    int product = accumulate(vec1.begin(), vec1.end(), 1, multiply);

    cout << product << endl;     
 /*
 A função `std::partial_sum()` atribui a soma cumulativa de todos os valores do conjunto que se encontram no intervalo especificado e a armazena em outro contêiner nas posições correspondentes. Assim como a função `accumulate()`, podemos modificar a função `partial_sum()` para realizar qualquer outra operação binária.
 */   

   vector<int> vec2 = {5, 10, 15};
    vector<int> res(vec2.size());

    // Compute cumulative sum
    partial_sum(vec2.begin(), vec2.end(), res.begin());

    for (int val : res)
        cout << val << " "; 

//usando o multiply method

  vector<int> vec3 = {5, 10, 15};
    vector<int> res3(vec3.size());

    // Compute cumulative product
    partial_sum(vec3.begin(), vec3.end(), res3.begin(), multiply);

    for (int val : res3)
        cout << val << " ";  
    return 0;
}