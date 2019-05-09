/*
CH08-320143
Queue.h
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
    int getSize()
    {
        return size;
    }
    void setSize(int s)
    {
        size = s;
    }
};


template<class T>
class Queue
{
public:
    Queue(int new_size);
    Queue();
    ~Queue();
    void Enqueue(T x);
    T Dequeue();

    Stack<T> s1;
    Stack<T> s2;
};

template<class T>
Queue <T>::Queue()
{
    s1.setSize(-1);
    s2.setSize(-1);
}

template<class T>
Queue<T>::Queue(int new_size)
{
    s1.setSize(new_size);
    s2.setSize(new_size);
}

template<class T>
Queue<T>::~Queue()
{

}
template<class T>
void Queue<T>::Enqueue(T x)
{
    //Stack <T> s1;
    s1.push(x);

}

template<class T>
T Queue<T>::Dequeue()
{
    if ((s1.getSize() <= 0) && (s2.getSize()<=0))
        return -1;

    if (s2.isEmpty())
    {
        while (!s1.isEmpty())
        {
            T x = s1.pop();
            s2.push(x);
        }
    }
    T y = s2.pop();

    return y;

}
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

    //cout << top->data << endl;

}


