#include "./the3.h"
#include <iostream>
using namespace std;

int recursive_sln(int i, char **&arr, int *&len, int &number_of_calls)
{ // direct recursive

    // your code here
    number_of_calls += 1;

    // Base case
    if (i == 0)
    {
        return len[0];
    }

    int result = 0;

    if (number_of_calls == 1)
    {
        int notincluded = 0;
        for (int k = 0; k < i; k++)
        {
            notincluded = std::max(notincluded, recursive_sln(i - 1 - k, arr, len, number_of_calls));
        }

        int sMeMax = len[i];
        for (int j = i - 1; j >= 0; j--)
        {
            char s = arr[i][0];
            char e = arr[j][1];
            if ((s == 'I' && e == 'O') || (s == 'O' && e == 'I') || (s == 'S' && e == 'S'))
            {
                sMeMax += recursive_sln(j, arr, len, number_of_calls);
                break;
            }
        }

        result = std::max(sMeMax, notincluded);
    }
    else
    {

        int sEmax = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            char e = arr[i][1];
            char e2 = arr[j][1];
            if (e == e2)
            {
                int rec = 0;
                sEmax = recursive_sln(j, arr, len, rec);
                number_of_calls += rec;
                break;
            }
        }

        int sMeMax = len[i];
        for (int j = i - 1; j >= 0; j--)
        {
            char s = arr[i][0];
            char e = arr[j][1];
            if ((s == 'I' && e == 'O') || (s == 'O' && e == 'I') || (s == 'S' && e == 'S'))
            {
                int rec = 0;
                sMeMax += recursive_sln(j, arr, len, rec);
                number_of_calls += rec;
                break;
            }
        }

        result = std::max(sMeMax, sEmax);
    }

    return result; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

int memoization_sln(int i, char **&arr, int *&len, int **&mem)
{ // memoization

    // your code here

    if (i == 0)
    {
        if (arr[0][1] == 'I')
        {
            mem[0][0] = len[0];
            mem[0][1] = 0;
            mem[0][2] = 0;
        }
        else if (arr[0][1] == 'O')
        {
            mem[0][0] = 0;
            mem[0][1] = len[0];
            mem[0][2] = 0;
        }
        else
        {
            mem[0][0] = 0;
            mem[0][1] = 0;
            mem[0][2] = len[0];
        }

        return len[0];
    }

    int result = 0;

    int memS1[3] = {-1};
    int allMax = memoization_sln(i - 1, arr, len, mem);

    for (int k = 0; k < 3; k++)
    {
        memS1[k] = mem[i - 1][k];
    }

    int temp = 0;
    if (arr[i][0] == 'I')
    {
        temp = memS1[1] + len[i];
    }
    else if (arr[i][0] == 'O')
    {
        temp = memS1[0] + len[i];
    }
    else
    {
        temp = memS1[2] + len[i];
    }

    if (arr[i][1] == 'I')
    {
        memS1[0] = std::max(memS1[0], temp);
    }
    else if (arr[i][1] == 'O')
    {
        memS1[1] = std::max(memS1[1], temp);
    }
    else
    {
        memS1[2] = std::max(memS1[2], temp);
    }

    mem[i][0] = memS1[0];
    mem[i][1] = memS1[1];
    mem[i][2] = memS1[2];
    result = std::max(memS1[0], memS1[1]);
    result = std::max(result, memS1[2]);
    result = std::max(result, allMax);

    return result; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

int dp_sln(int size, char **&arr, int *&len, int **&mem)
{ // dynamic programming

    if (size == 0)
        return 0;

    if (arr[0][1] == 'I')
    {
        mem[0][0] = len[0];
        mem[0][1] = 0;
        mem[0][2] = 0;
    }
    else if (arr[0][1] == 'O')
    {
        mem[0][0] = 0;
        mem[0][1] = len[0];
        mem[0][2] = 0;
    }
    else
    {
        mem[0][0] = 0;
        mem[0][1] = 0;
        mem[0][2] = len[0];
    }

    for (int i = 1; i < size; i++)
    {
        int memS1[3] = {-1};
        for (int k = 0; k < 3; k++)
        {
            memS1[k] = mem[i - 1][k];
        }

        int temp = 0;
        if (arr[i][0] == 'I')
        {
            temp = memS1[1] + len[i];
        }
        else if (arr[i][0] == 'O')
        {
            temp = memS1[0] + len[i];
        }
        else
        {
            temp = memS1[2] + len[i];
        }

        if (arr[i][1] == 'I')
        {
            memS1[0] = std::max(memS1[0], temp);
        }
        else if (arr[i][1] == 'O')
        {
            memS1[1] = std::max(memS1[1], temp);
        }
        else
        {
            memS1[2] = std::max(memS1[2], temp);
        }
        mem[i][0] = memS1[0];
        mem[i][1] = memS1[1];
        mem[i][2] = memS1[2];
    }

    int result = std::max(mem[size - 1][0], mem[size - 1][1]);
    result = std::max(result, mem[size - 1][2]);

    return result; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

// Testing purposed

void randomArray(char **&array, int *&len, int size)
{
    array = new char *[size];
    len = new int[size];
    for (int i = 0; i < size; i++)
    {
        char *stick = new char[2];
        array[i] = stick;
    }

    array[0][0] = 'I';
    array[0][1] = 'S';

    array[1][0] = 'S';
    array[1][1] = 'S';

    array[2][0] = 'O';
    array[2][1] = 'I';

    array[3][0] = 'S';
    array[3][1] = 'O';

    array[4][0] = 'O';
    array[4][1] = 'O';

    array[5][0] = 'I';
    array[5][1] = 'O';

    array[6][0] = 'S';
    array[6][1] = 'O';

    len[0] = 1;
    len[1] = 1;
    len[2] = 1;
    len[3] = 1;
    len[4] = 1;
    len[5] = 1;
    len[6] = 1;
}

int main()
{
    char **arr;
    int *len;
    int size = 7;
    int num = 0;
    randomArray(arr, len, size);

    int max = recursive_sln(6, arr, len, num);

    cout << "max " << max << ", Number of calls = " << num << endl;
    return 0;
}