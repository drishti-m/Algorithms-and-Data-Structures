#include <bits/stdc++.h>
using namespace std;
//Linked list and BST classes to work with

//Linked List
class LList
{

private:

    class Node
    {

    public:
        int value;
        Node *next;
        Node() {}
        Node(const int& data)
        {
            this->value = data;
            this->next = NULL;
        }
    };

    Node *head; //topmost element

public:

    void print_elements();
    LList()
    {
        head = NULL;
    }
    void pushfront(const int& x);
    void reverse();

};

//Binary Search Tree

class BinarySearchTree
{

private:

    class Node
    {
    public:
        int value;
        Node *left;
        Node *right;
        Node() {}
        Node(const int& data)
        {
            this->value = data;
            this->left = NULL;
            this->right = NULL;
        }
    };

    Node *root;

    void insert(Node *node, const int& data);

    void toLList(Node *node, LList& list);

public:

    BinarySearchTree()
    {
        root = NULL;
    }
    void insert_node(const int& data);
    void makeLinkedList(LList& list);
};
