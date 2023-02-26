#include "the2.h"
#include <cmath>
#include <iostream>
using namespace std;
// You may write your own helper functions here

int getIndex(int num, int len, int digit, bool ascending)
{
    int div = pow(10, digit);
    num = num / div;
    int index = num % len;
    if (!ascending)
        index = len - index - 1;
    return index;
}

// countSort and return number of itirations
int countSort(int *arr, bool ascending, int arrSize, int k, int digit)
{
    int len = pow(10, k);
    int tempArr[len] = {0};
    int count = 0;

    for (int i = 0; i < arrSize; i++)
    {
        count++;
        int index = getIndex(arr[i], len, digit, ascending);
        tempArr[index] += 1;
    }

    for (int i = 1; i < len; i++)
    {
        count++;
        tempArr[i] += tempArr[i - 1];
    }

    int sortedArr[arrSize] = {0};
    for (int i = arrSize - 1; i >= 0; i--)
    {
        count++;
        int elem = arr[i];
        int index = getIndex(elem, len, digit, ascending);
        sortedArr[tempArr[index] - 1] = elem;
        tempArr[index] -= 1;
    }

    for (int i = 0; i < arrSize; i++)
    {
        count++;
        arr[i] = sortedArr[i];
    }
    return count;
}

long multiDigitRadixSort(int *arr, bool ascending, int arraySize, int groupSize, int maxDigitLength)
{
    long numberOfIterations = 0;

    int digit = 0;
    while (maxDigitLength)
    {
        int k;
        if (maxDigitLength >= groupSize)
        {
            k = groupSize;
            maxDigitLength -= groupSize;
        }
        else
        {
            k = maxDigitLength;
            maxDigitLength = 0;
        }
        numberOfIterations += countSort(arr, ascending, arraySize, k, digit);
        digit += k;
    }
    return numberOfIterations;
}

// int main()
// {

//     // testing counting sort
//     int arr[] = {9, 4, 8, 4, 3};
//     countSort(arr, 1, 5, 1, 0);

//     for (auto n : arr)
//     {
//         cout << n << " ";
//     }
//     cout << endl;

//     // // Testing get index
//     // int index = getIndex(556677, 4, 1);
//     // cout << index << endl;
//     return 0;
// }
