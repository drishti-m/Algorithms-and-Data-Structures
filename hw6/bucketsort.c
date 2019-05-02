/* Concept: Bucket sort used with Insertion Sort,
as specified in lecture slides.

References:
https://www.geeksforgeeks.org/insertion-sort/
https://www.geeksforgeeks.org/bucket-sort-2/
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_arr(float A[], int n);

struct bucket
{
    int count;
    float* value;
};

/* Function to sort an array using insertion sort, from geeksforgeeks*/
//This algorithm already implemented in previous algorithms so not much explanations
void InsertionSort(float arr[], int n)
{
    int i, j;
    float key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/* Function for bucket sort */
void Bucket_Sort(float array[], int n, float max)
{
    struct bucket buckets[10];
    //10 buckets as we have 10 digits
    int bsize = 10;
    int i,j,k, bi;

    int divider = ceil((float)(max + 1)/ bsize);

    for (i = 0; i < bsize; i++)
    {

        buckets[i].count = 0;
        buckets[i].value = (float*)malloc(sizeof(float)*n);
    } //initializing buckets


    for (i = 0; i < n; i++)
    {
        j = floor(array[i] / divider ); //index in buckets

        buckets[j].value[buckets[j].count++] = array[i];

    }// Put array elements in different buckets according to the digit value


    for (k=0,i = 0; i < bsize; i++)
    {
        InsertionSort(buckets[i].value,buckets[i].count);
        //sort individual buckets using insertion sort

        //concatenating sorted buckets into original array
        for (j = 0; j < buckets[i].count; j++)
        {
            array[k + j] = buckets[i].value[j];

        }
        k += buckets[i].count;
        free(buckets[i].value); //deallocating bucket after use


    }



}
/* End of Bucket_Sort() */

//find max of an array
float Max(float A[], int n)
{
    float max = A[0];

    for (int i = 1; i < n; i++)
    {
        if (A[i] > max)
            max = A[i];
    }
    return max;

}

void print_arr (float A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%f ", A[i]);
    }
    printf("\n");
}

/*Driver Function */
int main()
{
    float A[] = {0.9, 0.1, 0.6, 0.7, 0.6, 0.3, 0.1};

    int n = sizeof(A)/sizeof(float);
    float max = Max(A,n);
    Bucket_Sort(A,n,max);

    print_arr(A,n);

    return 0;
}
