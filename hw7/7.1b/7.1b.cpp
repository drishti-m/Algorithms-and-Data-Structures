#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Queue<int> pq(6);
    pq.Enqueue(5);
    pq.Enqueue(10);
    cout << pq.Dequeue();
    return 0;
}
