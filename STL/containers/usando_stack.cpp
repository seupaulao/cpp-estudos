#include <iostream>
#include <stack>
using namespace std;
int main(){
    stack<int> st1;
    st1.push(10);
    st1.push(5);
    
    // Accessing top element
    cout << "Top element: " << st1.top() << endl;
    
    // Popping an element
    st1.pop();
    cout << "Top element after pop: " << st1.top() << endl;


    stack<int> st2;

    // Inserting elements at the top of the stack
    st2.push(10);
    st2.push(20);
    st2.push(30);
    st2.push(40);

    stack<int> st3;
    st3.push(10);
    st3.push(20);
    st3.push(30);
    st3.push(40);

    // Accessing the top element
    cout << st3.top();

     stack<int> st4;
    st4.push(10);
    st4.push(20);
    st4.push(30);
    st4.push(40);
    
    // Deleting top element
    st4.pop();
    
    while(!st4.empty()) {
        cout << st4.top() << " ";
        st4.pop();
    }

     stack<int>st5;
    if(st5.empty()){
        cout<<"Stack is empty "<<endl;
    }
    st5.push(100);
    if(!st5.empty()){
        cout<<"Stack is not empty. Top element: "<<st5.top()<<endl;
    }

    cout << "Size of stack:" << st5.size() << endl;

    stack<int> st6;
    st6.push(10);
    st6.push(20);
    st6.push(30);
    st6.push(40);

    // Create a copy
    stack<int> temp(st6);

    while (!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    return 0;
}   