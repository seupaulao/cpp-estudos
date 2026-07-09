//grafo matriz adjacencia

// C++ program to demonstrate Adjacency Matrix
// representation of undirected and unweighted graph
#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<vector<int>> &mat, int i, int j)
{
    mat[i][j] = 1;
    mat[j][i] = 1; // Since the graph is undirected
}

void displayMatrix(vector<vector<int>> &mat)
{
    int V = mat.size();
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

int main()
{

    // Create a graph with 4 vertices and no edges
    // Note that all values are initialized as 0
    int V = 4;
    vector<vector<int>> mat(V, vector<int>(V, 0));

    // Now add edges one by one
    addEdge(mat, 0, 1);
    addEdge(mat, 0, 2);
    addEdge(mat, 1, 2);
    addEdge(mat, 2, 3);

    /* Alternatively we can also create using below
       code if we know all edges in advacem

     vector<vector<int>> mat = {{ 0, 1, 0, 0 },
                               { 1, 0, 1, 0 },
                               { 0, 1, 0, 1 },
                               { 0, 0, 1, 0 } }; */

    cout << "Adjacency Matrix Representation" << endl;
    displayMatrix(mat);

    return 0;
}


// grafo lista de adjacencia

#include <iostream>
#include <vector>
using namespace std;

// Function to add an edge between two vertices
void addEdge(vector<vector<int>>& adj, int i, int j) {
    adj[i].push_back(j);
    adj[j].push_back(i); // Undirected
}

// Function to display the adjacency list
void displayAdjList(const vector<vector<int>>& adj) {
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": "; // Print the vertex
        for (int j : adj[i]) {
            cout << j << " "; // Print its adjacent
        }
        cout << endl; 
    }
}

// Main function
int main() {
    // Create a graph with 4 vertices and no edges
    int V = 4;
    vector<vector<int>> adj(V); 

    // Now add edges one by one
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);

    cout << "Adjacency List Representation:" << endl;
    displayAdjList(adj);

    return 0;
}



//adicionar e remover vertices da lista de adjacencia

#include <iostream>

using namespace std;

// Node to store adjacency list
class AdjNode {
public:
    int vertex;
    AdjNode* next;
    AdjNode(int data)
    {
        vertex = data;
        next = NULL;
    }
};

// Adjacency List representation
class AdjList {
private:
    int v;
    AdjNode** graph;

public:
    AdjList(int vertices)
    {
        v = vertices;
        graph = new AdjNode*[v];
        for (int i = 0; i < v; ++i)
            graph[i] = NULL;
    }

    // Function to add an edge from a source vertex
    // to a destination vertex
    void addEdge(int source, int destination)
    {
        AdjNode* node = new AdjNode(destination);
        node->next = graph[source];
        graph[source] = node;
    }

    // Function to add a vertex between two vertices
    void addVertex(int vk, int source, int destination)
    {
        addEdge(source, vk);
        addEdge(vk, destination);
    }

