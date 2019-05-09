/* Reference:
https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
https://github.com/anandarao/Red-Black-Tree/blob/master/RBTree.cpp
*/
#include <queue>
#include <cmath>
using namespace std;

//extra addition of double black to cover all cases
//Possible colors of red black tree nodes
enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    Color color;
    Node *left, *right, *parent;

    Node()
    {}

    Node(int data)
    {
        //default color= red
        color = RED;
        this->data = data;
        left = right = parent = NULL;
    }
};

class RedBlackTree
{
private:
    Node *root;

protected:
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    Node* searchNode(int, Node*);

public:
    RedBlackTree()
    {
        root = nullptr;
    }

    void insert(int);
    void deletes(int);
    Node* predecessor(const Node *&);// *& means parameter by reference
    Node* successor(const Node *&);
    Node* getMinimum();//get min of entire tree
    Node* getMaximum();
    Node* search(int);

    //additional methods:
    Color getColor(Node*&);
    void setColor(Node*&, Color);
    Node* getMinimum(Node*); //get minimum of a subtree
    Node* getMaximum(Node*);//get max of subtree
    //helper methods to insert
    Node* insertBST(Node*&, Node*&);
    void fixInsertRBTree(Node *&);

    //to delete
    Node* deleteBST(Node *&, int);
    void fixDeleteRBTree(Node *&node);

    //to print
    void LevelOrderTraversal();

};

//get minimum for entire tree
Node* RedBlackTree:: getMinimum()
{
    Node *mins = getMinimum(root);
    return mins;
}

//get maximum for entire tree
Node* RedBlackTree::getMaximum()
{
    Node* maxs = getMaximum(root);
    return maxs;
}
//empty and single node tree gets black
//otherwise, return the color that is assigned
Color RedBlackTree::getColor(Node *&node)
{
    if (node == nullptr)
        return BLACK;

    return node->color;
}

//set color of a node
void RedBlackTree::setColor(Node *&node, Color color)
{
    if (node == nullptr)
        return;
    node->color = color;
}


/*predecessor: the node lies behind of given node in terms of value
 successor: the node lies ahead of given node in terms of value

            25
          /    \
         15    40
        /  \   / \
       5   20 35  50

       Predecessor of node 25 will be right most element in left sub tree i.e.20
       Successor of node 25 will be left most element in right subtree i.e. 35

  */


//return the node with predecessor of the given node
Node* RedBlackTree::predecessor(const Node*& node)
{

    Node* curr = (Node*)node;

    //if left sub tree exists, get right most element(i.e. maximum of that sub tree)
    if(curr->left != NULL)
    {
        return getMaximum((Node*)node);
    }

    //if no left sub tree exists, there are 3 possible cases:
    // 1. if the current node is left child of its parent, its pre decessor doesn't exist(since its minimum of RBT):return null
    // 2. if current node is right child of its parent, its parent is its pre decessor
    // 3. if it is the root node, return null

    Node* p = curr->parent;
    while(p != NULL && curr == p->left)
    {
        curr = p;
        p = p->parent;
    }
    return p;
}

//return successor of given node
Node* RedBlackTree::successor(const Node*& node)
{

    Node* curr = (Node*)node;

    //if right sub tree exists, get left most node of that sub tree
    if(curr->right != NULL)
    {
        return getMinimum((Node*)node);
    }

    //if no right sub tree exists, there are 3 possible cases:
    // 1. if the current node is right child of its parent, its successor doesn't exist(since its maxmimum of RBT):return null
    // 2. if current node is left child of its parent, its parent is its successor
    // 3. if it is the root node, return null
    Node* p = curr->parent;
    while(p != NULL && curr == p->right)
    {
        curr = p;
        p = p->parent;
    }
    return p;
}

