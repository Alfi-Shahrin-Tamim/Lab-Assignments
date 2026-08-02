#include <stdio.h>
#include <stdlib.h>

int sum(int *arr, int length){
    if (length == 0) return 0;

    return *(arr + length - 1) + sum(arr, length - 1);
}

int main(){
    int len;
    printf("Number of elements: ");
    scanf("%d", &len);
    int *arr1 = malloc(len * sizeof(int));
    if (arr1 == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < len ; i ++){
        printf("Value at index %d: ", i);
        scanf("%d", arr1 + i);
    }
    printf("Sum of elements in the array is: %d\n", sum(arr1, len));
    free(arr1);
}
