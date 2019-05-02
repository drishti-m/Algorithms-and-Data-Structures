/*
Drishti Maharjan
ADS- 4.2b
Reference: Bottom up heap sort invariant
Retrieved from: https://link.springer.com/content/pdf/10.1007/BFb0029650.pdf
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int heaplength;
int x;
//global variables: x = size of entire array
//heaplength = size of particular reduced heaps (variable)

void Maxheap(int arr[], int n, int i); //to build Max heap structure
void printArray(int arr[], int n); //printing array
void partialMaxheap(int arr[], int i); //Fixing step when floating root to leaf disrupted heap
void Float_leaf(int arr[], int i, int l, int r); //Floating new root to leaf, and all the additional steps/checks
void heapSortL(int arr[], int n); //Heapsort implemented with the new variant
void JustheapSort(int arr[], int n);//normal heapsort function

void partialMaxheap(int arr[], int i)
{
    int upper_p = i; //upper_p takes care of parent position to control loop
    while (upper_p >= 0)
    {
        int l = 2*i+1; //left
        int r = 2*i+2; //right
        int largest = i;

        if ((l < heaplength) && (arr[l] > arr[i]))
        {
            largest = l;

        }
        if ((r < heaplength) && (arr[r] > arr[i]))
        {
            largest = r;
        }

        if (largest == i)
            return; //stop checking when parent is no longer smaller than its children


        if ((i % 2)!=0)
            upper_p = (int) i/2; //when current parent was the right child of its parent
        else
            upper_p = i/2 - 1; //when current parent was left child of its parent


        int temp;
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        //parent is largest now relative to children

        partialMaxheap(arr, upper_p);
        return;
    }

}

void Float_leaf(int arr[], int i, int l, int r)
{
    int temp_l = l; //to access the upper positions again, when required
    int temp_r = r;
    int temp_p = l/2;

    l = 2*i + 1; // left = 2*i + 1
    r = 2*i + 2; // right = 2*i + 2



    // If left child is larger than root
    if (l < heaplength && arr[l] >= arr[r])
    {
        int temp;
        temp = arr[i];
        arr[i] = arr[l];
        arr[l] = temp;
        Float_leaf(arr,l,l,r);

    }
    else if (r < heaplength && arr[r] > arr[l]) //if right child is larger than root
    {
        int temp;
        temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;

        Float_leaf(arr,r,l,r);
    }

    if (l >= heaplength) //when reaches leaf level
    {
        l = temp_l;
        r = temp_r;
        i = temp_p;

        if ((arr[i] < arr[l]) || (arr[i] < arr[r]))
            partialMaxheap(arr,i);
        //if heap is distorted by floating the new root to leaf
    }

    return;

}

//Making root node max in every sub-tree
//we get the max value in arr[0]
void Maxheap(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2


    // If left child is larger than root
    if (l < heaplength && arr[l] > arr[largest])
    {

        largest = l;
    }

    // If right child is larger than largest so far
    if (r < heaplength && arr[r] > arr[largest])
    {
        largest = r;
    }

    // If largest is not root
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        Maxheap(arr, n, largest);

    }
    return;
}

//NEW HEAP SORT (applied with loop variant of heapsort)
void heapSortL(int arr[], int n)
{
    int num;

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Maxheap(arr, n, i);
    } //first step same as normal heapsort



    for (int i = n-1; i >= 0; i--)
    {
        // Move current root(in this step, max is at arr[0]) to end
        //this max element of sub array won't be part of reduced heap

        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;


        //steps have changed from here:
        heaplength--;//to keep track of reduced heap structure
        Float_leaf(arr,0,1,2);
    }

    //Base Case: when we have only 2 elements left in our heap:
    //for some reason, I couldn't figure out how to put this case inside Float_leaf so i put it here
    //Please note that, this doesn't change any time complexity.

    if (arr[1] < arr[0])
    {
        int temp;
        temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
    } //last check between 1st and 2nd element

    return;
}

/*To print array whenever required: esp for checking purposes*/
void printArray(int arr[], int n)
{
    for (int i=0; i<n; ++i)
        printf("%d ",arr[i]);
    printf("\n");
}

//Function of normal heapSort taken from 4.2a
void JustheapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        Maxheap(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;


        // call max heapify on the reduced heap
        Maxheap(arr, i, 0);
    }
}

//Testing Program
int main()
{

    printf("Enter number of elements\n");
    scanf("%d", &heaplength);
    int y = x = heaplength, arr2[y], arr[x], i;

    srand(time(0)); //setting time seed
    printf("Generating random numbers..\n");

    for (i = 0; i < heaplength; i++)
    {
        arr[i] = rand() % 200 + 1;
        arr2[i] = arr[i];
    } //generating random numbers */

    // printf("array is \n");
    // printArray(arr, x);
    clock_t t1,t2;
    t1 = clock();
    JustheapSort(arr2,y);
    t2 = clock() - t1;
    double time2 = (double) t2/CLOCKS_PER_SEC;

    t1 = clock();
    heapSortL(arr, x);
    t2 = clock() - t1;
    double time = (double)t2/CLOCKS_PER_SEC;



    printf("Time taken for function with variant %lf\n", time);
    printf("Time taken for normal heapsort %lf\n", time2);

    // printf("Sorted array is \n");
    //  printArray(arr, x);

    return 0;

}

