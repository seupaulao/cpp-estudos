/*
O que é o Algoritmo Guloso?
Um algoritmo guloso é uma técnica de resolução de problemas que faz a melhor escolha local em cada etapa na esperança de encontrar a solução ótima global. Ele prioriza benefícios imediatos em vez de consequências de longo prazo, tomando decisões com base na situação atual sem considerar implicações futuras. Embora essa abordagem possa ser eficiente e direta, ela não garante o melhor resultado geral para todos os problemas.

No entanto, é importante observar que nem todos os problemas são adequados para algoritmos gulosos. Eles funcionam melhor quando o problema exibe as seguintes propriedades:

Propriedade da Escolha Gulosa: A solução ótima pode ser construída fazendo a melhor escolha local em cada etapa.
Subestrutura Ótima: A solução ótima para o problema contém as soluções ótimas para seus subproblemas.
Características do Algoritmo Guloso
Aqui estão as características de um algoritmo guloso:

Algoritmos gulosos são simples e fáceis de implementar.
Eles são eficientes em termos de complexidade de tempo, geralmente fornecendo soluções rápidas.
Algoritmos gananciosos são usados ​​para problemas de otimização em que uma escolha localmente ótima leva a uma solução globalmente ótima.
Esses algoritmos não reconsideram escolhas anteriores, pois tomam decisões com base em informações atuais sem olhar para o futuro.
Algoritmos gananciosos são adequados para problemas de subestrutura ótima.
Essas características ajudam a definir a natureza e o uso de algoritmos gananciosos na resolução de problemas.

Exemplos de algoritmo ganancioso
Vários algoritmos bem conhecidos se enquadram na categoria de algoritmos gananciosos. Aqui estão alguns exemplos:

Algoritmo de Dijkstra: Este algoritmo encontra o caminho mais curto entre dois nós em um gráfico. Ele funciona escolhendo repetidamente a aresta mais curta disponível do nó atual.
Algoritmo de Kruskal: Este algoritmo encontra a árvore de abrangência mínima de um gráfico. Ele funciona escolhendo repetidamente a aresta com o peso mínimo que não cria um ciclo.
Problema da mochila fracionária: Este problema envolve selecionar itens com a maior relação valor-peso para encher uma mochila com capacidade limitada. O algoritmo ganancioso seleciona itens em ordem decrescente de sua relação valor-peso até que a mochila esteja cheia.
Agendamento e alocação de recursos: O algoritmo ganancioso pode ser usado para agendar trabalhos ou alocar recursos de forma eficiente.
Problema de troca de moeda: O algoritmo ganancioso pode ser usado para fazer troco para uma determinada quantia com o número mínimo de moedas, sempre escolhendo a moeda com o valor mais alto que seja menor que a quantia restante a ser trocada.
Codificação Huffman: O algoritmo ganancioso pode ser usado para gerar um código sem prefixo para compressão de dados, construindo uma árvore binária de forma que a frequência de cada caractere seja levada em consideração.
Por que usar a abordagem gananciosa?
Aqui estão alguns motivos pelos quais você pode usar a abordagem gananciosa:

Simples e fácil de entender: A abordagem gananciosa é direta e fácil de implementar, o que a torna uma boa escolha para iniciantes.
Rápido e eficiente: Geralmente encontra uma solução rapidamente, o que a torna adequada para problemas em que o tempo é uma restrição.
Fornece uma solução boa o suficiente: embora nem sempre seja ótima, a Abordagem Gulosa frequentemente encontra uma solução que está próxima da melhor solução possível.
Pode ser usada como um bloco de construção para outros algoritmos: a Abordagem Gulosa pode ser usada como um ponto de partida para desenvolver algoritmos mais complexos.
Útil para uma variedade de problemas: a Abordagem Gulosa pode ser aplicada a uma ampla gama de problemas de otimização, incluindo problemas de mochila, problemas de programação e problemas de roteamento.
No entanto, é importante lembrar que a Abordagem Gulosa nem sempre encontra a solução ótima. Há casos em que ela pode levar a soluções subótimas. Portanto, é necessário considerar cuidadosamente o problema e as desvantagens potenciais antes de usar a Abordagem Gulosa.
*/

