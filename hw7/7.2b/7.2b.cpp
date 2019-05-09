//Reference: geeksforgeeks.com
#include <bits/stdc++.h>
#include "headers.h"

//print list
void LList::print_elements()
{

    if(head == NULL)
    {
        return;
    }

    Node *curr = head;
    while(curr != NULL)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
}


/* inserts a new node to BST.
Calls a private method insert to do the insertion in the right place.
  @param data the element to be inserted
*/
void BinarySearchTree::insert_node(const int& data)
{

    if(this->root == NULL)
    {
        this->root = new Node(data);
        return;
    }
    this->insert(this->root, data);
}



/* Converts the given BST to a linked list(sorted)
 calls the function toLList for the transformation on non empty BST.

@param node the current node
@param list the linked list
@return void
*/
void BinarySearchTree::makeLinkedList(LList& list)
{
    if(this->root == NULL)
    {
        return;
    }
    this->toLList(this->root, list);
}


int main()
{

    BinarySearchTree BST1;

    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {

        BST1.insert_node(i);
    }

    LList list;
    BST1.makeLinkedList(list);
    list.print_elements();

    return 0;
}