//get minimum node
Node* RedBlackTree::getMinimum(Node* node)
{
    Node* temp;
    temp = node;

    //if tree is empty
    if(temp == nullptr)
        return NULL;

    //minimum node will be in leftmost
    //go to the bottom left node
    while(temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

//get maximum
Node* RedBlackTree::getMaximum(Node* node)
{
    Node *temp = node;

    //if tree is empty
    if(temp == nullptr)
        return NULL;

    //go to bottom most right for max
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;

}

//helper method to get node with the data
//return node which has the searched value
Node* RedBlackTree::searchNode(int data, Node* node)
{
    //empty tree
    if(node == NULL)
    {
        return NULL;
    }

    //look for which direction to go:
    if(data < node->data)
    {
        return searchNode(data,node->left);
    } //if value is lesser than the current level parent, go to left
    else if(data > node->data)
    {
        return searchNode(data,node->right);
    }//else go right
    else
    {
        return node;
    }//if current parent/root has the value, stop search process
}

//search data in RBT
//return the node that has the value
Node* RedBlackTree::search(int data)
{
    cout << "Searching for value "<< data << "..." << endl;

    Node* result = searchNode(data, root);

    //value doesn't exist
    if (result == nullptr)
    {
        cout << "Value doesn't exist in this RedBlackTree!" << endl;
    }
    else //print in which direction value is found
    {
        if (data == root->data)
        {
            cout << "Value found in root!" << endl;
        }
        else if (data < root->data)
        {
            cout << "Value found in left sub tree of root!" << endl;
        }

        else
        {
            cout << "Value found in right sub tree of root!" << endl;
        }

    }

    return result;
}

//print RBT contents according to level
/**      5
        /  \
       4     9
      /     / \
     1     7  10
    /
   0

   will be printed as 5,4,9,1,7,10,0

**/
void RedBlackTree::LevelOrderTraversal()
{
    cout << "Level order traversal:" << endl;

    if (root == NULL)
        return;

    std::queue<Node*> q;
    q.push(root);
    //put root at end of queue
    //initially queue is empty, so root is 1st element


    while (!q.empty())
    {
        //print first element of queue and pop it
        Node *temp = q.front();
        cout << temp->data << "  ";
        q.pop();

        //add temp's left child node after temp to queue end
        if (temp->left != NULL)
            q.push(temp->left);

        // then, add temp's right child node to queue end
        if (temp->right != NULL)
            q.push(temp->right);
    }//iterate through next level
    cout << endl;
}


/** NOTE: This implementation of Red Black Tree assumes to get no duplicate values.
That is, it works for values that are a set **/

//helper method to insert a new node at BST
Node* RedBlackTree::insertBST(Node *&root, Node *&ptr)
{
    //empty tree
    if (root == nullptr)
        return ptr;

    //if node to be inserted is lesser than current root
    //go to left sub tree
    if (ptr->data < root->data)
    {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->data > root->data)
    {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }//if node to be inserted is greater than current root, go right

    //after it has been added, return actual root
    return root;
}

//method to insert any value at the BST
//and maintain the balance of RBT
void RedBlackTree::insert(int n)
{

    //if value is not integer
    if (isalpha(n) || (floor(n) != ceil(n)))
    {
        throw "Invalid data type. Please only pass integers!";
    }

    Node *node = new Node(n); //create a new node

    root = insertBST(root, node); //insert node and get the root

    //fix the RBT Properties
    fixInsertRBTree(node);
}

//Fixing RedBlack Tree Properties
void RedBlackTree::fixInsertRBTree(Node *&node)
{
    //null parent and grandparent
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    /* while inserting a red node to a valid red-black tree, properties violated:
    1. RooB: Violated if inserted node is root.
    2. BredB: Violated if parent of inserted node is red. */

    //loop when:
    //node to be added is not in root, and is red, (RooB property)
    //and parent is red i.e. consecutive reds (B.RedB property)

    while (node != root && getColor(node) == RED && getColor(node->parent) == RED)
    {
        //set node's parent and grandparent
        parent = node->parent;
        grandparent = parent->parent;

        /**if node's parent is left child of its parent **/

        if (parent == grandparent->left)
        {
            //set node's uncle in right
            Node *uncle = grandparent->right;

            /** CASE 1(from slides): **/ // if uncle is red
            //change grandparent's color to red, and uncle and parent -> black
            //set node to grandparent
            if (getColor(uncle) == RED)
            {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            }
            else
            {
                //if node is right child of its parent,
                //rotateLeft its parent, and update node as its parent
                // and go one level up in the tree
                /** Case 2 (Black Uncle, z Right Child) **/
                if (node == parent->right)
                {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }

                /** Case 3 (Black Uncle, z Left Child) **/
                //rotate Right via the last updated grandparent
                rotateRight(grandparent);

                //change parent and grandparent colors
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        /**if the node's parent is right child of its parent**/
        else
        {
            //left uncle
            Node *uncle = grandparent->left;

            /** Symmetric to Case 1 **/ //if uncle is red,
            if (getColor(uncle) == RED)
            {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            }
            else
            {
                /** Symmetric to case 2 **/
                if (node == parent->left)
                {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }

                /** Symmetric to case 3 **/
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    //fixing rooB property: root should be black

    setColor(root, BLACK);

}
/*
       7                            7
      /  \                        /  \
    4    11                      4   18
        /  \        ->              / \
        9   18                     11  19
           /  \                   /  \
          14  19                 9   14    */
//rotate left via the Node x
void RedBlackTree::rotateLeft(Node *&x)
{
    Node *y = x->right; //set y
    x->right = y->left; //turn y's left subtree into x's right subtree

    //if x has right sub tree, update right child's parent
    if (x->right != nullptr)
    {
        x->right->parent = x;

    }

    y->parent = x->parent; //link x's parent to y's parent


    if (x->parent == nullptr)
    {
        root = y;
    }//if x is root, make y root
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }//if x is left child of parent
    else
    {
        x->parent->right = y; //setting parent & new child's link
    }//if x is right child of parent

    y->left = x; //put x on y's left
    x->parent = y; //make x's new parent y
}

//Rotate Right via ptr Node
void RedBlackTree::rotateRight(Node *&ptr)
{
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    //if ptr has left sub tree, update left child's parent
    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent; //linking parents

    if (ptr->parent == nullptr)
        root = left_child; //if ptr is root
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child; //if ptr is left child
    else
        ptr->parent->right = left_child; //if ptr is right child

    //ptr on left child's right
    //make left child as ptr's parent
    left_child->right = ptr;
    ptr->parent = left_child;
}

//delete an element from the tree
//call deleteBSt which deletes the node
//then fix the distorted properties of RBT
void RedBlackTree::deletes(int data)
{
    Node *tmp = deleteBST(root, data);

    cout << "Deleting " << data << ".." << endl;
    fixDeleteRBTree(tmp);

}

//Main function to delete the node
Node* RedBlackTree::deleteBST(Node *&root, int data)
{
    //empty tree
    if (root == nullptr)
        throw "Empty tree. Nothing to delete";

    //if value to be deleted is in left subtree
    if (data < root->data)
        return deleteBST(root->left, data);

    //if value is in right subtree
    if (data > root->data)
        return deleteBST(root->right, data);

    //base case:
    if (root->left == nullptr || root->right == nullptr)
        return root;

    //change root data to minimum node
    Node *temp = getMinimum(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}//returns new root


//Fixing RBT after deletion
void RedBlackTree::fixDeleteRBTree(Node *&node)
{
    //empty tree
    if (node == nullptr)
        return;

    //if passed node is in root, then tree becomes empty after deletion
    if (node == root)
    {
        root = nullptr;
        return;
    }

    //if node is red or has red children
    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED)
    {
        Node *child = node->left != nullptr ? node->left : node->right;

        //if node is left child of its parent
        //recolor children nodes, and change links
        if (node == node->parent->left)
        {
            node->parent->left = child;
            if (child != nullptr)
            {
                child->parent = node->parent;
            }
            setColor(child, BLACK);
            delete (node);
            //delete the node
        }
        else
        {
            //if node is right child
            node->parent->right = child;
            if (child != nullptr)
            {
                child->parent = node->parent;
            }
            setColor(child, BLACK);
            delete (node);
        }
    }
    else //if node is black and has black children
    {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;

        //if it's already black, we need to double blacken it
        setColor(ptr, DOUBLE_BLACK);

        //loop until we reach the ptr and as long as its color is not changed
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK)
        {
            parent = ptr->parent;

            //if ptr is left child
            if (ptr == parent->left)
            {
                sibling = parent->right;
                //recolor
                if (getColor(sibling) == RED)
                {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                }
                else
                {
                    //if sibling's children are black
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
                    {
                        setColor(sibling, RED);

                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    }
                    else //if one of sibling children is red
                    {
                        if (getColor(sibling->right) == BLACK)
                        {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }

                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);

                        //work done,break out of loop
                        break;
                    }
                }
            }
            else //if ptr is right child
            {
                sibling = parent->left;

                //if sibling is red
                if (getColor(sibling) == RED)
                {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                }
                else //if sibling is black
                {
                    //black sibling children
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
                    {
                        setColor(sibling, RED);

                        //black or double black
                        if (getColor(parent) == RED)
                        {
                            setColor(parent, BLACK);
                        }
                        else
                        {
                            setColor(parent, DOUBLE_BLACK);
                        }
                        ptr = parent;
                    }
                    else //if any of sibling children is red
                    {
                        //black left child of sibling
                        if (getColor(sibling->left) == BLACK)
                        {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }

                        //change colors finally
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }

        //if node was left child, then now left child is null
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else //right child is null
            node->parent->right = nullptr;

        delete(node);

        //setting root property to default black
        setColor(root, BLACK);
    }
}


