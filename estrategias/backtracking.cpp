/*
O que é Backtracking?
Backtracking é uma técnica algorítmica de resolução de problemas que envolve encontrar uma solução incrementalmente, tentando diferentes opções e desfazendo-as se elas levarem a um beco sem saída. É comumente usado em situações em que você precisa explorar múltiplas possibilidades para resolver um problema, como procurar um caminho em um labirinto ou resolver quebra-cabeças como Sudoku. Quando um beco sem saída é alcançado, o algoritmo volta ao ponto de decisão anterior e explora um caminho diferente até que uma solução seja encontrada ou todas as possibilidades tenham sido esgotadas.

Backtracking pode ser definido como uma técnica algorítmica geral que considera a busca de todas as combinações possíveis para resolver um problema computacional.

Terminologias básicas
Candidato: Um candidato é uma escolha ou elemento potencial que pode ser adicionado à solução atual.
Solução: A solução é uma configuração válida e completa que satisfaz todas as restrições do problema.
Solução parcial: Uma solução parcial é uma configuração intermediária ou incompleta sendo construída durante o processo de backtracking.
Espaço de decisão: O espaço de decisão é o conjunto de todos os candidatos ou escolhas possíveis em cada ponto de decisão.
Ponto de decisão: Um ponto de decisão é uma etapa específica no algoritmo em que um candidato é escolhido e adicionado à solução parcial.
Solução viável: Uma solução viável é uma solução parcial ou completa que adere a todas as restrições.
Beco sem saída: Um beco sem saída ocorre quando uma solução parcial não pode ser estendida sem violar restrições.
Retrocesso: Retrocesso envolve desfazer decisões anteriores e retornar a um ponto de decisão anterior.
Espaço de busca: O espaço de busca inclui todas as combinações possíveis de candidatos e escolhas.
Solução ótima: Em problemas de otimização, a solução ótima é a melhor solução possível.
Tipos de problemas de retrocesso
Os problemas associados ao retrocesso podem ser categorizados em 3 categorias:

Problemas de decisão: Aqui, buscamos uma solução viável.
Problemas de otimização: Para este tipo, buscamos a melhor solução.
Problemas de enumeração: Encontramos o conjunto de todas as soluções viáveis ​​possíveis para os problemas deste tipo.

Applications of Backtracking
Creating smart bots to play Board Games such as Chess.
Solving mazes and puzzles such as N-Queen problem.
Network Routing and Congestion Control.
Decryption
Text Justification
*/

/*
Printing all solutions in N-Queen Problem
Last Updated : 01 Oct, 2024
Given an integer n, the task is to find all distinct solutions to the n-queens problem, where n queens are placed on an n×n chessboard such that no two queens can attack each other.

Each solution is a unique configuration of n queens, represented as a permutation of [1,2,3,….,n]. The number at the ith position indicates the row of the queen in the ith column. For example, [3,1,4,2] shows one such layout.

Example:

Input: 4
Output: [2, 4, 1, 3 ], [3, 1, 4, 2]
Explaination: These are the 2 possible solutions.


Input: 1
Output: [1]
Explaination: Only one queen can be placed in the single cell available.
*/

//solução por abordagem naive

#include <bits/stdc++.h>
using namespace std;

// Function to check if the current placement is safe
bool isSafe(const vector<int>& board, int currRow,
                                      int currCol) {

    // Check all previously placed queens
    for(int i = 0; i < board.size(); ++i) {
        int placedRow = board[i];

        // Columns are 1-based
        int placedCol = i + 1;

        // Check if the queen is on the same diagonal
        if(abs(placedRow - currRow) == 
                          abs(placedCol - currCol)) {
            return false; // Not safe
        }
    }

    // Safe to place the queen
    return true; 
}

