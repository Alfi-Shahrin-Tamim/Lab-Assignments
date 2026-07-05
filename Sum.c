#include <stdio.h>

int sum(int arr[], int length){
    if (length == 0) return 0;

    return arr[length - 1] + sum(arr, length - 1);
}

int main(){
    int arr1[] = {3, 59, 46, 100, 69, 50};
    int len = sizeof(arr1) / sizeof(arr1[0]);
    printf("Sum of elements in the array is: %d\n", sum(arr1, len));
}
