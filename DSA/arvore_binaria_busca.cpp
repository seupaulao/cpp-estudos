#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int item) {
        key = item;
        left = right = NULL;
    }
};

// function to search a key in a BST
Node* search(Node* root, int key) {
  
    // Base Cases: root is null or key 
    // is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

// Driver Code
int main() {
  
    // Creating a hard coded tree for keeping 
    // the length of the code small. We need 
    // to make sure that BST properties are 
    // maintained if we try some other cases.
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);
  
    (search(root, 19) != NULL)? cout << "Found\n": 
                               cout << "Not Found\n";

  
    (search(root, 80) != NULL)? cout << "Found\n": 
                               cout << "Not Found\n";

    return 0;
}

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;    
    Node(int item) {
        key = item;
        left = NULL;
        right = NULL;
    }
};

// A utility function to insert a new node with 
// the given key
Node* insert(Node* node, int key) {
  
    // If the tree is empty, return a new node
    if (node == NULL) 
        return new Node(key);    
    
    // If the key is already present in the tree,
    // return the node
    if (node->key == key) 
        return node;
    
    // Otherwise, recur down the tree/ If the key
    // to be inserted is greater than the node's key,
    // insert it in the right subtree
    if (node->key < key) 
        node->right = insert(node->right, key);
    
    // If the key to be inserted is smaller than 
    // the node's key,insert it in the left subtree
    else 
        node->left = insert(node->left, key);
    
    // Return the (unchanged) node pointer
    return node;
}

// A utility function to do inorder tree traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Driver program to test the above functions
int main() {
    // Creating the following BST
    //      50
    //     /  \
    //    30   70
    //   / \   / \
    //  20 40 60 80

    Node* root = new Node(50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Print inorder traversal of the BST
    inorder(root);

    return 0;
}


//insercao usando a abordagem iteraativa

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int item)
    {
        key = item;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* root, int x)
{

    Node* temp = new Node(x);

    // If tree is empty
    if (root == NULL)
        return temp;

    // Find the node who is going
    // to have the new node temp as
    // it child. The parent node is
    // mainly going to be a leaf node
    Node *parent = NULL, *curr = root;
    while (curr != NULL) {
        parent = curr;
        if (curr->key > x)
            curr = curr->left;
        else if (curr->key < x)
            curr = curr->right;
        else
            return root;
    }

    // If x is smaller, make it
    // left child, else right child
    if (parent->key > x)
        parent->left = temp;
    else
        parent->right = temp;
    return root;
}

// A utility function to do inorder
// tree traversal
void inorder(Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Driver program
int main()
{
    // Creating the following BST
    //      50
    //     /  \
    //    30   70
    //   / \   / \
    //  20 40 60 80

    Node* root = new Node(50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Print inorder traversal of the BST
    inorder(root);

    return 0;
}


//remoção - forma recursiva

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k)
    {
        key = k;
        left = right = NULL;
    }
};

// Note that it is not a generic inorder
// successor function. It mainly works
// when right child is not empty which is 
// the case wwe need in BST delete
Node* getSuccessor(Node* curr)
{
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

// This function deletes a given key x from
// the give BST and returns modified root of
// the BST (if it is modified)
Node* delNode(Node* root, int x)
{

    // Base case
    if (root == NULL)
        return root;

    // If key to be searched is in a subtree
    if (root->key > x)
        root->left = delNode(root->left, x);
    else if (root->key < x)
        root->right = delNode(root->right, x);

    // If root matches with the given key
    else {

        // Cases when root has 0 children
        // or only right child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // When root has only left child
        if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // When both children are present
        Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->right = delNode(root->right, succ->key);
    }
    return root;
}

// Utility function to do inorder
// traversal
void inorder(Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Driver code
int main()
{
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->right->left = new Node(12);
    root->right->right = new Node(18);
    int x = 15;

    root = delNode(root, x);
    inorder(root);
    return 0;
}


//Travessia Inorder:
//Primeiro percorra a subárvore esquerda, depois visite a raiz e depois percorra a subárvore direita.

// C++ code to implement the approach

#include <bits/stdc++.h>
using namespace std;

// Class describing a node of tree
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int v)
    {
        this->data = v;
        this->left = this->right = NULL;
    }
};

