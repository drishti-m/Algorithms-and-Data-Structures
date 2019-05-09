#include <iostream>
#include "stack.h"


using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Stack<int>List(5);



    List.push(5);
    List.push(10);
    cout << List.pop();
    return 0;
}
