// #include "the1.h"
#include <climits>
#include <iostream>
using namespace std;
// You can add your own helper functions

void insertionSort(int *arr, long &comparison, long &swap, int size)
{

	// Your Code Here
	int i = 1;
	int x, j;
	while (i < size)
	{
		x = arr[i];
		j = i - 1;
		while (j >= 0 && ++comparison && arr[j] > x)
		{
			swap += 1;
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = x;
		i += 1;
	}
}

void pdown(const int **heap, int i, int size, long &comparison, long &swap)
{
	const int *temp = heap[i];
	int child;
	int hole = i;
	for (; hole * 2 <= size; hole = child)
	{
		child = hole * 2;
		if (*heap[child] == INT_MAX)
		{
			comparison--;
		}
		comparison++;
		if (child != size && *heap[child + 1] != INT_MAX && comparison++ && *heap[child + 1] < *heap[child])
			++child;
		if (*heap[child] < *temp)
		{
			heap[hole] = heap[child];
			swap++;
		}
		else
		{
			break;
		}
	}

	heap[hole] = temp;
}

void heapfy(const int **heap, int size, long &comparison, long &swap)
{
	// find the half of the array and then start from their to put elements in their correct posistions
	for (int i = size / 2; i > 0; i--)
	{
		pdown(heap, i, size, comparison, swap);
	}
}

int kWayMergeSortWithHeap(int *arr, int K, int size, long &comparison, long &swap)
{

	int number_of_calls = 1;
	// Your code here
	if (size < K)
	{
		insertionSort(arr, comparison, swap, size);
		return number_of_calls;
	}

	int len = size / K;
	int *ptr = arr;

	for (int i = 0; i < K; i++)
	{
		number_of_calls += kWayMergeSortWithHeap(ptr, K, len, comparison, swap);
		ptr += len;
	}

	const int *arrptr[K + 1];
	int result[size];
	int r = 0;
	int arrptrSize = K;

	for (int i = 0; i < K; i++)
	{
		arrptr[i + 1] = len * i + arr;
	}
	int n = size;

	const int max = INT_MAX;
	heapfy(arrptr, K, comparison, swap);

	// cout << "heap " << endl;
	// for (int i = 1; i <= K; i++)
	// {
	// 	cout << *arrptr[i] << " ";
	// }
	// cout << endl;

	for (int i = 0; i < size; i++)
	{
		const int *temp = arrptr[1];
		result[r] = *temp;
		r++;
		temp += 1;

		if (int(temp - arr) % len == 0)
		{
			// arrptr[1] = arrptr[arrptrSize];
			// arrptr[arrptrSize] = &max;
			// arrptrSize -= 1;

			// arrptr[1] = &max;

			arrptr[1] = &max;
			pdown(arrptr, 1, K, comparison, swap);
			// arrptrSize -= 1;

			// cout << "heap " << endl;
			// for (int i = 1; i <= K; i++)
			// {
			// 	cout << *arrptr[i] << " ";
			// }
			// cout << endl;

			// arrptr[arrptrSize] = nullptr;
		}
		else
		{
			arrptr[1] = temp;
			pdown(arrptr, 1, arrptrSize, comparison, swap);
		}
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = result[i];
	}

	return number_of_calls;
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	int size = 16;
	long comparison = 0;
	long swap = 0;
	int calls = 0;
	int K = 4;

	calls = kWayMergeSortWithHeap(arr, K, size, comparison, swap);

	cout << "calls = " << calls << ", comps = " << comparison << ", swaps = " << swap << endl;

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	// int *arrptr[6];
	// for (int i = 0; i < 6; i++)
	// {
	// 	arrptr[i] = &arr[i]; /* assign the address of integer. */
	// }

	// for (int i = 0; i < 7; i++)
	// {
	// 	cout << *arrptr[i] << " ";
	// }
	// cout << endl;

	// heapfy(arrptr, 6, comparison, swap);

	// for (int i = 0; i < 7; i++)
	// {
	// 	cout << *arrptr[i] << " ";
	// }
	// cout << endl;

	// cout << "*************" << endl;

	// int arrx[] = {0, 20, 0, 7, 3, 16};
	// int *arrptr[6];
	// for (int i = 0; i < 6; i++)
	// {
	// 	arrptr[i] = &arrx[i]; /* assign the address of integer. */
	// }

	// for (int i = 0; i < 6; i++)
	// {
	// 	cout << *arrptr[i] << " ";
	// }
	// cout << endl;

	// heapfy(arrptr, 5, comparison, swap);

	// for (int i = 0; i < 6; i++)
	// {
	// 	cout << *arrptr[i] << " ";
	// }
	// cout << endl;

	// cout << "calls = " << calls << ", comps = " << comparison << ", swaps = " << swap << endl;

	return 0;
}