    // Function to print the graph
    void printGraph()
    {
        for (int i = 0; i < v; ++i) {
            cout << i << " ";
            AdjNode* temp = graph[i];
            while (temp != NULL) {
                cout << "-> " << temp->vertex << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    // Function to delete a vertex
    void delVertex(int k)
    {
        // Iterate through all the vertices of the graph
        for (int i = 0; i < v; ++i) {
            AdjNode* temp = graph[i];
            if (i == k) {
                graph[i] = temp->next;
                temp = graph[i];
            }
            // Delete the vertex using linked list concept
            while (temp != NULL) {
                if (temp->vertex == k) {
                    break;
                }
                AdjNode* prev = temp;
                temp = temp->next;
                if (temp == NULL) {
                    continue;
                }
                prev->next = temp->next;
                temp = NULL;
            }
        }
    }
};

int main()
{
    int V = 6;
    AdjList graph(V);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(3, 2);
    graph.addEdge(4, 3);

    cout << "Initial adjacency list" << endl;
    graph.printGraph();

    // Add vertex
    graph.addVertex(5, 3, 2);
    cout << "Adjacency list after adding vertex" << endl;
    graph.printGraph();

    // Delete vertex
    graph.delVertex(4);
    cout << "Adjacency list after deleting vertex" << endl;
    graph.printGraph();

    return 0;
}

// adicionar e remover vertices da matriz de adjacencia

class Graph {
private:
	// number of vertices
	int n;

	// adjacency matrix
	int g[10][10];

public:
	// constructor
	Graph(int x)
	{
		n = x;

		// initializing each element of the adjacency matrix to zero
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				g[i][j] = 0;
			}
		}
	}
};

void displayAdjacencyMatrix()
{
	cout << "\n\n Adjacency Matrix:";

	// displaying the 2D array
	for (int i = 0; i < n; ++i) {
		cout << "\n";
		for (int j = 0; j < n; ++j) {
			cout << " " << g[i][j];
		}
	}
}


void addEdge(int x, int y)
{

	// checks if the vertex exists in the graph
	if ((x >= n) || (y > n)) {
		cout << "Vertex does not exists!";
	}

	// checks if the vertex is connecting to itself
	if (x == y) {
		cout << "Same Vertex!";
	}
	else {
		// connecting the vertices
		g[y][x] = 1;
		g[x][y] = 1;
	}
}


void addVertex()
{
	// increasing the number of vertices
	n++;
	int i;

	// initializing the new elements to 0
	for (i = 0; i < n; ++i) {
		g[i][n - 1] = 0;
		g[n - 1][i] = 0;
	}
}


void removeVertex(int x)
{
	// checking if the vertex is present
	if (x > n) {
		cout << "\nVertex not present!";
		return;
	}
	else {
		int i;

		// removing the vertex
		while (x < n) {
			// shifting the rows to left side
			for (i = 0; i < n; ++i) {
				g[i][x] = g[i][x + 1];
			}

			// shifting the columns upwards
			for (i = 0; i < n; ++i) {
				g[x][i] = g[x + 1][i];
			}
			x++;
		}

		// decreasing the number of vertices
		n--;
	}
}


int main()
{
    // creating objects of class Graph
    Graph obj(4);
 
    // calling methods
    obj.addEdge(0, 1);
    obj.addEdge(0, 2);
    obj.addEdge(1, 2);
    obj.addEdge(2, 3);
    // the adjacency matrix created
    obj.displayAdjacencyMatrix();
 
    // adding a vertex to the graph
    obj.addVertex();
    // connecting that vertex to other existing vertices
    obj.addEdge(4, 1);
    obj.addEdge(4, 3);
    // the adjacency matrix with a new vertex
    obj.displayAdjacencyMatrix();
 
    // removing an existing vertex in the graph
    obj.removeVertex(1);
    // the adjacency matrix after removing a vertex
    obj.displayAdjacencyMatrix();
 
    return 0;
}

// Adicionar e remover aresta na representação da lista de adjacências de um gráfico

// C++ implementation of the above approach

#include <bits/stdc++.h>
using namespace std;

// A utility function to add an edge in an
// undirected graph.
void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

// A utility function to delete an edge in an
// undirected graph.
void delEdge(vector<int> adj[], int u, int v)
{
	// Traversing through the first vector list
	// and removing the second element from it
	for (int i = 0; i < adj[u].size(); i++) {
		if (adj[u][i] == v) {
			adj[u].erase(adj[u].begin() + i);
			break;
		}
	}

	// Traversing through the second vector list
	// and removing the first element from it
	for (int i = 0; i < adj[v].size(); i++) {
		if (adj[v][i] == u) {
			adj[v].erase(adj[v].begin() + i);
			break;
		}
	}
}

// A utility function to print the adjacency list
// representation of graph
void printGraph(vector<int> adj[], int V)
{
	for (int v = 0; v < V; ++v) {
		cout << "vertex " << v << " ";
		for (auto x : adj[v])
			cout << "-> " << x;
		printf("\n");
	}
	printf("\n");
}

// Driver code
int main()
{
	int V = 5;
	vector<int> adj[V];

	// Adding edge as shown in the example figure
	addEdge(adj, 0, 1);
	addEdge(adj, 0, 4);
	addEdge(adj, 1, 2);
	addEdge(adj, 1, 3);
	addEdge(adj, 1, 4);
	addEdge(adj, 2, 3);
	addEdge(adj, 3, 4);

	// Printing adjacency matrix
	printGraph(adj, V);

	// Deleting edge (1, 4)
	// as shown in the example figure
	delEdge(adj, 1, 4);

	// Printing adjacency matrix
	printGraph(adj, V);

	return 0;
}


// Add and Remove Arestas in Adjacency Matrix representation of a Graph

// C++ program to add and remove edge
// in the adjacency matrix of a graph

#include <iostream>
using namespace std;

class Graph {
private:
	// Number of vertices
	int n;

	// Adjacency matrix
	int g[10][10];

public:
	// Constructor
	Graph(int x)
	{
		n = x;

		// Initializing each element of the
		// adjacency matrix to zero
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				g[i][j] = 0;
			}
		}
	}

	// Function to display adjacency matrix
	void displayAdjacencyMatrix()
	{
		// Displaying the 2D matrix
		for (int i = 0; i < n; i++) {
			cout << "\n";
			for (int j = 0; j < n; j++) {
				cout << " " << g[i][j];
			}
		}
	}

	// Function to update adjacency
	// matrix for edge insertion
	void addEdge(int x, int y)
	{
		// Checks if the vertices
		// exist in the graph
		if ((x < 0) || (x >= n)) {
			cout << "Vertex" << x
				<< " does not exist!";
		}
		if ((y < 0) || (y >= n)) {
			cout << "Vertex" << y
				<< " does not exist!";
		}

		// Checks if it is a self edge
		if (x == y) {
			cout << "Same Vertex!";
		}

		else {
			// Insert edge
			g[y][x] = 1;
			g[x][y] = 1;
		}
	}

	// Function to update adjacency
	// matrix for edge removal
	void removeEdge(int x, int y)
	{
		// Checks if the vertices
		// exist in the graph
		if ((x < 0) || (x >= n)) {
			cout << "Vertex" << x
				<< " does not exist!";
		}
		if ((y < 0) || (y >= n)) {
			cout << "Vertex" << y
				<< " does not exist!";
		}

		// Checks if it is a self edge
		if (x == y) {
			cout << "Same Vertex!";
		}

		else {
			// Remove edge
			g[y][x] = 0;
			g[x][y] = 0;
		}
	}
};

// Driver Code
int main()
{
	int N = 6, X = 2, Y = 3;

	Graph obj(N);

	// Adding edges to the graph
	obj.addEdge(0, 1);
	obj.addEdge(0, 2);
	obj.addEdge(0, 3);
	obj.addEdge(0, 4);
	obj.addEdge(1, 3);
	obj.addEdge(2, 3);
	obj.addEdge(2, 4);
	obj.addEdge(2, 5);
	obj.addEdge(3, 5);

	cout << "Adjacency matrix after"
		<< " edge insertions:\n";
	obj.displayAdjacencyMatrix();

	obj.removeEdge(X, Y);

	cout << "\nAdjacency matrix after"
		<< " edge removal:\n";
	obj.displayAdjacencyMatrix();

	return 0;
}


