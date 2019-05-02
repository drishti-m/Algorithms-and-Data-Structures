/* Drishti Maharjan
4.2 a
Reference: Notes of heapsort from tutorialspoint.com
*/
#include <stdio.h>
#include <stdlib.h>

//Making root node max in every sub-tree
//we get the max value in arr[0]
void Maxheap(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    //largest -> index to hold largest value of one sub tree
    int L = 2* i + 1; // left = 2*i + 1
    int R = 2* i + 2; // right = 2*i + 2


    // If left child is larger than its parent update largest index
    if (L < n && arr[L] > arr[largest])
    {

        largest = L;
    }

    // If right child is larger than largest so far
    if (R < n && arr[R] > arr[largest])
    {
        largest = R;
    }

    // If largest is not root(i.e. parent)

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        //Using heapify recursively to make sure the entire heap satisfies maxheap properties
        Maxheap(arr, n, largest);
    }
}

//heapsort function: main part
void heapSort(int arr[], int n)
{
    //Build maxheap and get largest element in top of heap(i.e arr[0])
    for (int i = n / 2 - 1; i >= 0; i--)
        Maxheap(arr, n, i);

    // Extracting element from heap(reduced), one by one
    for (int i=n-1; i>=0; i--)
    {
        //swap current node(largest of sub heap) with last node
        //assuming last element is removed in sub heap
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call max heapify on the reduced heap
        Maxheap(arr, i, 0);
    }
}

/* print array to check if required*/
void printArray(int arr[], int n)
{
    for (int i=0; i<n; ++i)
        printf("%d ",arr[i]);
    printf("\n");
}

// test program for algorithm
int main()
{
    int heaplength;
    printf("Enter number of elements\n");
    scanf("%d", &heaplength);

    int arr[heaplength];

    for (int i = 0; i < heaplength; i++)
    {
        scanf("%d", &arr[i]);
    }


    heapSort(arr, heaplength);

    printf("Sorted array is \n");
    printArray(arr, heaplength);

    return 0;
}
