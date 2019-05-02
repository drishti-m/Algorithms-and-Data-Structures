

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void MergeSort_split(int *arr,int L,int R, int k);
void insertSort(int *arr,int L,int R);
void merges(int *arr,int L,int M,int R);
double random(int *arr,int n, int k);
double best(int *arr,int n, int k);
double worst(int *arr,int n, int k);


int main()
{
    int i,n;
    double time1,time2,time3;
    printf("enter number\n");
    scanf("%d",&n);
    int arr[n],k;


    printf("enter k\n");
    scanf("%d", &k);

    srand(time(0)); //setting time seed

    printf("Generating random numbers..\n");
    for (i = 0; i < n; i++)
    {
        arr[i] = rand() % 100000 + 1;
    } //generating random numbers

    /*for(int i = 0; i < n; i++)
        printf("%d ",arr[i]);
    printf("\n\n"); */

    time1 = random(arr,n, k);
    time2 = best(arr,n,k);
    time3 = worst(arr,n,k);

    printf("\n Displaying all time computations: \n");

    printf("Computation Time taken for RANDOM: %f \n", time1);
    printf("Computation Time taken for BEST %f \n", time2);
    printf("Computation Time taken for WORST: %f \n", time3);



    return 0;
}

double random(int *arr,int n, int k)
{
    clock_t t,t2;
    double time1; //variables for time computation

    printf("\n\n RANDOM case..\n");
    t = clock();
    MergeSort_split(arr,0,n-1,k);


    t2 = clock() - t;
    time1 = (double)t2/ CLOCKS_PER_SEC ; //time for computing random case

    /* printf("\nSorted array for RANDOM CASE is \n");
     for(int i = 0; i < n; i++)
         printf("%d ",arr[i]);
     printf("\n");*/

    return time1;

}

double best(int *arr,int n, int k)
{
    clock_t t,t2;
    double time2;


    printf("\nSorted array is now the BEST CASE..\n");
    t = clock();
    printf("For best case: \n");

    MergeSort_split(arr,0,n-1,k);

    t2 = clock() - t;
    time2 = (double)t2/ CLOCKS_PER_SEC ; //time for best case
    /* printf("\nSorted array for BEST CASE is \n");
    for(int i = 0; i < n; i++)
       printf("%d ",arr[i]);
    printf("\n"); */
    return time2;
}

double worst(int *arr,int n, int k)
{
    clock_t t,t2;
    double time3;
    int a,j,temp;
    printf("\nArranging list for WORST case.. \n");
    for (a = 0; a < n; ++a)
    {
        for (j = a + 1; j < n; ++j)
        {
            if (arr[a] < arr[j])
            {
                temp = arr[a];
                arr[a] = arr[j];
                arr[j] = temp;
            }
        }
    }

    t = clock();
    printf("For worst case: \n");

    MergeSort_split(arr,0,n-1,k);

    t2 = clock() - t;
    time3 = (double)t2/ CLOCKS_PER_SEC ; //time for worst case

    /* printf("\nSorted array for WORST CASE is \n");
    for(int i = 0; i < n; i++)
        printf("%d ",arr[i]);
    printf("\n"); */

    return time3;
}

void MergeSort_split(int *arr,int L,int R, int k)
{

    if ((R - L + 1) <= k)
        insertSort(arr,L,R);
    else //if(L < R)
    {
        int middle = (L+R)/2;
        MergeSort_split(arr,L,middle,k);
        MergeSort_split(arr,middle+1,R,k);
        merges(arr,L,middle,R);
    }
}


void insertSort(int *arr,int L,int R)
{
    int key,j,i;
    // printf("Insertion sort between position %d and %d:\n",L+1,R+1);
    for(i = L+1; i <= R; i++)
    {
        key = arr[i];
        j = i-1;
        while((j > L-1) && (arr[j] > key))
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }

    /* printf("Sorted array after insertion sort:\n {");
      for (i = L; i <= R; i++)
      {
          printf(" %d", arr[i]);
      }
      printf("}\n\n"); */

}
void merges(int *arr,int l,int m,int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}








