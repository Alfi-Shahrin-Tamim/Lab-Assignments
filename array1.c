#include <stdio.h>

int main(){

    int grades[7] = {85, 90, 78, 92, 88, 95, 80}, length, i, j;
    length = sizeof(grades) / sizeof(grades[0]);
    
    printf("Elements: ");
    for(i= 0; i < length ; i++){
        if (i == length - 1) printf("%d ", grades[i]);       
        else printf("%d, ", grades[i]);
    }

    for(i= 0; i < length - 1; i++){
        for(j = 0; j < length - 1 - i; j++){
             if (grades[j] < grades[j+1]){
                int temp = grades[j];
                grades[j] = grades[j+1];
                grades[j+1] = temp;
             } 
        }
    }
    printf("\nMaximum number is %d\n", grades[0]);
    printf("Minimum number is %d\n", grades[length - 1]);
}
