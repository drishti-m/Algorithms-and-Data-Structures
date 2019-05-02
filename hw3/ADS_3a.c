#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int naive_fib(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        int fib = naive_fib(n-1) + naive_fib(n - 2);
        return fib;
    }
}

int bottom_up(int n)
{

    int n1, n2;
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        n1 = 0;
        n2 = 1;
        //printf("0 1 ");
        for (int i = 0; i < n-1; i++)
        {
            n2 = n1 + n2;
            n1 = n2 - n1;
        }
        return n2;
    }
}

int matrix(int n)
{
    int matr1[2][2], matr2[2][2], matr3[2][2];
    matr1[0][0] = matr2[0][0] = 1;
    matr1[0][1] = matr2[0][1] = 1;
    matr1[1][0] = matr2[1][0] = 1;
    matr1[1][1] = matr2[1][1] = 0;
    int sum = 0;

    for (int i = 0; i < (n-1); i++) //multiplication of the matrix n times
    {
        for (int c = 0; c < 2; c++)
        {
            for (int d = 0; d < 2; d++)
            {
                for (int k = 0; k < 2; k++)
                {
                    sum = sum + matr1[c][k]*matr2[k][d];
                }
                matr3[c][d] = sum;
                //helper matrix to transfer contents for each loop of 2 matrix multiplication
                sum = 0;
            }
        }

//transfer contents to matr2
        for (int c = 0; c < 2; c++)
        {
            for (int d = 0; d < 2; d++)
            {
                matr2[c][d] = matr3[c][d];
            }
        } //matr2 is now the updated matrix */
    }

    //printf("matrix form = %d\n", matr2[0][1]);
    return matr2[0][1];
}

int closed(int n)
{
    float sqrt5 = sqrt(5);
    float phi = (1+sqrt5)/2;
    float nphi = 1;
    for (int i = 0; i < n; i++)
    {
        nphi = phi * nphi;

    }
    float fib = nphi/sqrt5;
    int rfib = round(fib);
    //printf("%d ", rfib);
    return rfib;

}
int main()
{
    clock_t t,t2;
    double time1,time2,time3,time4;
    int n,x;


    printf("Enter n\n");
    scanf("%d", &n);


    t = clock();
    x = naive_fib(n);
    t2 = clock() - t;
    time1 = (double)t2/ CLOCKS_PER_SEC ;

    t = clock();
    x = bottom_up(n);
    t2 = clock() - t;
    time2 = (double)t2/ CLOCKS_PER_SEC ;

    t = clock();
    x = closed(n);
    t2 = clock() - t;
    time3 = (double)t2/ CLOCKS_PER_SEC ;

    t = clock();
    x = matrix(n);
    t2 = clock() - t;
    time4 = (double)t2/ CLOCKS_PER_SEC ;

    /* printf("Time for naive %lf\n", time1);
    printf("Time for bottom up %lf\n", time2);
    printf("Time for closed form %lf\n", time3);
    printf("Time for matrix  %lf\n", time4); */




    return 0;
}