// Recursive function to generate all possible permutations
void nQueenUtil(int col, int n, vector<int>& board, 
  vector<vector<int>>& result, vector<bool>& visited) {

    // If all queens are placed, add into result
    if(col > n) {
        result.push_back(board);
        return;
    }

    // Try placing a queen in each row
    // of the current column
    for(int row = 1; row <= n; ++row) {

        // Check if the row is already used
        if(!visited[row]) {
            
            // Check if it's safe to place the queen
            if(isSafe(board, row, col)) {

                // Mark the row as used
                visited[row] = true; 

                // Place the queen
                board.push_back(row); 

                // Recur to place the next queen
                nQueenUtil(col + 1, n, board,
                             result, visited);

                // Backtrack: remove the queen
                board.pop_back(); 
                visited[row] = false; // Unmark row
            }
        }
    }
}

// Main function to find all distinct 
// result to the n-queens puzzle
vector<vector<int>> nQueen(int n) {
    vector<vector<int>> result; 

    // Current board configuration
    vector<int> board; 

    // Track used rows
    vector<bool> visited(n + 1, false); 

    // Start solving from the first column
    nQueenUtil(1, n, board, result, visited);
    return result; 
}

int main() {
    int n = 4; 
    
    vector<vector<int>> result = nQueen(n); 

    for(auto &res : result) {
        cout << "[";
        for(int i = 0; i < n; ++i) {
            cout << res[i]; 
            if(i != n - 1) cout << ", "; 
        }
        cout << "]\n";
    }
    return 0;
}

/*
Abordagem de retrocesso com poda
Para otimizar a abordagem ingênua, podemos usar retrocesso com poda. Em vez de gerar todas as permutações possíveis, construímos a solução incrementalmente, enquanto fazemos isso, podemos garantir a cada passo que a solução parcial permaneça válida. Se um conflito for detectado, retrocederemos imediatamente, o que evitará cálculos desnecessários.

Essa abordagem reduz significativamente o espaço de busca e é o método padrão para resolver o problema N-Queens de forma eficiente.

Abordagem passo a passo:

Comece na primeira coluna e tente colocar uma rainha em cada linha.
Mantenha matrizes para rastrear quais linhas já estão ocupadas. Da mesma forma, para rastrear diagonais maiores e menores já estão ocupadas.
Se o posicionamento de uma rainha entrar em conflito com rainhas existentes, pule essa linha e retroceda a rainha para tentar a próxima linha possível (Poda e retroceda durante o conflito).
*/

#include <bits/stdc++.h>
using namespace std;

 // Utility function for solving the N-Queens
// problem using backtracking.
void nQueenUtil(int j, int n, vector<int> &board,
vector<vector<int>> &result, vector<bool> &rows,
vector<bool> &diag1, vector<bool> &diag2){
  if (j > n){
      
        // A solution is found
        result.push_back(board);
        return;
    }
    for (int i = 1; i <= n; ++i){
        if (!rows[i] && !diag1[i + j] &&
                          !diag2[i - j + n]){

            // Place queen
            rows[i] = diag1[i + j] =
                        diag2[i - j + n] = true;
            board.push_back(i);

            // Recurse to the next column
            nQueenUtil(j + 1, n, board, result,
                            rows, diag1, diag2);

            // Remove queen (backtrack)
            board.pop_back();
            rows[i] = diag1[i + j] =
                    diag2[i - j + n] = false;
        }
    }
}

// Solves the N-Queens problem and returns
// all valid configurations.
vector<vector<int>> nQueen(int n){
    vector<vector<int>> result;
    vector<int> board;

    // Rows occupied
    vector<bool> rows(n + 1, false);

    // Major diagonals (row + j)
    vector<bool> diag1(2 * n, false);

    // Minor diagonals (row - col + n)
    vector<bool> diag2(2 * n, false);

    // Start solving from the first column
    nQueenUtil(1, n, board, result, rows,
                                diag1, diag2);
    return result;
}

int main(){
    int n = 4;

    vector<vector<int>> result = nQueen(n);

    for (auto &res : result){
        cout << "[";
        for (int i = 0; i < n; ++i){
            cout << res[i];
            if (i != n - 1)
                cout << ", ";
        }
        cout << "]\n";
    }
    return 0;
}

