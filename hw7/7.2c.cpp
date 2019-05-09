// Reference: https://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/
#include <bits/stdc++.h>
using namespace std;

/* node of Linked List*/
class NodeLL
{
public:
    int value;
    NodeLL* next;
};

/* A node for Binary Tree */
class TreeNode
{
public:
    int data;
    TreeNode* left;
    TreeNode* right;
};

//prototyping
TreeNode* newTreeNode(int data); //add node
int countLNodes(NodeLL *top); //count no of nodes in LinkedList
void push(NodeLL** head_ref, int new_data); //push_back for linked list
void printList(NodeLL *head);//print elements in linked list
TreeNode* sortedListToBSTRecur(NodeLL **head_ref, int n); //recursion to convert sorted LL to BST
TreeNode* sortedListToBST(NodeLL *top); //initial function call
void preOrder(TreeNode* node); //pre order traversal of BST


/* A helper function that returns
count of nodes in a given Linked List */
int countLNodes(NodeLL *top)
{
    int count = 0;
    NodeLL *tmp = top;
    while(tmp)
    {
        tmp = tmp->next;
        count++;
    }
    return count;
}

/* Insert Function to insert a node
at the beginning of the linked list */
void push(NodeLL** head_ref, int new_data)
{
    NodeLL* new_node = new NodeLL();
    new_node->value= new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}



/* Function to print nodes in a given linked list */
void printList(NodeLL *head)
{
    while(head!=NULL)
    {
        cout << head->value << " ";
        head= head->next;
    }
}

/* Constructing new tree node
with given data as root
and null pointers to children */
TreeNode* newTreeNode(int data)
{
    TreeNode* node = new TreeNode();
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* First, it counts the no of nodes in Linked List.
Then, it calls sortedListtoBST,
 and constructs BST */
TreeNode* sortedListToBST(NodeLL *top)
{
    /*Count the number of nodes in Linked List */
    int n = countLNodes(top);

    /* Construct BST */
    return sortedListToBSTRecur(&top, n);
}



/*** Main function to convert to tree
    Constructs Balanced BST.
Parameters:
    ref_of_top_node ---> Pointer to the pointer of topmost node in Linked List.
    n - no of nodes in the LinkedList
returns:
    root of tree ***/
TreeNode* sortedListToBSTRecur(NodeLL **ref_of_top_node, int n)
{
    /* Base Case */
    if (n <= 0)
        return NULL;

    /* Recursively construct the left subtree */
    TreeNode *left = sortedListToBSTRecur(ref_of_top_node, n/2);


    /* Make a new tree node called root, to be linked with the left subtree
    constructed above. */
    TreeNode *root = newTreeNode((*ref_of_top_node)->value);
    root->left = left;

    /* Changing pointer to top node for parent recursive calls
    Main change of variable for recursion */
    *ref_of_top_node = (*ref_of_top_node)->next;

    /* Similarly, linking right sub tree to the root.
    No of nodes in right subtree =
    total nodes - nodes in left subtree -1 (for root)*/
    root->right = sortedListToBSTRecur(ref_of_top_node, n - n / 2 - 1);

    return root;
}

/* print pre order traversal of BST */
void preOrder(TreeNode* node)
{
    if (node == NULL)
        return;
    cout<<node->data<<" ";

    preOrder(node->left);
    preOrder(node->right);
}

/* Driver code*/
int main()
{

    NodeLL* head = NULL;

    /* Created linked list will be 1->2->3->4->5->6->7 */

    for (int i = 7; i > 0; i--)
    {
        push(&head,i);
    }


    cout<<"Given Linked List ";
    printList(head);

    /* Convert List to BST */
    TreeNode *root = sortedListToBST(head);
    cout<<"\nPreOrder Traversal of constructed BST ";
    preOrder(root);
    //printed in this order:
    /*     4
          /  \
         2    6
        / \  /  \
       1   3 5   7

       4 2 1 3 6 5 7 */

    return 0;
}
