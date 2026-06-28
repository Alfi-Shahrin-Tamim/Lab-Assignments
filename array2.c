#include <stdio.h>

int main(){
    int x, y, i, length;
    printf("Size of array: ");
    scanf("%d", &length);
    int num[length];

    for(i = 0; i< length;i++){
        printf("Element at index %d: ", i);
        scanf("%d", &num[i]);
    }

    printf("Elements: ");
    for(i= 0; i < length ; i++){
        if (i == length - 1) printf("%d ", num[i]);       
        else printf("%d, ", num[i]);
    }
    printf("\nElement to be replaced: ");
    scanf("%d", &x);
    printf("New element: ");
    scanf("%d", &y);
       
    for(i= 0; i < length ; i++){
        if (num[i] == x) num[i] = y;
    }
    for(i= 0; i < length ; i++){
        if (i == length - 1) printf("%d \n", num[i]);       
        else printf("%d, ", num[i]);
    }

}
