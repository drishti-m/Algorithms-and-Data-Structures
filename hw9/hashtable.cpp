#include<stdio.h>
#include<stdlib.h>
#include <iostream>
/** HASH FUNCTION USED (Division Method)

h = k mod m;
where m = 241, a prime not too close to a power of 2 or 10.

This is a simple test function to analyze .
Run the program to further see how this choice structures the test data.

**/

//used struct because i thought it was easier
//however, the implementation framework remains the same
struct Node
{
    int key;
    int value;

};

//class Hashtable
class HashTable
{
private:
    Node arr[241];
    int currentSize = 0;
    int maxSize = 241;

public:
    //empty constructor
    //initialize array
    HashTable()
    {
        maxSize = 241; //max size of hashtable
        currentSize = 0;
        Node empty = {0, 0};
        for (int i = 0; i < 241; i++)
        {
            arr[i] = empty;
        }
    };

    //key is passed return index as per function
    int hashCode(int key)
    {
        std::cout << "Applied Hash function: "<< key<<" % "<< maxSize<<" = "<<(key % maxSize)<< "\n";
        return (key % maxSize);
    };

    //insert element into the hashtable with key and value
    void insertNode(int key, int value)
    {

        if (currentSize >= maxSize)
        {
            std::cout << "Hash Table is full. No more insertion possible\n";
            return;
        }

        //x has index acc to hash fct
        int x = hashCode(key);
        bool empty = isEmpty(x);

        //checking for collision:
        int k = x;
        while ((empty != 1) && (x <= k))
        {
            //linear probing: when reaches end of array,
            //check if there are spaces before, go from 0
            if (k == maxSize)
            {
                x = 0;
            }
            x++;

            std::cout << "Collision occurred..\n Don't worry. Looking for new place.. \n";
            //std::cout << "New place found at "<< x << '\n';
            empty = isEmpty(x);
        }
        //x = k;

        //insert to the node
        Node node = {key, value};
        arr[x] = node;
        std::cout << "Successfully inserted at position "<< x << '\n';
        currentSize++;

    };

    //return value of the table when key is given
    int get(int key) //getter
    {
        int x = hashCode(key);

        //if key is the current index
        if (this->arr[x].key == key)
        {
            // std::cout << x << "\n";
            return arr[x].value;
        }
        else
            //look for the index
        {
            while (this->arr[x].key != key)
            {
                x++;
            }
            //std::cout << x << '\n';
            return arr[x].value;
        };
    }

    //checks if array is empty
    bool isEmpty(int index);
};

//checks if the array is empty
bool HashTable::isEmpty(int index)
{
    if (this->arr[index].key == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

int main()
{
    HashTable hasht;//testing

    //Simple test data of key 50
    //to check for its performance during collision

    hasht.insertNode(1, 1);
    hasht.insertNode(2, 2);

    hasht.insertNode(2, 3);
    hasht.insertNode(89,7);

    std::cout << hasht.get(2) << " " << hasht.get(89) << std::endl;

    return 0;
}
