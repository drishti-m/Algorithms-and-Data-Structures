/* Problem 5.1 a
Lomoto Partition */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int n;
int swap(int A[], int a, int b)
{
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;

}
int Partition(int A[],int p,int q)//  A[p. . q]
{
    int x = A[p]; // pivot = A[p]
    int i = p;
    for(int j = p + 1; j <= q; j++)
    {

        if (A[j] <= x)
        {
            i = i + 1;
            swap(A,i,j); //placing elements lesser than or equal to pivot in right partition side
        }
    }
    swap(A,p,i); //placing pivot at right position
    return i; //pivot index
}

void QuickSort(int A[], int p, int r)
{
    if (p < r) //until trivial case is exceeded
    {
        int q = Partition(A, p, r);

        //2 subsequences:
        QuickSort (A, p, q - 1);
        QuickSort (A, q + 1, r);
        //q is position of pivot so pivot is excluded while subdividing
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

    double total = 0;
    int j = 1;
    int t = 0;

    FILE *fptr;
    char fname[50]= "array.txt";
    fname[strlen(fname)] = '\0';


    fptr = fopen(fname,"r");
    //file opening error

    if (fptr == NULL)
    {
        perror("Error opening file\n");
        return -1;
    }

    /* All the randomly generate arrays are in one file, and the quicksort is performed for 1000 elements at one time or loop */

    while (j <= 100000)
    {

        srand(time(0));
        j++;

        int temp = t;
        int lim = temp + n;
        int s = 0; //for overwriting array and saving space for every loop

        for (int i = temp ; i < lim; i++) //size= 1000
        {
            fscanf(fptr,"%d\n", &A[s]);
            t++; //track of which line are we in the file
            s++;
        }
        // print_arr(A,n);

        clock_t t1,t2;
        t1 = clock();

        QuickSort(A, 0, n-1);

        t2 = clock() - t1;
        double time = (double) t2/CLOCKS_PER_SEC;

        //print_arr(A,n);
        total = total + time;

    }

    fclose(fptr);
    printf("lomoto time is %lf\n", total/100000);

    return 0;

}

