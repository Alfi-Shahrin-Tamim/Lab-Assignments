#include <stdio.h>

int main(){
    int i, j, k ,length1, length2, length3;
    int arr1[] = {12, 23, 34, 43, 55, 58, 69, 79, 90, 100};
    int arr2[] = {35, 38, 45, 58, 67, 78, 79, 88, 120};
    length1 = sizeof(arr1) / sizeof(arr1[0]);
    length2 = sizeof(arr2) / sizeof(arr2[0]);
    length3 = length1 + length2;
    
    int arr3[length3];

    printf("1st array: ");
    for(i= 0; i < length1 ; i++){
        if (i == length1 - 1) printf("%d \n", arr1[i]);       
        else printf("%d, ", arr1[i]);
    } 
    printf("2nd array: ");
    for(j= 0; j < length2 ; j++){
        if (j == length2 - 1) printf("%d \n", arr2[j]);       
        else printf("%d, ", arr2[j]);
    }          

    for(i = 0, j = 0, k = 0; i < length1 && j < length2;){
           if(arr1[i] <= arr2[j]){
              arr3[k] = arr1[i];
              i++;
           }
           else {
            arr3[k] = arr2[j];
            j++;
           }
           k++;

    }
    while(i < length1){
        arr3[k] = arr1[i];
        i++;
        k++;
    }
        while(j < length2){
        arr3[k] = arr2[j];
        j++;
        k++;
    }
    
    printf("New merged array: ");
    for(k= 0; k < length3 ; k++){
        if (k == length3 - 1) printf("%d \n", arr3[k]);       
        else printf("%d, ", arr3[k]);
    } 
}