/*
Problema 1 - Huffman Coding

A codificação Huffman é um algoritmo de compressão de dados sem perdas. A ideia é atribuir códigos de comprimento variável aos caracteres de entrada, os comprimentos dos códigos atribuídos são baseados nas frequências dos caracteres correspondentes.
Os códigos de comprimento variável atribuídos aos caracteres de entrada são Códigos de Prefixo, significa que os códigos (sequências de bits) são atribuídos de tal forma que o código atribuído a um caractere não é o prefixo do código atribuído a qualquer outro caractere. É assim que a codificação Huffman garante que não haja ambiguidade ao decodificar o fluxo de bits gerado.
Vamos entender os códigos de prefixo com um contraexemplo. Sejam quatro caracteres a, b, c e d, e seus códigos de comprimento variável correspondentes sejam 00, 01, 0 e 1. Essa codificação leva à ambiguidade porque o código atribuído a c é o prefixo dos códigos atribuídos a a e b. Se o fluxo de bits compactado for 0001, a saída descompactada pode ser “cccd” ou “ccb” ou “acd” ou “ab”.
Veja isso para aplicações da codificação Huffman.
Existem principalmente duas partes principais na codificação de Huffman

Construa uma árvore de Huffman a partir de caracteres de entrada.
Atravesse a árvore de Huffman e atribua códigos aos caracteres.


*/

// C++ program for Huffman Coding 
#include <cstdlib> 
#include <iostream> 
using namespace std; 

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 

// A Huffman tree node 
struct MinHeapNode { 

	// One of the input characters 
	char data; 

	// Frequency of the character 
	unsigned freq; 

	// Left and right child of this node 
	struct MinHeapNode *left, *right; 
}; 

// A Min Heap: Collection of 
// min-heap (or Huffman tree) nodes 
struct MinHeap { 

	// Current size of min heap 
	unsigned size; 

	// capacity of min heap 
	unsigned capacity; 

	// Array of minheap node pointers 
	struct MinHeapNode** array; 
}; 

// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc( 
		sizeof(struct MinHeapNode)); 

	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

// A utility function to create 
// a min heap of given capacity 
struct MinHeap* createMinHeap(unsigned capacity) 

{ 

	struct MinHeap* minHeap 
		= (struct MinHeap*)malloc(sizeof(struct MinHeap)); 

	// current size is 0 
	minHeap->size = 0; 

	minHeap->capacity = capacity; 

