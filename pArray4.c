#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, j, k ,length1, length2, length3;

    printf("Size of array 1: ");
    scanf("%d", &length1);
    int *arr1 = malloc(length1 * sizeof(int));

    if(arr1 == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for(i = 0; i< length1;i++){
        printf("Element at index %d: ", i);
        scanf("%d", arr1 + i);
    }
    for(i = 0; i < length1 - 1; i++) {
       for(j = 0; j < length1 - 1 - i; j++) {
          if (*(arr1 + j) > *(arr1 + j + 1)) {
             int temp = *(arr1 + j);
             *(arr1 + j) = *(arr1 + j + 1);
             *(arr1 + j + 1) = temp;
          }
       }
    }

    printf("Size of array 2: ");
    scanf("%d", &length2);
    int *arr2 = malloc(length2 * sizeof(int));

    if (arr2 == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for(i = 0; i< length2;i++){
        printf("Element at index %d: ", i);
        scanf("%d", arr2 + i);
    }      
    for(i = 0; i < length2 - 1; i++) {
       for(j = 0; j < length2 - 1 - i; j++) {
          if (*(arr2 + j) > *(arr2 + j + 1)) {
             int temp = *(arr2 + j);
             *(arr2 + j) = *(arr2 + j + 1);
             *(arr2 + j + 1) = temp;
          }
       }
    }    

    length3 = length1 + length2;
    
    int *arr3 = malloc(length3 * sizeof(int));

    if(arr3 == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("1st array: ");
    for(i= 0; i < length1 ; i++){
        if (i == length1 - 1) printf("%d \n", *(arr1 + i));       
        else printf("%d, ", *(arr1 + i));
    } 
    printf("2nd array: ");
    for(j= 0; j < length2 ; j++){
        if (j == length2 - 1) printf("%d \n", *(arr2 + j));       
        else printf("%d, ", *(arr2 + j));
    }          

    for(i = 0, j = 0, k = 0; i < length1 && j < length2;){
           if(*(arr1 + i) <= *(arr2 + j)){
              *(arr3 + k) = *(arr1 + i);
              i++;
           }
           else {
            *(arr3 + k) = *(arr2 + j);
            j++;
           }
           k++;

    }
    while(i < length1){
        *(arr3 + k) = *(arr1 + i);
        i++;
        k++;
    }
        while(j < length2){
        *(arr3 + k) = *(arr2 + j);
        j++;
        k++;
    }
  
    printf("New merged array: ");
    for(k= 0; k < length3 ; k++){
        if (k == length3 - 1) printf("%d \n", *(arr3 + k));       
        else printf("%d, ", *(arr3 + k));
    }
    free(arr1);
    free(arr2);
    free(arr3); 
}
