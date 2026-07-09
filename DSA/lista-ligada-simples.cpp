#include <bits/stdc++.h>
using namespace std;

struct Node {

    int data;
    Node* next;

    Node(int new_data) {
        data = new_data;
        next = nullptr; 
    }
};

// Function to insert a new node at the beginning of the
// list
Node* insertAtFront(Node* head, int new_data) {
  
    // Create a new node with the given data
    Node* new_node = new Node(new_data);

    // Make the next of the new node point to the current
    // head
    new_node->next = head;

    // Return the new node as the new head of the list
    return new_node;
}

void printList(Node* head) {
  
    // Start from the head of the list
    Node* curr = head;

    // Traverse the list
    while (curr != nullptr) {
      
        // Print the current node's data
        cout << " " << curr->data;

        // Move to the next node
        curr = curr->next;
    }

    // Print a newline at the end
    cout << endl;
}

int main() {
  
    // Create the linked list 2->3->4->5
    Node* head = new Node(2);
    head->next = new Node(3);
    head->next->next = new Node(4);
    head->next->next->next = new Node(5);

    int data = 1;
    head = insertAtFront(head, data);
    printList(head);

    return 0;
}


// C++ Program to Insert a Node after a Given Node in Linked
// List
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Function to insert a new node after a given node
Node* insertAfter(Node* head, int key, int newData) {
  
    // Initilize curr Pointer to head
    Node* curr = head;

    // Iterate over Linked List to find the key
    while (curr != nullptr) {
        if (curr->data == key)
            break;
        curr = curr->next;
    }

    // if curr becomes NULL means, given key is not
    // found in linked list
    if (curr == nullptr)
        return head;

    // Allocate new node by given data and point
    // the next of newNode to curr's next &
    // point current next to newNode
    Node* newNode = new Node(newData);
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

void printList(Node* node) {
  
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
  
    // Create the linked list 2->3->4->5
    Node* head = new Node(2);
    head->next = new Node(3);
    head->next->next = new Node(5);
    head->next->next->next = new Node(6);

    int key = 3, newData = 4;

    head = insertAfter(head, key, newData);

    printList(head);

    return 0;
}



// C++ Implementation to insert a node before
// a given key using iteratinon
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};

// Iterative function to insert a new node with value 
// newData before the node with the given key
Node* insertBeforeKey(Node* head, int key, int newData) {

    // If the list is empty
    if (head == nullptr) {
        return nullptr;
    }

    // Special case: if the key is at the head
    if (head->data == key) {
        Node* new_node = new Node(newData);
        new_node->next = head;
        return new_node;
    }

    // Initialize current and previous pointers
    Node* curr = head;
    Node* prev = nullptr;

    // Traverse the list to find the key
    while (curr != nullptr && curr->data != key) {
        prev = curr;
        curr = curr->next;
    }

    // If the key was found
    if (curr != nullptr) {
        Node* new_node = new Node(newData);
        prev->next = new_node;
        new_node->next = curr;
    }

    return head;
}

void printList(Node* node) {
    Node* curr = node;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {

    // Create a hard-coded linked list:
    // 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    int newData = 6;
    int key = 2;

    head = insertBeforeKey(head, key, newData);

    printList(head);

    return 0;
}



// C++ Program to Insert a Node At a Specific Position in
// Linked List
#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Function to insert a node at a specific position in the

// linked list.
Node* insertAtPosition(Node* head, int position, int data) {
    Node* newNode = new Node(data);

    // If inserting at the beginning
    if (position == 1) {
        newNode->next = head;
        head = newNode;
        return head;
    }

    Node* current = head;
  
    // Traverse the list to find the node before the
    // insertion point
    for (int i = 1; i < position - 1 && current != nullptr;
         ++i) {
        current = current->next;
    }

    // If the position is out of bounds
    if (current == nullptr) {
        cout << "Position is out of bounds." << endl;
      
        // Deallocate memory to prevent
        delete newNode; 
                       
        return head;
    }

    // Insert the new node at the specified position
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Function to print the linked list.
void printList(Node* head) {
    while (head != nullptr) {
        cout << " " << head->data;
        head = head->next;
    }
    cout << endl;
}

int main() {
  
    // Creating the list 3->5->8->10
    Node* head = new Node(3);
    head->next = new Node(5);
    head->next->next = new Node(8);
    head->next->next->next = new Node(10);

    int data = 12, pos = 2;
    head = insertAtPosition(head, pos, data);
 
    printList(head);

    return 0;
}


// C++ Program to Insert a Node at the End of Linked List
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int new_data) {
        data = new_data;
        next = nullptr;
    }
};

