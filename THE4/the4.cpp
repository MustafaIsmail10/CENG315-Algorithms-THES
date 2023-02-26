#include "the4.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

int dp_sln(char **&arr1, char **&arr2, int nrow, int ncol1, int ncol2, int **&mem)
{ // dynamic programming

    // your code here

    // Filling first 2 rows ***************************
    mem[0][0] = 0;
    for (int i = 0; i < ncol2; i++)
    {
        int temp = mem[0][i];
        for (int j = 0; j < nrow; j++)
        {
            if (arr2[j][i] != '-')
                temp += 1;
        }
        mem[0][i + 1] = temp;
    }

    for (int j = 0; j < ncol1; j++)
    {
        int temp = mem[j][0];
        for (int i = 0; i < nrow; i++)
        {
            if (arr1[i][j] != '-')
                temp += 1;
        }
        mem[j + 1][0] = temp;
    }
    //***********************************************

    // Filling the rest of the mem table
    for (int i = 1; i <= ncol1; i++)
    {
        for (int j = 1; j <= ncol2; j++)
        {
            // First case insert box2 column delete b1 column
            int temp1 = mem[i - 1][j];
            for (int k = 0; k < nrow; k++)
            {
                if (arr1[k][i - 1] != '-')
                    temp1 += 1;
            }

            // Second Case inset b2 colunm on the pervious result
            int temp2 = mem[i][j - 1];
            for (int k = 0; k < nrow; k++)
            {
                if (arr2[k][j - 1] != '-')
                    temp2 += 1;
            }

            int temp3 = mem[i - 1][j - 1];
            // For conversioin, there are 2 cases raplacing or reodering
            // For replacing
            int replace = 0;
            for (int k = 0; k < nrow; k++)
            {
                char v1 = arr1[k][i - 1], v2 = arr2[k][j - 1];
                if ((v1 == '-' && v2 != '-') || (v1 != '-' && v2 == '-'))
                {
                    replace += 2;
                }
                else if (v1 != v2)
                {
                    replace += 1;
                }
            }
            // For reordering
            int order = 0;
            // cout << "*********(i= " << i << ", j= " << j << " )************" << endl;

            bool vls[nrow] = {false};
            for (int x = 0; x < nrow; x++)
            {
                for (int s = 0; s < nrow; s++)
                {
                    char v1 = arr1[s][i - 1], v2 = arr2[x][j - 1];
                    // cout << "x= " << x << ", s= " << s << ", v2= " << v2 << "v1= " << v1 << ", vls = " << vls[s] << endl;
                    if (v1 == v2 && !vls[s])
                    {
                        vls[s] = true;
                        if (s != x)
                        {
                            order += 1;
                        }
                        break;
                    }
                }
            }
            int flag = true;
            for (int s = 0; s < nrow; s++)
            {
                // cout << vls[s] << " ";
                if (!vls[s])
                {
                    flag = false;
                }
            }
            // cout << endl;

            if (flag)
            {
                temp3 += min(order, replace);
                // cout << "can be reordered" << endl;
                // cout << "order= " << order << ", replace= " << replace << endl;
            }
            else
            {
                temp3 += replace;
            }
            // cout << "temp 3 = " << temp3 << endl;
            int temp = min(temp1, temp2);
            temp = min(temp, temp3);
            mem[i][j] = temp;
        }
    }

    return mem[ncol1][ncol2]; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
