#include <stdio.h>

void mSort(int arr[], int start, int end){
    if (start == end) return;
    int mid = (start + end) /2;
    mSort(arr, start, mid);
    mSort(arr, mid + 1, end);

    int arr2[mid - start + 1], arr3[end - mid];
    //Transferring value to offspring arrays

    int i,j,k;
    for(i = 0; i< mid - start + 1; i++) arr2[i] = arr[start + i];
    for(j = 0; j < end - mid; j++) arr3[j] = arr[mid + 1 + j]; 

    //Giving back sorted values to parent array

    for(i = 0, j = 0, k = start; i < mid - start + 1 && j < end - mid;){
        if(arr2[i] <= arr3[j]){
            arr[k] = arr2[i];
            i++;
        }
        else{
            arr[k] = arr3[j];
            j++;
        }
        k++;    
    }
    while(i < mid - start + 1){
        arr[k] = arr2[i];
        i++;
        k++;
    }
    while(j < end - mid){
        arr[k] = arr3[j];
        j++;
        k++;
    }            
}

int main(){
    int arr1[] = {3, 12, 5, 89, 54, 48}, mid;
    int len = sizeof(arr1) / sizeof(arr1[0]);
    mSort(arr1, 0, len - 1);
    for(int i = 0; i < len; i++) printf("%d ", arr1[i]);
}