// Inorder Traversal
void printInorder(Node* node)
{
    if (node == NULL)
        return;

    // Traverse left subtree
    printInorder(node->left);

    // Visit node
    cout << node->data << " ";

    // Traverse right subtree
    printInorder(node->right);
}

// Driver code
int main()
{
    // Build the tree
    Node* root = new Node(100);
    root->left = new Node(20);
    root->right = new Node(200);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(150);
    root->right->right = new Node(300);

    // Function call
    cout << "Inorder Traversal: ";
    printInorder(root);
    return 0;
}


// travessia pre-ordem

// C++ code to implement the approach

#include <bits/stdc++.h>
using namespace std;

// Class describing a node of tree
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int v)
    {
        this->data = v;
        this->left = this->right = NULL;
    }
};

// Preorder Traversal
void printPreOrder(Node* node)
{
    if (node == NULL)
        return;

    // Visit Node
    cout << node->data << " ";

    // Traverse left subtree
    printPreOrder(node->left);

    // Traverse right subtree
    printPreOrder(node->right);
}

// Driver code
int main()
{
    // Build the tree
    Node* root = new Node(100);
    root->left = new Node(20);
    root->right = new Node(200);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(150);
    root->right->right = new Node(300);

    // Function call
    cout << "Preorder Traversal: ";
    printPreOrder(root);
    return 0;
}


//travessia pos-ordem

// C++ code to implement the approach

#include <bits/stdc++.h>
using namespace std;

// Class to define structure of a node
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int v)
    {
        this->data = v;
        this->left = this->right = NULL;
    }
};

// PostOrder Traversal
void printPostOrder(Node* node)
{
    if (node == NULL)
        return;

    // Traverse left subtree
    printPostOrder(node->left);

    // Traverse right subtree
    printPostOrder(node->right);

    // Visit node
    cout << node->data << " ";
}

// Driver code
int main()
{
    Node* root = new Node(100);
    root->left = new Node(20);
    root->right = new Node(200);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(150);
    root->right->right = new Node(300);

    // Function call
    cout << "PostOrder Traversal: ";
    printPostOrder(root);
    cout << "\n";

    return 0;
}


//valor minimo

// C++ code to find minimum value in BST
// using inorder traversal
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Recursive function to solve and store elements 
// in a vector
void inorder(Node* root, vector<int>& sortedInorder) {
  
    // Base Case
    if (root == nullptr) return;

    // Traverse left subtree
    inorder(root->left, sortedInorder);

    // Store the current node's data
    sortedInorder.push_back(root->data);

    // Traverse right subtree
    inorder(root->right, sortedInorder);
}

// Function to find the minimum value in BST
int minValue(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    
    vector<int> sortedInorder;
    
    // Call the recursive inorder function
    inorder(root, sortedInorder);
    
    // Return the first element, which is the minimum
    return sortedInorder[0];
}

int main() {

    // Representation of input binary search tree
    //        5
    //       / \
    //      4   6
    //     /     \
    //    3       7
    //   / 
    //  1
    Node* root = new Node(5);
    root->left = new Node(4);
    root->right = new Node(6);
    root->left->left = new Node(3);
    root->right->right = new Node(7);
    root->left->left->left = new Node(1);

    cout << minValue(root) << "\n";

    return 0;
}


//piso da arvore binaria de busca

// C++ implementation to find floor of given 
// number x in BST
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;    
  
    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

// This function is used to find floor 
// of given number x
int floor(Node* root, int x) {
  
   // Base case: return -1 if no floor found
   if (root == nullptr) {
        return -1; 
    }

    // If the root's data is equal to x, 
    // we've found the floor
    if (root->data == x) {
        return root->data;
    }

    // If root's data is greater than x, 
    // search in the left subtree
    if (root->data > x) {
        return floor(root->left, x);
    }

    // Else, search in the right subtree 
    // and compare with current root
    int floorValue = floor(root->right, x);

    // If the right subtree returns 
    //a valid floor, return that
    // Otherwise, return the current root's data
    return (floorValue <= x && floorValue != -1)
                              ? floorValue : root->data;
}

