#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int value){
        data = value;
        next = nullptr;
    }
};

// Function to insert a node into an empty circular singly linked list
Node *insertInEmptyList(Node *last, int data){
    if (last != nullptr) return last;
    
    // Create a new node
    Node *newNode = new Node(data);
  
    // Point newNode to itself
    newNode->next = newNode;
  
    // Update last to point to the new node
    last = newNode;
    return last;
}

void printList(Node* last){
    if(last == NULL) return;
  
    // Start from the head node
    Node* head = last->next;
    while (true) {
        cout << head->data << " ";
        head = head->next;
        if (head == last->next) break;
    }
    cout << endl;
}

int main(){
    Node *last = nullptr;

    // Insert a node into the empty list
    last = insertInEmptyList(last, 1);

    // Print the list
    cout << "List after insertion: ";
    printList(last);

    return 0;
}


#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

// Function to insert a node at the beginning of the
// circular linked list
Node* insertAtBeginning(Node* last, int value){
    // Allocate memory for the new node and set its data
    Node* newNode = new Node(value);

    // If the list is empty, make the new node point to
    // itself and set it as last
    if (last == nullptr) {
        newNode->next = newNode;
        return newNode;
    }

    // Insert the new node at the beginning
    newNode->next = last->next;
    last->next = newNode;

    return last;
}

void printList(Node* last){
  if(last == NULL) return;
  
    // Start from the head node
    Node* head = last->next;
    while (true) {
        cout << head->data << " ";
        head = head->next;
        if (head == last->next)
            break;
    }
    cout << endl;
}

int main(){

    // Create circular linked list: 2, 3, 4
    Node* first = new Node(2);
    first->next = new Node(3);
    first->next->next = new Node(4);

    Node* last = first->next->next;
    last->next = first;

    cout << "Original list: ";
    printList(last);

    // Insert 5 at the beginning
    last = insertAtBeginning(last, 5);

    cout << "List after inserting 5 at the beginning: ";
    printList(last);

    return 0;
}


#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

// Function to insert a node at the end of a circular linked list
Node *insertEnd(Node *tail, int value)
{
    Node *newNode = new Node(value);
    if (tail == nullptr){
        // If the list is empty, initialize it with the new node
        tail = newNode;

        // Point to itself to form a circular structure
        newNode->next = newNode;
    }
    else{
        // Insert new node after the current tail
        // and update the tail pointer.
        // New node points to the head node
        newNode->next = tail->next;

        // Tail node points to the new node
        tail->next = newNode;

        // Update tail to be the new node
        tail = newNode;
    }
    return tail;
}

void printList(Node *last){
  if(last == NULL) return;
  
    // Start from the head node
    Node *head = last->next;
    while (true){
        cout << head->data << " ";
        head = head->next;
        if (head == last->next)
            break;
    }
    cout << endl;
}

int main(){
    // Create circular linked list: 2, 3, 4
    Node *first = new Node(2);
    first->next = new Node(3);
    first->next->next = new Node(4);

    Node *last = first->next->next;
    last->next = first;

    cout << "Original list: ";
    printList(last);

    // Insert elements at the end of the circular linked list
    last = insertEnd(last, 5);
    last = insertEnd(last, 6);

    cout << "List after inserting 5 and 6: ";
    printList(last);

    return 0;
}



#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int value){
        data = value;
        next = nullptr;
    }
};

// Function to insert a node at a specific position in a circular linked list
Node *insertAtPosition(Node *last, int data, int pos){
    if (last == nullptr){
        // If the list is empty
        if (pos != 1){
            cout << "Invalid position!" << endl;
            return last;
        }
        // Create a new node and make it point to itself
        Node *newNode = new Node(data);
        last = newNode;
        last->next = last;
        return last;
    }

    // Create a new node with the given data
    Node *newNode = new Node(data);

    // curr will point to head initially
    Node *curr = last->next;

    if (pos == 1){
        // Insert at the beginning
        newNode->next = curr;
        last->next = newNode;
        return last;
    }

    // Traverse the list to find the insertion point
    for (int i = 1; i < pos - 1; ++i) {
        curr = curr->next;
      
        // If position is out of bounds
        if (curr == last->next){
            cout << "Invalid position!" << endl;
            return last;
        }
    }
    // Insert the new node at the desired position
    newNode->next = curr->next;
    curr->next = newNode;

    // Update last if the new node is inserted at the end
    if (curr == last) last = newNode;

    return last;
}

void printList(Node *last){
    if (last == NULL) return;

    Node *head = last->next;
    while (true){
        cout << head->data << " ";
        head = head->next;
        if (head == last->next) break;
    }
    cout << endl;
}

int main(){
    // Create circular linked list: 2, 3, 4
    Node *first = new Node(2);
    first->next = new Node(3);
    first->next->next = new Node(4);

    Node *last = first->next->next;
    last->next = first;

    cout << "Original list: ";
    printList(last);

    // Insert elements at specific positions
    int data = 5, pos = 2;
    last = insertAtPosition(last, data, pos);
    cout << "List after insertions: ";
    printList(last);

    return 0;
}



// Function to delete First node of
// Circular Linked List
void DeleteFirst(struct Node** head)
{
	struct Node *previous = *head, *firstNode = *head;

	// check if list doesn't have any node
	// if not then return
	if (*head == NULL) {
		printf("\nList is empty\n");
		return;
	}

	// check if list have single node
	// if yes then delete it and return
	if (previous->next == previous) {
		*head = NULL;
		return;
	}

	// traverse second node to first
	while (previous->next != *head) {

		previous = previous->next;
	}

	// now previous is last node and
	// first node(firstNode) link address
	// put in last node(previous) link
	previous->next = firstNode->next;

	// make second node as head node
	*head = previous->next;
	free(firstNode);
	return;
}


// Function delete last node of
// Circular Linked List
void DeleteLast(struct Node** head)
{
	struct Node *current = *head, *temp = *head, *previous;

	// check if list doesn't have any node
	// if not then return
	if (*head == NULL) {
		printf("\nList is empty\n");
		return;
	}

	// check if list have single node
	// if yes then delete it and return
	if (current->next == current) {
		*head = NULL;
		return;
	}

	// move first node to last
	// previous
	while (current->next != *head) {
		previous = current;
		current = current->next;
	}

	previous->next = current->next;
	*head = previous->next;
	free(current);
	return;
}



// Function to delete node at given index
// of Circular Linked List
void DeleteAtPosition(Node* head, int index)
{

	// find length of list
	int len = Length(head);
	int count = 1;
	Node* previous = head;
	Node* next = head;
	
	// check if list doesn't have any node
	// if not then return
	if(head == NULL){
		cout<<"Delete Last list is empty";
		return;
	}
	
	// given index is in list or not
	if(index >= len || index<0){
		cout<<"Index is not Found";
		return;
	}
	
	// delete first node
	if(index == 0){
		DeleteFirst(head);
		return;
	}
	
	// traverse first to last node
	while(len > 0){
		// if index found delete that node
		if(index == count){
			previous->next = next->next;
			free(next);
			return;
		}
		previous = previous->next;
		next = previous->next;
		len--;
		count++;
	}
	return;
}

// This code is contributed by Yash Agarwal(yashagarwal2852002)

