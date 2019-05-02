/* Drishti Maharjan
ADS Assignment 6.1a
countsort.c

reference: Lecture slides pseudocode
*/

#include <stdio.h>
#include <stdlib.h>

void print_arr (int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void CountSort(int A[], int n)
{
    int C[10+1],i,j,k;
    k = 11; /** k should be max element not 11**/
    //10 digits and one extra space
    int B[n];
    //temporary array

    for (i = 0; i < k; i++)
        C[i] = 0;
    //initializing count array

    for (j = 0; j < n; j++)
        C[A[j]] = C[A[j]] + 1;
    //recording occurrences of digits

/* ADD PSEUDOCODE OF 6.1 c: Function RangeCount here */


    for (i = 1; i <= k; i++)
    {
        C[i] = C[i] + C[i-1];
    } //summing up count variables consecutively


    for (j = n-1; j >= 0; j--)
    {
        int x = A[j];
        int y = C[x];
        B[y-1] = x;
        C[x] = C[x] - 1 ;

    }  //filling in the sorted array

    print_arr(B,n);
}

/*Driver Function*/
int main()
{

    int A[] = {9, 1, 6, 7, 6, 2, 1};

    int n = sizeof(A)/sizeof(int);
    printf("Sorted array is\n");
    CountSort(A,n);

    return 0;

}
