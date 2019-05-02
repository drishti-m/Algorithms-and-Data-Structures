/* Algorithms and Data Structure
Assignment 1
Code for 1.2 c and d
Drishti Maharjan */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* For 1.2 c, a program was written in C to generate random numbers using seed, and function ssort implemented selection sort.
Then, time computations were calculated for the randomly generated list.
The sorted list was then considered to be the best case, and ssort was called and time computed.
For worst case, the sorted list was reversed and ssort was called for it, and time computed.

For 1.2 d, the program was run for multiple times over same n to get raw data for average case, worst case and best case.
Then, data points were plotted in a graph to see the curves via gnuplot.
*/


void ssort(int array[],int n); //prototype function for selection sort

int main()
{
    int n, a, j,k;
    printf("Enter number of elements\n");
    scanf("%d", &n);
    int array[n];
    //setting variables

    srand(time(0)); //setting time seed

    for (k = 0; k < n; k++)
    {
        array[k] = rand() % 100000000 + 1;
        printf("%d ", array[k]);

    } //generating random numbers


    clock_t t,t2;
    double time1,time2,time3; //variables for time computation

    printf("\n\n RANDOM case..\n");
    t = clock();
    ssort(array, n); //calling function for selection sort
    t2 = clock() - t;
    time1 = (double)t2/ CLOCKS_PER_SEC ; //time for computing random case


    printf("\nSorted array is the BEST CASE..\n");
    t = clock();
    printf("For best case: \n");
    ssort(array, n);
    t2 = clock() - t;
    time2 = (double)t2/ CLOCKS_PER_SEC ; //time for best case

    printf("\nArranging list for WORST case.. \n");
    for (k = 0; k < n; ++k)
    {
        for (j = k + 1; j < n; ++j)
        {
            if (array[k] < array[j])
            {
                a = array[k];
                array[k] = array[j];
                array[j] = a;
            }
        }
    }


    t = clock();
    printf("For worst case: \n");
    ssort(array, n);
    t2 = clock() - t;
    time3 = (double)t2/ CLOCKS_PER_SEC ; //time for worst case

    printf("\n Displaying all time computations: \n");
    printf("Computation Time taken for RANDOM: %f \n", time1);
    printf("Computation Time taken for BEST %f \n", time2);
    printf("Computation Time taken for WORST: %f \n", time3);

    return 0;
}


//main code for selection sort:
void ssort(int array[], int n)
{
    int i, j, position, swap;


    for (i = 0; i < (n - 1); i++)
    {
        position = i; //position of 1st element in unsorted list

        for (j = i + 1; j < n; j++)
        {
            if (array[position] > array[j])
                position = j;
        } //smallest element from unsorted list
        if (position != i)
        {
            swap = array[i];
            array[i] = array[position];
            array[position] = swap;
        }//swapping current element and smallest
    }//loops (n-1) times


    printf("\nSorted list in ascending order:\n");

    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("\n \n \n");

}

