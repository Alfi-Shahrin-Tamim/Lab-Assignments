#include <stdio.h>

int reverse(int arr[], int length, int i, int middle){
    if(i > middle) return 0;
    int temp;
    temp = arr[i];
    arr[i] = arr[length - 1];
    arr[length - 1] = temp;
    reverse(arr, length - 1, i + 1, middle);
}
int main(){
    int arr1[] = {3, 59, 46, 100, 69, 50};
    int len = sizeof(arr1) / sizeof(arr1[0]), mid, i;
    if(len % 2 == 0) mid = (len/2) - 1;
    else mid = ((len - 1) / 2) - 1;
    reverse(arr1, len, 0, mid);
    for(i = 0; i < len; i ++) printf("Element: %d\n", arr1[i]);
}    
