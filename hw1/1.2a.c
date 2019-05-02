/* Algorithms and Data Structure
Assignment 1
Code for 1.2 a
Drishti Maharjan */

//implementation of selection sort

#include <stdio.h>

int main()
{

    int n, k, i, j, position, swap;
    printf("Enter number of elements you want to enter\n");
    scanf("%d",&n);
    int array[n];

    printf("\nEnter %d elements:\n", n);

    for (k = 0; k < n; k++)
    {
        scanf("%d", &array[k]);

    }

    //main code for selection sort:
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


    printf("\nAfter sorting, elements listed as: \n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    } //final list of sorted elements

    return 0;
}
