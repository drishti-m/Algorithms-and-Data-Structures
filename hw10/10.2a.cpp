//Hints taken from: https://www.geeksforgeeks.org/program-to-print-sum-triangle-for-a-given-array/

#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

int cn; //cn = No of lines

//Prototyping
void print_arr(int* arr, int* path);//printing the path
int input(); //To take input as per the requirement
vector <int> temp;


/* Continues taking input until empty line is entered
When, invalid input is entered, it asks to input the line again
The input function is a bit complicated,
but it's done to adjust the test case format and avoid any issue with formatting
because I couldn't think of other way */

int input()
{

    string line;

    while (1)
    {
        getline(cin,line);
        //reads an entire line

        //if empty, exit loop
        if (line.empty())
            break;

        auto it = line.begin(); //iterator at start of the string line

        //scan all characters of string line
        while (it != line.end())
        {
            char x = *it; //store char by char
            it = next(it,1); //move to next position

            if (x != ' ') //to skip white space chars
            {
                string num;
                num = x; //single digit char stored in num

                //if the number entered is multiple digits,
                //keep scanning next character until space is encountered
                while((*it != ' ') && (it != line.end()))
                {
                    x = *it;
                    num = num + x;
                    it = next(it,1);
                }

                //num contains a number, as string

                int z = stoi(num); //convert it to integer

                //if any value in the line is out of range
                //0 is included because question's sample has 0 as valid input
                if ((z < 0) || (z > 10000))
                {
                    return -1;

                }
                else
                {
                    temp.push_back(z);
                    //add the number in vector temp
                }
            }
        }
    }
    return 0;

}

//*Main Function*
int main()
{
    //Ask for input
    int ret;
    ret = input();

    //Validation check, keep asking for input until valid data is entered
    while (ret != 0)
    {
        cout << "One of the numbers entered is invalid. \n"
             << "Valid Range is 0 to 10000. \n"
             << "Please enter the line again:\n";
        ret = input();
    }

    //Helper variables for
    /** Finding cn(no of lines n) **/
    //based on number of elements entered
    int j = 0;
    int k = 1;
    int i = 1;
    for (auto s: temp)
    {
        //cout << s << " "; //Elements of vector temp (numbers entered)
        j++;
        if (k == j)
        {
            i++;
            k = j + i;
        }
    }
    cn = i - 1; //gives the number of lines

    int inp, arr[cn][cn], path[cn][cn];


    /* Concept explained:
     Virtually creating a triangle to rectangular matrix, filling blank spaces with 0
    For eg,

    1           1 0 0
    2 3         2 3 0
    4 0 5   ->  4 0 5
    */



    /* MAIN PART OF THE logic for program starts here: */

    //Fill arr in the format above
    int ind = 0;
    for (int i = 0; i < cn; i++)
    {
        for (int k = 0; k < cn; k++)
        {
            if (k <= i)
            {
                arr[i][k] = temp[ind];
                ind++;
            }
            else //fill blank spaces with 0
            {
                arr[i][k] = 0;
            }
        }
    }


    //initialization of path with values of array(rectangle matrix)
    for (int i = 0; i < cn; i++)
    {
        for (int j =0; j < cn; j++)
        {
            path[i][j] = arr[i][j];
        }
    }


    /* Idea here is to add the path from bottom children, and
    replace their parents with the sum from right/left path whichever is maximum
    E.g,

        7                 7           21
       5 10             7 14         7 14
      1 2  4    ->     1 2 4    ->  1 2 4

    hence, 21 is the maximum sum and path is 7-10-4. */

    for (int i = cn-2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {

            //if adding left child yields higher sum, add it in path
            if ((path[i+1][j] + path[i][j]) > (path[i+1][j+1] + path[i][j]))

            {
                path[i][j] += path[i+1][j];
            }
            else
                //add right child in the path
            {
                path[i][j] += path[i+1][j+1];
            }
        }
    }


    //the top most value in the triangle gives the max sum
    int max_sum = path[0][0];

    cout << max_sum << endl; //print the max value

    print_arr((int*)arr, (int*)path); //print the path

    return 0;
}

//printing the maximum sum yielding path
void print_arr(int *arr, int *path)
{

    int j = 0;

    for (int i = 0; i < cn; i++)
    {
        cout << *((arr+i*cn)+j) << " "; //printing arr[i][j]

        //if right child yields higher sum, follow right path with j++
        //else, follow left path with j
        int temp1 = *((path + (i+1)*cn) + j); // temp1 = path[i+1][j]
        int temp2 = *((path + (i+1)*cn) + (j+1)); //temp2 = path[i+1][j+1]

        if (temp1 <  temp2)
        {
            j++;
        }
    }

}
