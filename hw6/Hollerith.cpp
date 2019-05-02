/** DRISHTI MAHARJAN **/

/* Hollerith's Radix Sort.

For general concept of radix sort, this site was used:
https://www.geeksforgeeks.org/radix-sort/

For idea of significant digit, and exponent, this site was used:
https://austingwalters.com/radix-sort-in-c/

GitHub: https://gist.github.com/lettergram/39da091bfe634af655d8#file-radixsort-c

And, C++, and vectors was used in recommendation of Professor Lipskoch.
*/

/** Algorithm steps extracted from stackoverflow:

-Find the maximum value, hence the maximum exponent to get the most significant digit.
-Sort the array according to the current digit
-For each bucket of elements with the same digit at the current position:
if the bucket is empty or has only one element, it is sorted
otherwise, recurse on the bucket for the next lesser digit, using exp/10.

https://stackoverflow.com/questions/36120783/holleriths-radix-sort
**/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

void bucket_sort(vector<int>& Arr, int exp);

void print_arr(vector <int>&Arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << Arr[i] << " ";
    }
    cout << endl;
}

/*find max element of the entire array to know our max most significant digit */
int Max(vector<int>& Arr, int n)
{
    float maxx = Arr[0];

    for (int i = 1; i < n; i++)
    {
        if (Arr[i] > maxx)
            maxx = Arr[i];
    }
    return maxx;

}

/*
  Radix sort finds maximum element and exponent exp, and calls Bucket Sort which does the sorting.
  In the first call, elements are sorted according to MSB.
  Then, it propagates to LSB through recursion.
*/

void radix_sort(vector<int>& a,int n)
{

    int maxx = 0, exp = 1;
    maxx = Max(a,n);

    while(maxx/exp > 0)
    {
        exp = exp * 10;
    } //loops until the most significant digit of max element is reached.

    exp = exp/10;
    //MSB's exp place

    bucket_sort(a, exp);
}

/*
 This algorithm is slightly modified from the regular bucket sort.
 This has parameters array to be sorted, and exp : the exponent.
 We recursively use bucket sort such that base case is when all elements are in same bucket and exp = 0.
 The recursive call is done passing exp as exp/10, as we are moving from most significant to least.
*/
void bucket_sort(vector<int>& Arr, int exp)
{

    /* Base Case: exp = 0 and all elements are in the same bucket */
    if(exp == 0)
    {
        return;
    }
    else
    {
        int sig_digit;
        vector<int> Bucket[10];
        //Bucket[10] can be considered as a multi dimensional array, as we are using vector of int[]


        /* This is like going bit by bit internally.
         We take the digit on the current exponent(sig_digit)
         and put them in buckets accordingly. */
        for(int i = 0; i < Arr.size(); i++)
        {
            sig_digit = (Arr[i]/exp)%10;
           // cout << exp << " exp ";
           // cout << "sig " << sig_digit << " arr " << Arr[i] << endl;
            Bucket[sig_digit].push_back(Arr[i]);
            //push_back adds the element at the end
        }



        /* Individual Bucket Sorting:

         Guard case: Bucket size <= 1 means bucket is currently sorted as it has only one element.

         Otherwise, when the bucket size is > 1,
         we sort these buckets by dividing these buckets into child buckets(recursions).
         This is done by recursively calling bucketsort with exp = exp/10 */

        for(int i = 0; i < 10; i++)
        {
            if(Bucket[i].size() > 1)
            {
                bucket_sort(Bucket[i], exp/10);
            }
        }


        /* Putting the sections of sorted array to our original array */
        sig_digit = 0;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < Bucket[i].size(); j++)
            {
                Arr[sig_digit++] = Bucket[i][j];
            }
        }
    }
}

/* Driver Function*/
int main()
{

    const int n = 6 ;
    int vv[n] = {5,100,523,245,300,1000};
    //array list so that easy to assign list to vector
//int vv[n] = {110,111,111,112,109,113};
    vector<int> a(n);
    a.assign(&vv[0], &vv[0]+n); //assigning list vv to vector a

    radix_sort(a,n);

    cout << "Sorted array is " << endl;
    print_arr(a,n);

    return 0;
}
