/*
Problem 5.2 c
 DUAL PARTITIONING QUICKSORT WITH RANDOM PIVOTS */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void print_arr(int A[], int n); //prints array A of size n
int swap(int A[], int a, int b); //swaps A[a] and A[b]
void QuickSort(int A[], int left, int right); //Quicksort function with partition in the same function, to avoid use of pointers

int n;

int swap(int A[], int a, int b)
{
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;

}
/* Partition designed as follows:

 [ P1 |         < P1      | L |   >= P1 and <=P2   | K |    ??           ?? | G |   > P2            | P2 ]
left     sub-array I            sub-array II           elements to be examined     sub-array III      right
                                                         indices from K to G




    Reference: concept of Yaroslavskiy's Dual Partition Quicksort with modifications:
    1. 2 pivots taken were first and second element, instead of first and last
    2. smaller element put in first index(here, named as 'left')
    3. larger element put in last index(here, named as 'right') -> to follow concept of Yaroslavskiv
    4. No insertion sort introduced, this is pure Quick Sort
    5. Technically, pointers have not been used to traverse the array (as pointers make it more complicated, and also might mess with time complexities)

    Then, Yaroslavskiy's algorithm was used with all the modifications.

    Algorithm retrieved from:
   https://codeblab.com/wp-content/uploads/2009/09/DualPivotQuicksort.pdf

*/
void QuickSort(int A[], int left, int right)
{
    int r1, r2;
    if ((left < right) && (right >= 0))
    {
        r1 = (rand() % (right + 1 - left)) + left;
        r2 = (rand() % (right + 1 - left)) + left;
        //setting two random indices from the sub array

        while (r1 == r2)
        {
            r2 =  (rand() % (right + 1 - left)) + left;
        } //making sure that the two pivots are not of the same index

        if (r1>r2)
        {
            int temp = r1;
            r1 = r2;
            r2 = temp;
        } //to use r1 as the smaller index always

        if (A[r1] > A[r2])
        {
            swap (A,r1,r2);
        } //if element in pivot of lower index > pivot of higher index, swap

        swap(A,r1,left);
        swap(A,r2,right);
        //keeping the pivots in left and right respectively
        //-> to follow Yaroslavskiyi's algo.

    } // condition applies until the base case is reached(when left index = right index)



    int p = A[left];
    int q = A[right];
    //left and right elements of sub array

    int l = left+1;
    int k = l;
    int g = right -1;

    if (k > g) //no element left to be examined

    {

        return;
    }//i.e. no element between K and G left
    //every element examined and sorted

    else
    {

        while (k <= g) //loops until K and G meet
        {
            if (A[k] < p)
            {
                swap(A,k,l);
                l=l+1;
            } //put elements smaller than 1st pivot in left side
            else
            {

                if (A[k] > q) //if elements larger than 2nd pivot are in left side(wrong side) of ideal location of pivot
                {
                    while ((A[g] > q) && (k < g))
                    {
                        g = g -1;
                    } //checking elements from right of K..G array and gives index of element that needs to be swapped
                    swap(A,k,g);
                    g = g -1;

                    if (A[k] < p)
                    {
                        swap(A,k,l);
                        l = l + 1;
                    } //if there's any element lesser than 1st pivot in the wrong side
                }
            }
            k = k +1;
            //traversing through the "to be examined" array position by position
        }

        //move to left by one index
        l = l -1;
        g = g +1;
        //move to right by one index

        //keeping the pivots in positions such that the partition strategy is maintained
        // [< p1, p1 , >= p1 && <= p2, p2, >p2]
        swap(A,left,l);
        swap(A,right,g);

        //3 subsequences:
        QuickSort(A,left,l-1);
        QuickSort(A,l+1,g-1);
        QuickSort(A,g+1, right);
    }

}

void print_arr(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);

    }
    printf("\n");
}

int main()
{
    printf("Enter number of elements\n");
    scanf("%d", &n);
    int A[n];
    srand(time(0));

    for (int i = 0 ; i < n; i++)
    {
        A[i] = rand() % 100 + 1;
    }
    print_arr(A,n);

    clock_t t1,t2;
    t1 = clock();

    QuickSort(A, 0, n-1);

    t2 = clock() - t1;
    double time = (double) t2/CLOCKS_PER_SEC;

    printf("Sorted array is\n");
    print_arr(A,n);

    //printf("Dual random pivot partition time is %lf\n", time );

    return 0;

}


