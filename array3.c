#include <stdio.h>

int main(){
    int y, i, j ,length;

    printf("Size of array: ");
    scanf("%d", &length);
    int num[length];

    for(i = 0; i< length;i++){
        printf("Element at index %d: ", i);
        scanf("%d", &num[i]);
    }    
    printf("Elements: ");
    for(i= 0; i < length ; i++){
        if (i == length - 1) printf("%d \n", num[i]);       
        else printf("%d, ", num[i]);
    }
    for(i = 0; i < length; i++){
        for(j = i + 1;j < length; j++){
            if (num[i] == num[j]){
                for(y = j; y < length - 1; y++) {
                    num[y] = num[y+1];
                }
                length--;
                j--;
            }
        }
    }
    printf("Updated array: ");
    for(i= 0; i < length ; i++){
        if (i == length - 1) printf("%d ", num[i]);       
        else printf("%d, ", num[i]);
    }
    printf("\n");    

}
