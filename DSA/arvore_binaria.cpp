// Use any below method to implement Nodes of binary tree

// 1: Using struct
struct Node {
    int data;
    Node* left, * right;

    Node(int key) {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};

// 2: Using class
class Node {
public:
    int data;
    Node* left, * right;

    Node(int key) {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};


#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *left, *right;
    Node(int d){
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

int main(){
    // Initilize and allocate memory for tree nodes
    Node* firstNode = new Node(2);
    Node* secondNode = new Node(3);
    Node* thirdNode = new Node(4);
    Node* fourthNode = new Node(5);

    // Connect binary tree nodes
    firstNode->left = secondNode;
    firstNode->right = thirdNode;
    secondNode->left = fourthNode;
    return 0;
}


/*

Terminologias em Árvore Binária
Nós: A parte fundamental de uma árvore binária, onde cada nó contém dados e link para dois nós filhos.
Raiz: O nó mais alto em uma árvore é conhecido como nó raiz. Ele não tem pai e serve como ponto de partida para todos os nós na árvore.
Nó Pai: Um nó que tem um ou mais nós filhos. Em uma árvore binária, cada nó pode ter no máximo dois filhos.
Nó Filho: Um nó que é descendente de outro nó (seu pai).
Nó Folha: Um nó que não tem filhos ou ambos os filhos são nulos.
Nó Interno: Um nó que tem pelo menos um filho. Isso inclui todos os nós, exceto os nós raiz e folha.
Profundidade de um Nó: O número de arestas de um nó específico para o nó raiz. A profundidade do nó raiz é zero.
Altura de uma Árvore Binária: O número de nós do nó folha mais profundo para o nó raiz.

Propriedades da Árvore Binária
O número máximo de nós no nível L de uma árvore binária é 2L
O número máximo de nós em uma árvore binária de altura H é 2H – 1
Número total de nós folha em uma árvore binária = número total de nós com 2 filhos + 1
Em uma Árvore Binária com N nós, a altura mínima possível ou o número mínimo de níveis é Log2(N+1)
Uma Árvore Binária com L folhas tem pelo menos | Log2L |+ 1 níveis
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left, * right;

    Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

// In-order DFS: Left, Root, Right
void inOrderDFS(Node* node) {
    if (node == nullptr) return;

    inOrderDFS(node->left);
    cout << node->data << " ";
    inOrderDFS(node->right);
}

// Pre-order DFS: Root, Left, Right
void preOrderDFS(Node* node) {
    if (node == nullptr) return;

    cout << node->data << " ";
    preOrderDFS(node->left);
    preOrderDFS(node->right);
}

// Post-order DFS: Left, Right, Root
void postOrderDFS(Node* node) {
    if (node == nullptr) return;

    postOrderDFS(node->left);
    postOrderDFS(node->right);
    cout << node->data << " ";
}

void BFS(Node* root) {

    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop(); 
        cout << node->data << " ";
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
        
    }
}

int main() {
    Node* root = new Node(2);
    root->left = new Node(3);
    root->right = new Node(4);
    root->left->left = new Node(5);

    cout << "In-order DFS: ";
    inOrderDFS(root);

    cout << "\nPre-order DFS: ";
    preOrderDFS(root);
   
    cout << "\nPost-order DFS: ";
    postOrderDFS(root);
  
    cout << "\nLevel order: ";
    BFS(root);

    return 0;
}


Node* insert(Node* root, int key) {
    // If the tree is empty, create the root node
    if (root == nullptr) {
        root = new Node(key);
        return root;
    }
    // Create a queue for level order traversal
    queue<Node*> q;
    q.push(root);

    // Do level order traversal until we find an empty place
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        // If left child is empty, insert the new node here
        if (temp->left == nullptr) {
            temp->left = new Node(key);
            break;
        } else {
            q.push(temp->left);
        }
        // If right child is empty, insert the new node here
        if (temp->right == nullptr) {
            temp->right = new Node(key);
            break;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}

void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Function to search for a value in the binary tree using DFS
bool searchDFS(Node *root, int value){
    // Base case: If the tree is empty or we've reached a leaf node
    if (root == nullptr) return false;

    // If the node's data is equal to the value we are searching for
    if (root->data == value) return true;

    // Recursively search in the left and right subtrees
    bool left_res = searchDFS(root->left, value);
    bool right_res = searchDFS(root->right, value);

    return left_res || right_res;
}

// Function to delete a node from the binary tree
Node* deleteNode(Node* root, int val) {
    if (root == nullptr) return nullptr; 
    // Use a queue to perform BFS
    queue<Node*> q;
    q.push(root);
    Node* target = nullptr;

    // Find the target node
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        // Check for current node is the target node to delete
        if (curr->data == val) {
            target = curr;
            break;
        }
        // Add children to the queue
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    // If target node is not found, return the original tree
    if (target == nullptr) return root;

    // Find the deepest rightmost node and its parent
    pair<Node*, Node*> last = {nullptr, nullptr};
    queue<pair<Node*, Node*>> q1;
    q1.push({root, nullptr});
  
    while (!q1.empty()) {
        auto curr = q1.front();
        q1.pop();

        // Update the last
        last = curr;
      
        if (curr.first->left) 
          q1.push({curr.first->left, curr.first});
        if (curr.first->right) 
          q1.push({curr.first->right, curr.first});
    }

    Node* lastNode = last.first;
    Node* lastParent = last.second;

    // Replace target's value with the last node's value
    target->data = lastNode->data;

    // Remove the last node
    if (lastParent) {
        if (lastParent->left==lastNode)lastParent->left = nullptr;
        else lastParent->right = nullptr;
        delete lastNode;
    } else {
        // If the last node was the root
        delete lastNode;
        return nullptr;
    }
    return root;  
}





