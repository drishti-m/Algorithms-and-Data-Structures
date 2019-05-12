/* Reference: https://github.com/laituan245/spoj-solution/blob/master/classical/SCUBADIV.cpp */

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

const int INF_WEIGHT = 100000;
//Since, max weight allowed is 800, creating an artificial infinite weight higher than 800

//program that returns min of 2 numbers
int minimum (int a, int b)
{
    if (a < b)
        return a;
    return b;
}

//program that returns max of 2 numbers
int maximum (int a, int b)
{
    if (a > b)
        return a;
    return b;
}

/*Path Reconstruction to print the used cylinders for min weight
@parameters
dp - dynamic programming table created in main
t - amount of oxygen required
a - required nitrogen
n - number of accessible cylinders
oxygen - array of oxygen contained in cylinders
nitrogen -nitrogen cylinders
*/
void prints(int dp[100][22][80], int t, int a, int n, int oxygen[10],int nitrogen[10])
{

    int i = n-1, tempOx = t, tempN = a;
    vector<int> seq;

    //loop n times
    //cylinder number = index of cylinder + 1 = i+1, so push_back(i+1)
    while(i >= 0 && (tempOx > 0 || tempN > 0))
    {
        //if 1st cylinder is used
        if(i == 0)
        {
            seq.push_back(i+1);
            break;
        }
        //if the top right element is different than current element
        //(i+1)th cylinder was used,
        //so subtract nitrogen and oxygen of ith cylinder from temp to trace the next cylinder
        else if(dp[i][tempOx][tempN] != dp[i-1][tempOx][tempN])
        {
            tempOx -= oxygen[i];
            tempOx = maximum(tempOx, 0);
            tempN -= nitrogen[i];
            tempN = maximum(tempN, 0);

            //add the i+1 cylinder in trace
            seq.push_back(i+1);
            i--;
        }
        else
        {
            //this i+1th cylinder wasn't used,
            //so just continue the loop
            i--;
        }
    }
    //we need the output from start to end, so reverse
    reverse(seq.begin(), seq.end());

    /* Output */

    for(auto element : seq)
    {
        cout << element << " ";
    }
    cout << endl;

}

/*Main Program to find minimum weight with enough N2 and O2 */

int main ()
{
    int c;  // Nb of test cases
    int t, a; //t = required oxygen and a = nitrogen
    int oxygen[1000]; //oxygen cylinders
    int nitrogen[1000]; //nitrogen cylinders
    int weight[1000]; //weight of cylinder
    int dp[100][22][80];
    int n; //number of accessible cylinder

    //Read no of test cases
    cin >> c;

    //m -> checking for all accessible cylinders
    for (int m = 0; m < c; m++)
    {
        cin >> t >> a >> n; //input required oxygen, nitrogen, and accessible cylinders

        //input test cases
        for (int i = 0; i < n; i++)
        {
            cin >> oxygen[i] >> nitrogen[i] >> weight[i];
        }

        // Dynamic Programming Table
        /* Visualize 3d table as:

        Row-> i
        Column-> (j,k)

        e.g, if we have 5 cylinders, and oxygen required = 2, nitrogen = 1,
        table would look like this:
        (j,k)  | (0,0) (0,1) (1,0) (1,1) (2,0) (2,1)

        i| 0       ..    ..
         1
         2
         3
         4

        */



        //Initializing values in the dp table
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= t; j++)
            {
                for (int k = 0; k <= a; k++)
                {
                    //fill all vertices with infinity
                    dp[i][j][k] = INF_WEIGHT;

                    //fill 1st column with 0
                    if ((j == 0) && (k == 0))
                    {
                        dp[i][j][k] = 0;
                    }
                }
            }
        }

        /* filling the 1st row with 1st weight at vertices where
        accessible oxygen and nitrogen are enough for given j and k.
        When the given cylinder's oxygen or nitrogen is not enough,
        let it remain infinity when j or k exceeds the given O2 and N2 */

        for (int j = 0; j <= t; j++)
        {
            for (int k = 0; k <= a; k++)
            {
                if (j <= oxygen[0] && k <= nitrogen[0] && (j > 0 || k > 0))
                {
                    dp[0][j][k] = weight[0];
                }
            }
        }

        int topright, topleft, p[n][t][a];
        /*First row is filled, so we need to fill the remaining rows. So, it starts with i = 1 instead of 0 */

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= t; j++)
            {
                for (int k = 0; k <= a; k++)
                {
                    //first fill dp[i][j][k] with value right above
                    dp[i][j][k] = dp[i-1][j][k];

                    //if given oxygen and nitrogen is enough for current j and k
                    if ((j <= oxygen[i]) && (k <= nitrogen[i]))
                    {
                        //if the new cylinder's weight is minimum, place it in table
                        if (minimum(dp[i][j][k], weight[i]) == weight[i])
                        {

                            dp[i][j][k] = weight[i];
                        }

                        //else let the value in table be dp[i-1][j][k] (as it is)
                    }
                    //if given nitrogen and/or oxygen not enough,
                    //need to add new cylinder and check gas and weight requirements
                    else
                    {

                        int temp = weight[i] + dp[i-1][maximum(0,j-oxygen[i])][maximum(0,k-nitrogen[i])];

                        //if the new addition of weight fulfills requirement and also gives lesser weight,
                        //place the total weight in table
                        if (minimum(dp[i][j][k], temp) == temp)
                        {
                            dp[i][j][k] = temp;
                        }

                        // else let the value be as it is
                    }
                }
            }
        }

        //The bottom most value of the table is our final answer
        cout << dp[n-1][t][a] << "\n";
        prints(dp,t,a,n,oxygen,nitrogen);
    }



    return 0;
}
