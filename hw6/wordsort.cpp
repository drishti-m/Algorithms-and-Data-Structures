/** Drishti Maharjan
wordsort.cpp
Assignment 6.1 d **/

#include <iostream>
#include <cstring>
using namespace std;
void print(string arr[], int n);

//Get maximum value in arr[]
int getMax(string arr[], int n)
{
    int mx = arr[0].length();
    for (int i = 1; i < n; i++)
        if (arr[i].length() > mx)
            mx = arr[i].length();
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(string arr[], int n, int exp)
{
    string output[n]; // output array
    int i,ci, countv[256] = {0};
    //initializing count array

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
    {
        string b;
        b = arr[i];

        char c;

        if ((b.length()-1) < exp)
        {

            c = '*';
        } //for words smaller in length than max word length, fill remaining characters with '*'
        //* has lesser ASCII value than all letters in alphabet
        else
        {
            c = b[exp];
        } //otherwise, character by character sorting

        ci = (int)c; //ascii value of c

        countv[ci]++; //using as index of countv array

    }



    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 256; i++)
    {
        countv[i] += countv[i - 1];
    }


    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        string b;
        b = arr[i];
        char c;
        if ((b.length()-1) < exp)
        {

            c = '*';
        }
        else
        {

            c = b[exp];
        }
        ci = (int)c;
        //same process of extracting character to sort

        int x = countv[ci]-1;
        output[x] = arr[i];
        countv[ci]--;
    }



    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];


}


// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(string arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = (m-1); exp >= 0; exp--)
        countSort(arr, n, exp);
}

//print an array
void print(string arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i]  << " ";
}

/*Driver program*/
int main()
{
    string arr[] = {"word", "category", "cat", "new", "news", "world", "bear", "at", "work", "time"};
    int n = sizeof(arr)/sizeof(string);

    radixsort(arr,n);
    cout << "Sorted: " << endl;
    print(arr,n);

    return 0;
}