	minHeap->array = (struct MinHeapNode**)malloc( 
		minHeap->capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

// A utility function to 
// swap two min heap nodes 
void swapMinHeapNode(struct MinHeapNode** a, 
					struct MinHeapNode** b) 

{ 

	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// The standard minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int idx) 

{ 

	int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 

	if (left < minHeap->size 
		&& minHeap->array[left]->freq 
			< minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size 
		&& minHeap->array[right]->freq 
			< minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != idx) { 
		swapMinHeapNode(&minHeap->array[smallest], 
						&minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
} 

// A utility function to check 
// if size of heap is 1 or not 
int isSizeOne(struct MinHeap* minHeap) 
{ 

	return (minHeap->size == 1); 
} 

// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 

{ 

	struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] = minHeap->array[minHeap->size - 1]; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return temp; 
} 

// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, 
				struct MinHeapNode* minHeapNode) 

{ 

	++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i 
		&& minHeapNode->freq 
				< minHeap->array[(i - 1) / 2]->freq) { 

		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 

// A standard function to build min heap 
void buildMinHeap(struct MinHeap* minHeap) 

{ 

	int n = minHeap->size - 1; 
	int i; 

	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 

// A utility function to print an array of size n 
void printArr(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; ++i) 
		cout << arr[i]; 

	cout << "\n"; 
} 

// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root) 

{ 

	return !(root->left) && !(root->right); 
} 

// Creates a min heap of capacity 
// equal to size and inserts all character of 
// data[] in min heap. Initially size of 
// min heap is equal to capacity 
struct MinHeap* createAndBuildMinHeap(char data[], 
									int freq[], int size) 

{ 

	struct MinHeap* minHeap = createMinHeap(size); 

	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[i]); 

	minHeap->size = size; 
	buildMinHeap(minHeap); 

	return minHeap; 
} 

// The main function that builds Huffman tree 
struct MinHeapNode* buildHuffmanTree(char data[], 
									int freq[], int size) 

{ 
	struct MinHeapNode *left, *right, *top; 

	// Step 1: Create a min heap of capacity 
	// equal to size. Initially, there are 
	// modes equal to size. 
	struct MinHeap* minHeap 
		= createAndBuildMinHeap(data, freq, size); 

	// Iterate while size of heap doesn't become 1 
	while (!isSizeOne(minHeap)) { 

		// Step 2: Extract the two minimum 
		// freq items from min heap 
		left = extractMin(minHeap); 
		right = extractMin(minHeap); 

		// Step 3: Create a new internal 
		// node with frequency equal to the 
		// sum of the two nodes frequencies. 
		// Make the two extracted node as 
		// left and right children of this new node. 
		// Add this node to the min heap 
		// '$' is a special value for internal nodes, not 
		// used 
		top = newNode('$', left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 

	// Step 4: The remaining node is the 
	// root node and the tree is complete. 
	return extractMin(minHeap); 
} 

// Prints huffman codes from the root of Huffman Tree. 
// It uses arr[] to store codes 
void printCodes(struct MinHeapNode* root, int arr[], 
				int top) 

{ 

	// Assign 0 to left edge and recur 
	if (root->left) { 

		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 

	// Assign 1 to right edge and recur 
	if (root->right) { 

		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 

	// If this is a leaf node, then 
	// it contains one of the input 
	// characters, print the character 
	// and its code from arr[] 
	if (isLeaf(root)) { 

		cout << root->data << ": "; 
		printArr(arr, top); 
	} 
} 

// The main function that builds a 
// Huffman Tree and print codes by traversing 
// the built Huffman Tree 
void HuffmanCodes(char data[], int freq[], int size) 

{ 
	// Construct Huffman Tree 
	struct MinHeapNode* root 
		= buildHuffmanTree(data, freq, size); 

	// Print Huffman codes using 
	// the Huffman tree built above 
	int arr[MAX_TREE_HT], top = 0; 

	printCodes(root, arr, top); 
} 

// Driver code 
int main() 
{ 

	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
	int freq[] = { 5, 9, 12, 13, 16, 45 }; 

	int size = sizeof(arr) / sizeof(arr[0]); 

	HuffmanCodes(arr, freq, size); 

	return 0; 
}

/* problema 2 
How to find Shortest Paths from Source to all Vertices using Dijkstra’s Algorithm

 Input:  src = 0, the graph is shown below. 


1-(2)
 Output:  0 4 12 19 21 11 9 8 14 
 Explanation:  The distance from 0 to 1 = 4. 
 The minimum distance from 0 to 2 = 12. 0->1->2 
 The minimum distance from 0 to 3 = 19. 0->1->2->3 
 The minimum distance from 0 to 4 = 21. 0->7->6->5->4 
 The minimum distance from 0 to 5 = 11. 0->7->6->5 
 The minimum distance from 0 to 6 = 9. 0->7->6 
 The minimum distance from 0 to 7 = 8. 0->7 
 The minimum distance from 0 to 8 = 14. 0->1->2->8 */
 
 // C++ program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph
#include <iostream>
using namespace std;
#include <limits.h>

// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist);
}

// driver's code
int main()
{

    /* Let us create the example graph discussed above */
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    // Function call
    dijkstra(graph, 0);

    return 0;
}

// This code is contributed by shivanisinghss2110


/*
Problema 3

Job Sequencing Problem
Last Updated : 23 Feb, 2023
Given an array of jobs where every job has a deadline and associated profit if the job is finished before the deadline. It is also given that every job takes a single unit of time, so the minimum possible deadline for any job is 1. Maximize the total profit if only one job can be scheduled at a time.

Examples: 


Input: Four Jobs with following deadlines and profits


JobID  Deadline  Profit


  a           4          20   
  b           1          10
  c           1          40  
  d          1          30


Output: Following is maximum profit sequence of jobs: c, a   


Input:  Five Jobs with following deadlines and profits


JobID   Deadline  Profit


  a            2          100
  b            1          19
  c            2          27
 d            1          25
 e            3          15


Output: Following is maximum profit sequence of jobs: c, a, e

*/
// C++ code for the above approach

#include <algorithm>
#include <iostream>
using namespace std;

// A structure to represent a job
struct Job {

	char id; // Job Id
	int dead; // Deadline of job
	int profit; // Profit if job is over before or on
				// deadline
};

// Comparator function for sorting jobs
bool comparison(Job a, Job b)
{
	return (a.profit > b.profit);
}

// Returns maximum profit from jobs
void printJobScheduling(Job arr[], int n)
{
	// Sort all jobs according to decreasing order of profit
	sort(arr, arr + n, comparison);

	int result[n]; // To store result (Sequence of jobs)
	bool slot[n]; // To keep track of free time slots

	// Initialize all slots to be free
	for (int i = 0; i < n; i++)
		slot[i] = false;

	// Iterate through all given jobs
	for (int i = 0; i < n; i++) {
		// Find a free slot for this job (Note that we start
		// from the last possible slot)
		for (int j = min(n, arr[i].dead) - 1; j >= 0; j--) {
			// Free slot found
			if (slot[j] == false) {
				result[j] = i; // Add this job to result
				slot[j] = true; // Make this slot occupied
				break;
			}
		}
	}

	// Print the result
	for (int i = 0; i < n; i++)
		if (slot[i])
			cout << arr[result[i]].id << " ";
}

// Driver's code
int main()
{
	Job arr[] = { { 'a', 2, 100 },
				{ 'b', 1, 19 },
				{ 'c', 2, 27 },
				{ 'd', 1, 25 },
				{ 'e', 3, 15 } };

	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Following is maximum profit sequence of jobs "
			"\n";

	// Function call
	printJobScheduling(arr, n);
	return 0;
}

// This code is contributed by Aditya Kumar (adityakumar129)

/*
Problema 4

Greedy Algorithm to find Minimum number of Coins
Last Updated : 21 Feb, 2023
Given a value of V Rs and an infinite supply of each of the denominations {1, 2, 5, 10, 20, 50, 100, 500, 1000} valued coins/notes, The task is to find the minimum number of coins and/or notes needed to make the change?

Examples:  


Input: V = 70
Output: 2
Explanation: We need a 50 Rs note and a 20 Rs note.


Input: V = 121
Output: 3
Explanation: We need a 100 Rs note, a 20 Rs note, and a 1 Rs coin.
*/

// C++ program to find minimum
// number of denominations
#include <bits/stdc++.h>
using namespace std;

// All denominations of Indian Currency
int denomination[]
	= { 1, 2, 5, 10, 20, 50, 100, 500, 1000 };
int n = sizeof(denomination) / sizeof(denomination[0]);

void findMin(int V)
{
	sort(denomination, denomination + n);

	// Initialize result
	vector<int> ans;

	// Traverse through all denomination
	for (int i = n - 1; i >= 0; i--) {

		// Find denominations
		while (V >= denomination[i]) {
			V -= denomination[i];
			ans.push_back(denomination[i]);
		}
	}

	// Print result
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}

// Driver Code
int main()
{
	int n = 93;
	cout << "Following is minimal"
		<< " number of change for " << n << ": ";

	// Function Call
	findMin(n);
	return 0;
}

/*
Problema 5
Graph Coloring Using Greedy Algorithm

Graph Coloring Using Greedy Algorithm:
* Color first vertex with first color. 
* Do following for remaining V-1 vertices. 
     * Consider the currently picked vertex and color it with the lowest numbered color that has not been used on any previously colored vertices adjacent to it. If all previously used colors appear on vertices adjacent to v, assign a new color to it.
*/

// A C++ program to implement greedy algorithm for graph coloring
#include <iostream>
#include <list>
using namespace std;

// A class that represents an undirected graph
class Graph
{
	int V; // No. of vertices
	list<int> *adj; // A dynamic array of adjacency lists
public:
	// Constructor and destructor
	Graph(int V) { this->V = V; adj = new list<int>[V]; }
	~Graph()	 { delete [] adj; }

	// function to add an edge to graph
	void addEdge(int v, int w);

	// Prints greedy coloring of the vertices
	void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v); // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
	int result[V];

	// Assign the first color to first vertex
	result[0] = 0;

	// Initialize remaining V-1 vertices as unassigned
	for (int u = 1; u < V; u++)
		result[u] = -1; // no color is assigned to u

	// A temporary array to store the available colors. True
	// value of available[cr] would mean that the color cr is
	// assigned to one of its adjacent vertices
	bool available[V];
	for (int cr = 0; cr < V; cr++)
		available[cr] = false;

	// Assign colors to remaining V-1 vertices
	for (int u = 1; u < V; u++)
	{
		// Process all adjacent vertices and flag their colors
		// as unavailable
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = true;

		// Find the first available color
		int cr;
		for (cr = 0; cr < V; cr++)
			if (available[cr] == false)
				break;

		result[u] = cr; // Assign the found color

		// Reset the values back to false for the next iteration
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = false;
	}

	// print the result
	for (int u = 0; u < V; u++)
		cout << "Vertex " << u << " ---> Color "
			<< result[u] << endl;
}

// Driver program to test above function
int main()
{
	Graph g1(5);
	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 2);
	g1.addEdge(1, 3);
	g1.addEdge(2, 3);
	g1.addEdge(3, 4);
	cout << "Coloring of graph 1 \n";
	g1.greedyColoring();

	Graph g2(5);
	g2.addEdge(0, 1);
	g2.addEdge(0, 2);
	g2.addEdge(1, 2);
	g2.addEdge(1, 4);
	g2.addEdge(2, 4);
	g2.addEdge(4, 3);
	cout << "\nColoring of graph 2 \n";
	g2.greedyColoring();

	return 0;
}