/*
Algorithm to Solve Sudoku | Sudoku Solver
Last Updated : 30 Jul, 2024
Given a partially filled 9×9 2D array ‘grid[9][9]’, the goal is to assign digits (from 1 to 9) to the empty cells so that every row, column, and subgrid of size 3×3 contains exactly one instance of the digits from 1 to 9. 

sudoku

Examples: 

Input: grid
{ {3, 0, 6, 5, 0, 8, 4, 0, 0},
{5, 2, 0, 0, 0, 0, 0, 0, 0},
{0, 8, 7, 0, 0, 0, 0, 3, 1},
{0, 0, 3, 0, 1, 0, 0, 8, 0},
{9, 0, 0, 8, 6, 3, 0, 0, 5},
{0, 5, 0, 0, 9, 0, 6, 0, 0}, 
{1, 3, 0, 0, 0, 0, 2, 5, 0},
{0, 0, 0, 0, 0, 0, 0, 7, 4},
{0, 0, 5, 2, 0, 6, 3, 0, 0} }
Output:
3 1 6 5 7 8 4 9 2
5 2 9 1 3 4 7 6 8
4 8 7 6 2 9 5 3 1
2 6 3 4 1 5 9 8 7
9 7 4 8 6 3 1 2 5
8 5 1 7 9 2 6 4 3
1 3 8 9 4 7 2 5 6
6 9 2 3 5 1 8 7 4
7 4 5 2 8 6 3 1 9
Explanation: Each row, column and 3*3 box of the output matrix contains unique numbers.


Input: grid
{ { 3, 1, 6, 5, 7, 8, 4, 9, 2 },
{ 5, 2, 9, 1, 3, 4, 7, 6, 8 },
{ 4, 8, 7, 6, 2, 9, 5, 3, 1 },
{ 2, 6, 3, 0, 1, 5, 9, 8, 7 },
{ 9, 7, 4, 8, 6, 0, 1, 2, 5 },
{ 8, 5, 1, 7, 9, 2, 6, 4, 3 },
{ 1, 3, 8, 0, 4, 7, 2, 0, 6 },
{ 6, 9, 2, 3, 5, 1, 8, 7, 4 },
{ 7, 4, 5, 0, 8, 6, 3, 1, 0 } };
Output:
3 1 6 5 7 8 4 9 2 
5 2 9 1 3 4 7 6 8 
4 8 7 6 2 9 5 3 1 
2 6 3 4 1 5 9 8 7
9 7 4 8 6 3 1 2 5
8 5 1 7 9 2 6 4 3
1 3 8 9 4 7 2 5 6
6 9 2 3 5 1 8 7 4
7 4 5 2 8 6 3 1 9 
Explanation: Each row, column and 3*3 box of the output matrix contains unique numbers.
*/

/*
Abordagem ingênua - Naive:

A abordagem ingênua é gerar todas as configurações possíveis de números de 1 a 9 para preencher as células vazias. Tente cada configuração uma por uma até que a configuração correta seja encontrada, ou seja, para cada posição não atribuída, preencha a posição com um número de 1 a 9. Após preencher todas as posições não atribuídas, verifique se a matriz é segura ou não. Se for seguro, imprima, senão, recorre para outros casos.

Siga as etapas abaixo para resolver o problema:

Crie uma função que verifique se a matriz fornecida é um sudoku válido ou não. Mantenha Hashmap para a linha, coluna e caixas. Se qualquer número tiver uma frequência maior que 1 no hashMap, retorne false, senão, retorne true;
Crie uma função recursiva que pegue uma grade e o índice atual de linha e coluna.
Verifique alguns casos base.
Se o índice estiver no final da matriz, ou seja, i=N-1 e j=N, verifique se a grade é segura ou não, se for seguro, imprima a grade e retorne true, senão, retorne false.
O outro caso base é quando o valor da coluna é N, ou seja, j = N, então vá para a próxima linha, ou seja, i++ e j = 0.
Se o índice atual não for atribuído, preencha o elemento de 1 a 9 e repita para todos os 9 casos com o índice do próximo elemento, ou seja, i, j+1. Se a chamada recursiva retornar true, interrompa o loop e retorne true.
Se o índice atual for atribuído, chame a função recursiva com o índice do próximo elemento, ou seja, i, j+1
Abaixo está a implementação da abordagem acima:
*/

