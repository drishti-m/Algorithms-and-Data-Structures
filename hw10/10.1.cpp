//Reference: https://www.geeksforgeeks.org/construction-of-longest-increasing-subsequence-using-dynamic-programming/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//prototyping
void print_arr(vector<int> arr); //printing sub-array of maximal ordered length
void LOS(vector <int> arr, int n); //Longest Ordered Sub Array

/*Tester Function */
int main()
{
    vector <int> array;
    int c ;

    //accepts input until new line is entered
    while (cin.peek() != '\n')
    {
        cin >> c;

        array.push_back(c);
    }

    int arr_size = array.size();

    LOS(array, arr_size);
    return 0;
}

//printing function to print the vector which contains the selected sub-array.
void print_arr(vector<int> arr)
{
    for (auto x = arr.begin(); x != arr.end(); x++)
    {
        cout << *x << " ";
    }
}

//finding the maximal ordered length sub array
void LOS(vector <int> arr, int n)
{
    //vector of vectors
    vector<vector<int> > dp(n);

    //using dynamic programming table to compute values from bottom up

    dp[0].push_back(arr[0]); //1st value(row) filled

    //Start from 2nd value, so i = 1 to n
    for (int i = 1; i < n; i++)
    {
        //Start j from beginning to current i every time
        for (int j = 0; j < i; j++)
        {
            //if element in position i is greater and array size of i in dp is smaller
            if ((arr[i] > arr[j]) && (dp[i].size() < dp[j].size() + 1))
            {
                dp[i] = dp[j];
            }
        }

        dp[i].push_back(arr[i]);
        //add the element in array i
    }

    //initialize max as 1st value of dp
    vector<int> max = dp[0];

    //LOS will be max of all increasing subsequences of arr
    for (vector<int> x : dp)
    {
        if (x.size() > max.size())
            max = x;
    }

    // max will contain LOS, so print
    print_arr(max);
}
