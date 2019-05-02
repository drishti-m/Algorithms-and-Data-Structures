/* Problem 5.1 b
HOARE PARTITION */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int n;
void print_arr(int A[], int temp,int lim); //print arr A from index temp to lim

int swap(int A[], int a, int b)
{
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;

}
int Partition(int A[],int p,int q)//  A[p. . q]
{
    int pivot = A[(p + q) / 2];
    int i = p - 1;
    int j = q + 1;
    while(1)
    {

        do
            i = i + 1;
        while (A[i] < pivot);//traverse from left until value lesser than the pivot is found
        //this value is in the wrong partition side

        do

            j = j - 1;
        while (A[j] > pivot); //traverse from right until value higher than pivot is found
        //this value is also in wrong partition side

        if (i >= j)
            return j;
            //if i and j have crossed each other, no more element to be examined in the sub array
             //returns index of pivot


        swap(A,i,j);
        //swap the pair of elements which are placed in wrong partition sides
    }


}
void QuickSort(int A[], int p, int r)
{
    if (p < r)
    {
        /* pi is index of pivot. */

        int pi = Partition(A, p, r);
        // now, A[p] is in its right position

      //2 subsequences:
        QuickSort(A, p, pi);
        QuickSort(A, pi + 1, r);
    }
}

void print_arr(int A[], int temp, int lim)
{
    for (int i = temp; i < lim; i++)
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


    while (j <= 1)
    {
        srand(time(0));
        j++;
        int A[8] = {2,8,7,1,3,5,6,4};

        int temp = t;
        int lim = temp + n; int s = 0;

        for (int i = temp ; i < lim; i++)
        {
            //fscanf(fptr,"%d\n", &A[s]);
            t++;
            s++;
        }

       // print_arr(A,temp,lim);
        clock_t t1,t2;
        t1 = clock();

        QuickSort(A, 0, n-1);

        t2 = clock() - t1;
        double time = (double) t2/CLOCKS_PER_SEC;
        total = total + time;

        print_arr(A,temp,lim);


    }
    printf("Time %lf\n", total/100000);
    fclose(fptr);
    return 0;

}