#include <iostream>

using namespace std;

// N is the size of the 2D matrix   N*N
#define N 9

/* A utility function to print grid */
void print(int arr[N][N])
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

// Checks whether it will be 
// legal to assign num to the
// given row, col
bool isSafe(int grid[N][N], int row, 
                       int col, int num)
{
    
    // Check if we find the same num 
    // in the similar row , we
    // return false
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return false;

    // Check if we find the same num in 
    // the similar column , we
    // return false
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return false;

    // Check if we find the same num in 
    // the particular 3*3 matrix,
    // we return false
    int startRow = row - row % 3, 
            startCol = col - col % 3;
  
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + 
                            startCol] == num)
                return false;

    return true;
}

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool solveSudoku(int grid[N][N], int row, int col)
{
    // Check if we have reached the 8th 
    // row and 9th column (0
    // indexed matrix) , we are 
    // returning true to avoid
    // further backtracking
    if (row == N - 1 && col == N)
        return true;

    // Check if column value  becomes 9 , 
    // we move to next row and
    //  column start from 0
    if (col == N) {
        row++;
        col = 0;
    }
  
    // Check if the current position of 
    // the grid already contains
    // value >0, we iterate for next column
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= N; num++) 
    {
        
        // Check if it is safe to place 
        // the num (1-9)  in the
        // given row ,col  ->we 
        // move to next column
        if (isSafe(grid, row, col, num)) 
        {
            
           /* Assigning the num in 
              the current (row,col)
              position of the grid
              and assuming our assigned 
              num in the position
              is correct     */
            grid[row][col] = num;
          
            //  Checking for next possibility with next
            //  column
            if (solveSudoku(grid, row, col + 1))
                return true;
        }
      
        // Removing the assigned num , 
        // since our assumption
        // was wrong , and we go for 
        // next assumption with
        // diff num value
        grid[row][col] = 0;
    }
    return false;
}

// Driver Code
int main()
{
    // 0 means unassigned cells
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

    if (solveSudoku(grid, 0, 0))
        print(grid);
    else
        cout << "no solution  exists " << endl;

    return 0;
    // This is code is contributed by Pradeep Mondal P
}

//solução por backtracking

// A Backtracking program in
// C++ to solve Sudoku problem
#include <bits/stdc++.h>
using namespace std;

// UNASSIGNED is used for empty
// cells in sudoku grid
#define UNASSIGNED 0

// N is used for the size of Sudoku grid.
// Size will be NxN
#define N 9

// This function finds an entry in grid
// that is still unassigned
bool FindUnassignedLocation(int grid[N][N],
                            int& row, int& col);

// Checks whether it will be legal
// to assign num to the given row, col
bool isSafe(int grid[N][N], int row,
            int col, int num);

