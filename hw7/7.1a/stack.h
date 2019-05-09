/*
CH08-320143
LinkedList.h
Drishti Maharjan
d.maharjan@jacobs-university.de
*/
#include <iostream>

using namespace std;

/*
This is a generic doubly linked list. Its type T is generic
*/
template<class T>
class Stack
{
private:
    struct StackNode   // linked list
    {
        T data;
        StackNode *next;
    };

    StackNode *top; // top of stack
    int size; // -1 if not set, value otherwise
    int current_size; // unused if size = -1

public:
    void push(T x);// if size set, check for overflow
    T pop(); // return element if not in underflow
    bool isEmpty(); // true if empty, false otherwise
    Stack(int new_size);
    Stack();
    ~Stack();
};


//empty constructor
template<class T>
Stack<T>::Stack()
{
    size = -1;
    current_size = 0;
    top = NULL;
}

template<class T>
Stack<T>::Stack(int new_size)
{
    top = NULL;
    size = new_size;
    current_size = 0;

}

template<class T>
Stack<T>::~Stack()
{
    delete top;
}
template<class T>
bool Stack<T>::isEmpty()
{
    if (current_size <= 0)
        return true;
    else
        return false;

}

template<class T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        cout << "Stack Underflow" << endl;
        return -1;

    } //empty list
    else if (current_size == 1)
    {
        T f = top->data;
        top = NULL;

        current_size = 0;

        return f;
    } //list with 1 element
    else
    {
        StackNode *tmpnode = top;
        T f = top->data;
        top = top->next;
        delete tmpnode;
        current_size--;

        return f;
    } //delete 1st element and return it

}

template<class T>
void Stack<T>::push(T x)
{
    if (current_size == size)
    {
        cout << "Stack Overflow" << endl;
    }
    else  if (current_size <= 0)
    {
        top = new StackNode();

        top->next = NULL;
        top->data = x;
        current_size = 1;

    }//if empty, make element last
    else
    {
        StackNode *newel = new StackNode();
        newel->data = x;
        newel->next = top;
        top = newel;
        current_size++;

//delete newel;
    }//else update first element

    cout << top->data << endl;

}

