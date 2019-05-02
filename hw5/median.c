/* Problem 5.2 c
MEDIAN OF THREE */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int n;
void Mprint_arr(int A[], int p,int q);

int Mswap(int A[], int a, int b)
{
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;

}

int MPartition(int A[],int p,int r)//  A[p. . r]
{
    /* finding median element between p,(p+r)/2, and r */

    int mid = (p + r) / 2;
    if (A[mid] < A[p])
        Mswap(A,p,mid);
    if (A[r] < A[p])
        Mswap(A,p,r);
    if (A[mid] < A[r])
        Mswap(A, mid, r);

    // now elements in p, mid, and r are in ascending order


    int pivot = A[mid]; //true median is pivot
    int i = p - 1;//traversing through left
    int j = r + 1; //traversing through right
    /* same as Hoare: */
    while(1)
    {

        do
            i = i + 1;
        while (A[i] < pivot);

        do

            j = j - 1;
        while (A[j] > pivot);

        if (i >= j)
            return j;


        Mswap(A,i,j);
    }

}

void MQuickSort(int A[], int p, int r)
{

    if (p < r)
    {

        int pi = MPartition(A, p, r);
        MQuickSort(A, p, pi);
        MQuickSort(A, pi + 1, r);
    }

} //same as Hoare


void Mprint_arr(int A[], int p,int q)
{
    for (int i = p; i < q; i++)
    {
        printf("%d ", A[i]);

    }
    printf("\n");
}

int main()
{
    printf("Enter number of elements\n");
    scanf("%d", &n);

    int j = 1;
    double total = 0;

    FILE *fptr;
    char fname[50]= "array.txt";
    fname[strlen(fname)] = '\0';


    fptr = fopen(fname,"a");


    //file opening error
    if (fptr == NULL)
    {
        perror("Error opening file\n");
        return -1;
    }

    srand(time(0));
    int A[n];

    while (j <= 100000)
    {

        j++;

        for (int i = 0 ; i < n; i++)
        {
            A[i] = rand() % 100 + 1;
            fprintf(fptr,"%d\n",A[i]);

        }


        clock_t t1,t2;
        t1 = clock();
        MQuickSort(A, 0, n-1);

        t2 = clock() - t1;
        double time = (double) t2/CLOCKS_PER_SEC;
        total = total + time;

    }


    printf("Median time is %lf\n", total/100000 );
    fclose(fptr);

    return 0;
}