// Function appends a new node at the end and returns the
// head.
Node* insertAtEnd(Node* head, int new_data) {
  
    // Create a new node
    Node* new_node = new Node(new_data);

    // If the Linked List is empty, make
    // the new node as the head and return
    if (head == nullptr) {
        return new_node;
    }

    // Store the head reference in a temporary variable
    Node* last = head;

    // Traverse till the last node
    while (last->next != nullptr) {
        last = last->next;
    }

    // Change the next pointer of the last node
    // to point to the new node
    last->next = new_node;

    // Return the head of the list
    return head;
}

void printList(Node* node)
{
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->next;
    }
}

int main()
{
    // Create a linked list: 2->3->4->5->6
    Node* head = new Node(2);
    head->next = new Node(3);
    head->next->next = new Node(4);
    head->next->next->next = new Node(5);
    head->next->next->next->next = new Node(6);

    // Example of appending a node at the end
    head = insertAtEnd(head, 1);

    printList(head);

    return 0;
}



// C++ program to delete a node
// from the beginning of given linked list
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value){
        data = value;
        next = nullptr;
    }
};

// Function to delete the head node
Node* deleteHead(Node* head)
{
    // Base case if linked list is empty
    if (head == nullptr)
        return nullptr;
  
    // Change the head pointer to the next node
    // and free the original head 
    Node* temp = head;
    head = head->next;
    delete temp;
  
    // Return the new head
    return head;
}

void printList(Node* head)
{
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

int main()
{
    // Creating a linked list
    // 1 -> 2 -> 3 -> 4 -> 5 -> nullptr
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    cout << "Original list: ";
    printList(head);
    // Deleting the head node
    head = deleteHead(head);
    cout << "List after deleting the head: ";
    printList(head);

    return 0;
}


// C++ code for the deleting a node from end
// in two traversal
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    struct Node* next;
    Node(int value)
    {
        this->data = value;
        this->next = NULL;
    }
};

int length(Node* head)
{
    Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void printList(Node* head)
{
    Node* ptr = head;
    while (ptr != NULL) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

Node* deleteNthNodeFromEnd(Node* head, int n)
{
    int Length = length(head);
    int nodeFromBeginning = Length - n + 1;
    Node* prev = NULL;
    Node* temp = head;
    for (int i = 1; i < nodeFromBeginning; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL) {
        head = head->next;
        return head;
    }
    else {
        prev->next = prev->next->next;
        return head;
    }
}

int main()
{
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    cout<<"Linked List before Deletion:"<<endl;
    printList(head);

    head = deleteNthNodeFromEnd(head, 4);

      cout<<"Linked List after Deletion: "<<endl;
    printList(head);
    return 0;
}

// This code is contributed by Yash Agarwal(yashagarwal2852002)


// C++ program to delete a linked list node at a given
// position
#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;
    Node(int data)
        : data(data)
        , next(nullptr)
    {
    }
};

// Function to delete a node at a given position
Node* deleteNode(Node* head, int position)
{
    // previous of node to be deleted
    Node* prev;
    Node* temp = head;

    // Base case if linked list is empty
    if (temp == NULL)
        return head;

    // Case 1: Head is to be deleted
    if (position == 1) {
        // make next node as head and free old head
        head = temp->next;
        free(temp);
        return head;
    }

    // Case 2: Node to be deleted is in middle
    // Traverse till given position
    for (int i = 1; i != position; i++) {
        prev = temp;
        temp = temp->next;
    }

    // If given position is found, delete node
    if (temp != NULL) {
        prev->next = temp->next;
        free(temp);
    }
    // If given position is not present
    else {
        cout << "Data not present\n";
    }

    return head;
}

void printList(Node* head)
{
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

// Driver code
int main()
{
    // Creating a static linked list
    // 1 -> 2 -> 3 -> 4 -> 5 -> nullptr
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    cout << "Original list: ";
    printList(head);

    // Deleting node at position 2
    int position = 2;
    head = deleteNode(head, position);

    cout << "List after deletion : ";
    printList(head);

    // Cleanup remaining nodes
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}



#include <iostream>

using namespace std;

// A linked list node
class Node {
public:
    int data;
    Node* next;

    // Constructor to initialize a new node with data
    Node(int new_data) {
        this->data = new_data;
        this->next = nullptr;
    }
};

// Function to traverse and print the singly linked list
void traverseList(Node* head) {

    // A loop that runs till head is nullptr
    while (head != nullptr) {

        // Printing data of current node
        cout << head->data << " ";

        // Moving to the next node
        head = head->next;
    }
    cout << endl;
}

// Driver Code
int main() {
  
    // Create a hard-coded linked list:
    // 10 -> 20 -> 30 -> 40
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);

    // Example of traversing the node and printing
    traverseList(head);

    return 0;
}

// This code is contributed by Utkasrh

