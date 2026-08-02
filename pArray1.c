#include <stdio.h>
#include <stdlib.h>

int main(){

    int length, i, j;
    printf("Size of array: ");
    scanf("%d", &length);
    int *grades = malloc(length * sizeof(int));

    if ( grades == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for(i = 0; i< length;i++){
        printf("Element at index %d: ", i);
        scanf("%d", grades + i);
    }
    
    printf("\nElements: ");
    for(i= 0; i < length ; i++){
        if (i == length - 1) printf("%d ", *(grades + i));       
        else printf("%d, ", *(grades + i));
    }

    for(i= 0; i < length - 1; i++){
        for(j = 0; j < length - 1 - i; j++){
             if (*(grades + j) < *(grades + j + 1)){
                int temp = *(grades + j);
                *(grades + j) = *(grades + j + 1);
                *(grades + j + 1) = temp;
             } 
        }
    }
    printf("\nMaximum number is %d\n", *grades);
    printf("Minimum number is %d\n", *(grades + length - 1));
    free(grades);
}