/* Takes a partially filled-in grid and attempts 
to assign values to all unassigned locations in 
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool SolveSudoku(int grid[N][N])
{
    int row, col;

    // If there is no unassigned location,
    // we are done
    if (!FindUnassignedLocation(grid, row, col))
        // success!
        return true;

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++) 
    {
        
        // Check if looks promising
        if (isSafe(grid, row, col, num)) 
        {
            
            // Make tentative assignment
            grid[row][col] = num;

            // Return, if success
            if (SolveSudoku(grid))
                return true;

            // Failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
   
    // This triggers backtracking
    return false;
}

/* Searches the grid to find an entry that is 
still unassigned. If found, the reference 
parameters row, col will be set the location 
that is unassigned, and true is returned. 
If no unassigned entries remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N],
                            int& row, int& col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

/* Returns a boolean which indicates whether 
an assigned entry in the specified row matches
the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether 
an assigned entry in the specified column
matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether 
an assigned entry within the specified 3x3 box 
matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow,
               int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                    [col + boxStartCol] ==
                                       num)
                return true;
    return false;
}

/* Returns a boolean which indicates whether 
it will be legal to assign num to the given 
row, col location. */
bool isSafe(int grid[N][N], int row,
            int col, int num)
{
    /* Check if 'num' is not already placed in 
    current row, current column 
    and current 3x3 box */
    return !UsedInRow(grid, row, num)
           && !UsedInCol(grid, col, num)
           && !UsedInBox(grid, row - row % 3,
                         col - col % 3, num)
           && grid[row][col] == UNASSIGNED;
}