int main() {
  
    // Representation of the given tree
    //       10
    //       / \
    //      5  15
    //         / \
    //        12 30 
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->right->left = new Node(12);
    root->right->right = new Node(30);

    int x = 14;
    cout << floor(root, x) << endl;
    return 0;
}


// piso da arvore binaria de busca - abordagem 2

// C++ implementation to find floor of given 
// number x in BST
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;    
  
    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

// This function is used to find floor 
// of given number x
int floor(Node* root, int x) {
  
    // Initialize variable to store the floor value
    int floorValue = -1;

    while (root != nullptr) {
      
        // If the root's data is equal to x, 
        // we've found the floor
        if (root->data == x) {
            return root->data;
        }

        // If root's data is greater than x, 
        // search in the left subtree
        if (root->data > x) {
            root = root->left;
        } 
        else {
          
            // Update floorValue and move to the 
            // right subtree
            floorValue = root->data;
            root = root->right;
        }
    }

    return floorValue;
}

int main() {
  
    // Representation of the given tree
    //       10
    //       / \
    //      5  15
    //         / \
    //        12 30 
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->right->left = new Node(12);
    root->right->right = new Node(30);

    int x = 14;
    cout << floor(root, x) << endl;
    return 0;
}

// Teto da bst - arvore binaria de busca

/*
A comparação produz três possibilidades,

A) Dados raiz são iguais à chave. Terminamos, dados raiz são valor ceil.

B) Dados raiz < valor chave, certamente o valor ceil não pode estar na subárvore esquerda.

Prossiga para a busca na subárvore direita como instância reduzida do problema.

C) Dados raiz > valor chave, o valor ceil pode estar na subárvore esquerda.

Podemos encontrar um nó com dados maiores que o valor chave na subárvore esquerda,

se não, a própria raiz será o nó ceil.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

// Function to find the ceiling of a given 
// input in BST. If the input is more than
// the max key in BST, return -1.
int findCeil(Node* root, int input) {
  
    // Base case
    if (root == nullptr)
        return -1;

    // We found equal key
    if (root->key == input)
        return root->key;

    // If root's key is smaller, 
    // ceil must be in the right subtree
    if (root->key < input)
        return findCeil(root->right, input);

    // Else, either left subtree or
    // root has the ceil value
    int ceil = findCeil(root->left, input);
    return (ceil >= input) ? ceil : root->key;
}

// Driver code
int main() {
    Node* root = new Node(8);
    root->left = new Node(4);
    root->right = new Node(12);
    root->left->left = new Node(2);
    root->left->right = new Node(6);
    root->right->left = new Node(10);
    root->right->right = new Node(14);

    // Testing for values from 0 to 15
    for (int i = 0; i < 16; i++)
        cout << i << " " << findCeil(root, i) << endl;

    return 0;
}


// teto - abordagem iterativa

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

// Helper function to find ceil of a given key in BST
int findCeil(Node* root, int key) {
  
    int ceil = -2; 

    while (root) {
      
        // If root itself is ceil
        if (root->data == key) {
            return root->data; 
        }
 
        // If root is smaller, the ceil
        // must be in the right subtree
        if (key > root->data) {
            root = root->right; 
        } 
      
        // Else either root can be ceil
        // or a node in the left child
        else {
            ceil = root->data; 
            root = root->left; 
        }
    }
    return ceil; 
}

// Driver code
int main() {
    Node* root = new Node(8);
    root->left = new Node(4);
    root->right = new Node(12);
    root->left->left = new Node(2);
    root->left->right = new Node(6);
    root->right->left = new Node(10);
    root->right->right = new Node(14);

    for (int i = 0; i < 16; i++)
        cout << findCeil(root, i) << "\n";

    return 0;
}


	
