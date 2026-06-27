#include <stdio.h>

int main(){
    int num[10] = {3, 4, 6, 20, 5, 15, 20, 4, 94, 20}, y, i, j ,length;
    length = sizeof(num) / sizeof(num[0]);

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
    for(i= 0; i < length ; i++){
        if (i == length - 1) printf("%d ", num[i]);       
        else printf("%d, ", num[i]);
    }    

}
