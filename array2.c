#include <stdio.h>

int main(){
    int num[10] = {3, 4, 6, 2, 5, 15, 20, 76, 94, 102}, x, y, i, length;
    length = sizeof(num) / sizeof(num[0]);

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
