#include <stdio.h>
#include <stdlib.h>

void mSort(int *arr, int start, int end){
    if (start >= end) return;
    int mid = (start + end) /2;
    mSort(arr, start, mid);
    mSort(arr, mid + 1, end);
    int *arr2 = malloc((mid - start + 1) * sizeof(int));

    if (arr2 == NULL){
        printf("Memory allocation failed.\n");
        return ;
    }

    int *arr3 = malloc((end - mid) * sizeof(int));

    if (arr3 == NULL){
        printf("Memory allocation failed.\n");
        free(arr2);
        return ;
    }
    
    int i,j,k;
    for(i = 0; i< mid - start + 1; i++) *(arr2 + i) = *(arr + start + i);
    for(j = 0; j < end - mid; j++) *(arr3 + j) = *(arr + mid + 1 + j); 
    for(i = 0, j = 0, k = start; i < mid - start + 1 && j < end - mid;){
        if(*(arr2 + i) <= *(arr3 + j)){
            *(arr + k) = *(arr2 + i);
            i++;
        }
        else{
            *(arr + k) = *(arr3 + j);
            j++;
        }
        k++;    
    }
    while(i < mid - start + 1){
        *(arr + k) = *(arr2 + i);
        i++;
        k++;
    }
    while(j < end - mid){
        *(arr + k) = *(arr3 + j);
        j++;
        k++;
    }
    
    free(arr2);
    free(arr3);
}
int main(){
    int mid, len;
    printf("Size of array: ");
    scanf("%d", &len);

    int *arr1 = malloc(len * sizeof(int));

    if ( arr1 == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < len; i ++){
        printf("Value at index %d: ", i);
        scanf("%d", arr1 + i);
    }

    mSort(arr1, 0, len - 1);
    for(int i = 0; i < len; i++) printf("%d ", *(arr1 + i));
    printf("\n");

    free(arr1);
}