/* A utility function to print grid */
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++) 
    {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Driver Code
int main()
{
    // 0 means unassigned cells
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    if (SolveSudoku(grid) == true)
        printGrid(grid);
    else
        cout << "No solution exists";

    return 0;
}

// This is code is contributed by rathbhupendra

/*
Sudoku usando Bit Masks:
Este método é uma ligeira otimização dos 2 métodos acima. Para cada linha/coluna/caixa, crie uma bitmask e para cada elemento na grade, defina o bit na posição 'valor' como 1 nas bitmasks correspondentes, para verificações O(1).

Siga os passos abaixo para resolver o problema:

Crie 3 matrizes de tamanho N (uma para linhas, colunas e caixas).
As caixas são indexadas de 0 a 8. (para encontrar o índice da caixa de um elemento, usamos a seguinte fórmula: linha / 3 * 3 + coluna / 3).
Mapeie os valores iniciais da grade primeiro.
Cada vez que adicionarmos/removermos um elemento para/da grade, defina o bit como 1/0 para as bitmasks correspondentes.
*/

#include <bits/stdc++.h>
using namespace std;

#define N 9

// Bitmasks for each row/column/box
int row[N], col[N], box[N];
bool seted = false;

// Utility function to find the box index
// of an element at position [i][j] in the grid
int getBox(int i, int j) { return i / 3 * 3 + j / 3; }

// Utility function to check if a number
// is present in the corresponding row/column/box
bool isSafe(int i, int j, int number)
{
    return !((row[i] >> number) & 1)
           && !((col[j] >> number) & 1)
           && !((box[getBox(i, j)] >> number) & 1);
}

// Utility function to set the initial values of a Sudoku
// board (map the values in the bitmasks)
void setInitialValues(int grid[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            row[i] |= 1 << grid[i][j],
                col[j] |= 1 << grid[i][j],
                box[getBox(i, j)] |= 1 << grid[i][j];
}

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool SolveSudoku(int grid[N][N], int i, int j)
{
    // Set the initial values
    if (!seted)
        seted = true, setInitialValues(grid);

    if (i == N - 1 && j == N)
        return true;
    if (j == N)
        j = 0, i++;

    if (grid[i][j])
        return SolveSudoku(grid, i, j + 1);

    for (int nr = 1; nr <= N; nr++) {
        if (isSafe(i, j, nr)) {
            /*  Assign nr in the
                current (i, j)
                position and
                add nr to each bitmask
            */
            grid[i][j] = nr;
            row[i] |= 1 << nr;
            col[j] |= 1 << nr;
            box[getBox(i, j)] |= 1 << nr;

            if (SolveSudoku(grid, i, j + 1))
                return true;

            // Remove nr from each bitmask
            // and search for another possibility
            row[i] &= ~(1 << nr);
            col[j] &= ~(1 << nr);
            box[getBox(i, j)] &= ~(1 << nr);
        }

        grid[i][j] = 0;
    }

    return false;
}

// Utility function to print the solved grid
void print(int grid[N][N])
{
    for (int i = 0; i < N; i++, cout << '\n')
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << ' ';
}

// Driver Code
int main()
{
    // 0 means unassigned cells
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

    if (SolveSudoku(grid, 0, 0))
        print(grid);
    else
        cout << "No solution exists\n";

    return 0;
}
// This code is contributed
// by Gatea David

/*
Sudoku usando Cross-Hatching com backtracking:
Este método é uma otimização do método 2 acima. Ele roda 5X mais rápido que o método 2. Como costumávamos preencher o sudoku identificando primeiro o elemento que está quase preenchido. Ele começa identificando a linha e a coluna onde o elemento deve ser colocado. Escolher os elementos quase preenchidos primeiro dará uma poda melhor.
*/
// C++ Code
#include <algorithm>
#include <bits/stdc++.h>
#include <map>
#include <vector>

using namespace std;

// Input matrix
vector<vector<int> > arr
    = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
        { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
        { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
        { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
        { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
        { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
        { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

// Position of the input elements in the arr
// pos = {
//     element: [[position 1], [position 2]]
// }
map<int, vector<vector<int> > > pos;

// Count of the remaining number of the elements
// rem = {
//     element: pending count
// }
map<int, int> rem;

// Graph defining tentative positions of the elements to be
// filled graph = {
//     key: {
//         row1: [columns],
//         row2: [columns]
//     }
// }
map<int, map<int, vector<int> > > graph;

// Print the matrix array
void printMatrix()
{
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}

// Method to check if the inserted element is safe
bool is_safe(int x, int y)
{
  int key = arr[x][y];
  for (int i = 0; i < 9; i++) {
    if (i != y && arr[x][i] == key) {
      return false;
    }
    if (i != x && arr[i][y] == key) {
      return false;
    }
  }

  int r_start = floor(x / 3) * 3;
  int r_end = r_start + 3;

  int c_start = floor(y / 3) * 3;
  int c_end = c_start + 3;

  for (int i = r_start; i < r_end; i++) {
    for (int j = c_start; j < c_end; j++) {
      if (i != x && j != y && arr[i][j] == key) {
        return false;
      }
    }
  }
  return true;
}

// method to fill the matrix
// input keys: list of elements to be filled in the matrix
//        k   : index number of the element to be picked up
//        from keys rows: list of row index where element is
//        to be inserted r   : index number of the row to be
//        inserted
//
bool fill_matrix(int k, vector<int> keys, int r,
                 vector<int> rows)
{
  int c = 0;
  arr[rows[r]][c] = keys[k];
  if (is_safe(rows[r], c)) {
    if (r < rows.size() - 1) {
      if (fill_matrix(k, keys, r + 1, rows)) {
        return true;
      }
      else {
        arr[rows[r]][c] = 0;
      }
    }
    else {
      if (k < keys.size() - 1) {
        if (fill_matrix(
          k + 1, keys, 0,
          rows)) {
          return true;
        }
        else {
          arr[rows[r]][c] = 0;

        }
      }
      return true;
    }
  }
  arr[rows[r]][c] = 0;

  return false;
}

// Fill the pos and rem dictionary. It will be used to build
// graph
void build_pos_and_rem()
{
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (arr[i][j] > 0) {
        if (!pos.count(arr[i][j])) {
          pos[arr[i][j]] = {};
        }
        pos[arr[i][j]].push_back({ i, j });
        if (!rem.count(arr[i][j])) {
          rem[arr[i][j]] = 9;
        }
        rem[arr[i][j]] -= 1;
      }
    }
  }

  // Fill the elements not present in input matrix.
  // Example: 1 is missing in input matrix
  for (int i = 1; i < 10; i++) {
    if (!pos.count(i)) {
      pos[i] = {};
    }
    if (!rem.count(i)) {
      rem[i] = 9;
    }
  }
}

int main() { printMatrix(); }

// This code is contributed by ishankhandelwals.

/*
Problema 3 - Colorizacao de grafo

M-Coloring Problem
Last Updated : 10 Oct, 2023
Given an undirected graph and a number m, the task is to color the given graph with at most m colors such that no two adjacent vertices of the graph are colored with the same color

Note: Here coloring of a graph means the assignment of colors to all vertices

Input:  graph = {0, 1, 1, 1},
                         {1, 0, 1, 0},
                         {1, 1, 0, 1},
                         {1, 0, 1, 0}
Output: Solution Exists: Following are the assigned colors: 1  2  3  2
Explanation: By coloring the vertices with following colors, 
                      adjacent vertices does not have same colors


Input: graph = {1, 1, 1, 1},
                         {1, 1, 1, 1},
                         {1, 1, 1, 1},
                         {1, 1, 1, 1}


Output: Solution does not exist
Explanation: No solution exits 


*/

//solução pela abordagem de backtraking

// C++ program for solution of M
// Coloring problem using backtracking

#include <bits/stdc++.h>
using namespace std;

// Number of vertices in the graph
#define V 4

void printSolution(int color[]);

/* A utility function to check if
the current color assignment
is safe for vertex v i.e. checks
whether the edge exists or not
(i.e, graph[v][i]==1). If exist
then checks whether the color to
be filled in the new vertex(c is
sent in the parameter) is already
used by its adjacent
vertices(i-->adj vertices) or
not (i.e, color[i]==c) */
bool isSafe(int v, bool graph[V][V], int color[], int c)
{
	for (int i = 0; i < V; i++)
		if (graph[v][i] && c == color[i])
			return false;

	return true;
}

/* A recursive utility function
to solve m coloring problem */
bool graphColoringUtil(bool graph[V][V], int m, int color[],
					int v)
{

	/* base case: If all vertices are
	assigned a color then return true */
	if (v == V)
		return true;

	/* Consider this vertex v and
	try different colors */
	for (int c = 1; c <= m; c++) {

		/* Check if assignment of color
		c to v is fine*/
		if (isSafe(v, graph, color, c)) {
			color[v] = c;

			/* recur to assign colors to
			rest of the vertices */
			if (graphColoringUtil(graph, m, color, v + 1)
				== true)
				return true;

			/* If assigning color c doesn't
			lead to a solution then remove it */
			color[v] = 0;
		}
	}

	/* If no color can be assigned to
	this vertex then return false */
	return false;
}

/* This function solves the m Coloring
problem using Backtracking. It mainly
uses graphColoringUtil() to solve the
problem. It returns false if the m
colors cannot be assigned, otherwise
return true and prints assignments of
colors to all vertices. Please note
that there may be more than one solutions,
this function prints one of the
feasible solutions.*/
bool graphColoring(bool graph[V][V], int m)
{

	// Initialize all color values as 0.
	// This initialization is needed
	// correct functioning of isSafe()
	int color[V];
	for (int i = 0; i < V; i++)
		color[i] = 0;

	// Call graphColoringUtil() for vertex 0
	if (graphColoringUtil(graph, m, color, 0) == false) {
		cout << "Solution does not exist";
		return false;
	}

	// Print the solution
	printSolution(color);
	return true;
}

/* A utility function to print solution */
void printSolution(int color[])
{
	cout << "Solution Exists:"
		<< " Following are the assigned colors"
		<< "\n";
	for (int i = 0; i < V; i++)
		cout << " " << color[i] << " ";

	cout << "\n";
}

// Driver code
int main()
{

	/* Create following graph and test
	whether it is 3 colorable
	(3)---(2)
	| / |
	| / |
	| / |
	(0)---(1)
	*/
	bool graph[V][V] = {
		{ 0, 1, 1, 1 },
		{ 1, 0, 1, 0 },
		{ 1, 1, 0, 1 },
		{ 1, 0, 1, 0 },
	};

	// Number of colors
	int m = 3;

	// Function call
	graphColoring(graph, m);
	return 0;
}

// This code is contributed by Shivani


