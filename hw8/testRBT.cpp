#include <iostream>
#include "redblacktree.h"

/** NOTE: This implementation of Red Black Tree assumes to get no duplicate values.
That is, it works for values that are a set **/

using namespace std;

int main()

{
    RedBlackTree rbt;

    for (int i = 0; i <= 10; i++)
    {
        rbt.insert(i);
        rbt.insert(30-i);

    }
    rbt.insert(7);
    rbt.LevelOrderTraversal();

    try
    {
        rbt.insert('c');
    }
    catch(const char * e)
    {
        cerr << "Error: " << e << endl;
    }

    try
    {
        rbt.deletes(7);
    }
    catch(const char* e)
    {
        cerr << e << endl;
    }

    rbt.LevelOrderTraversal();
    rbt.deletes(20);
    rbt.LevelOrderTraversal();
    rbt.search(10);
    rbt.search(100);

    RedBlackTree rb;
    try
    {
        rb.deletes(20);
    }
    catch(const char* e)
    {
        cerr << "Exception caught in main: " << e << endl;
    }

    return 0;
}
