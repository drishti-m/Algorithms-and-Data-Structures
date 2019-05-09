#include "headers.h"
/* pushes element at front of linked list */
void LList::pushfront(const int& e)
{
    if(head == NULL)
    {
        head = new Node(e);
        return;
    }
    Node *newnode = new Node(e);
    newnode->next = head;
    head = newnode;
}


/* Inserts element in the tree such that it maintains BST property
  @param node the current node
 @param data element to be inserted
 @return void
*/
void BinarySearchTree::insert(Node *node, const int& data)
{

    //if element is less, it has to go to left
    if(data <= node->value)
    {
        if(node->left == NULL)
        {
            node->left = new Node(data); //empty, create new root
        }
        else
        {
            insert(node->left, data);
            //recursively call
        }
    }
    else //goes to right
    {
        if(node->right == NULL)
        {
            node->right = new Node(data);
        }
        else
        {
            insert(node->right, data);
        }
    }
}

/* This method is called pre-order traversal of the tree.
 @param node the current node
 @param list the linked list
*/
void BinarySearchTree::toLList(Node *node, LList& mylist)
{
    //if node has right children
    if(node->right != NULL)
    {
        toLList(node->right, mylist);
    }

    mylist.pushfront(node->value);
    //add the rightmost leaf to the linkedlist in front

    //recursion for left sub tree
    if(node->left != NULL)
    {
        toLList(node->left, mylist);
    }
}
