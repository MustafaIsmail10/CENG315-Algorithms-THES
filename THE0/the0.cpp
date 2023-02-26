#include "the0.h"

void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    
    //Your Code Here
    int i = 1;
    int x , j;
    comparison = 0; 
    swap = 0; 
    
    while (i < size){
        x = arr[i]; 
        j = i-1; 
        comparison += 1;
        while (j >= 0 && arr[j] > x){
            comparison+= 1;
            swap += 1;
            arr[j+1] = arr[j];
            j -= 1;
        }
        arr[j+1] = x; 
        i += 1;
    }
    
}