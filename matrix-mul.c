#include <stdio.h>
#include <stdlib.h>

int main(){
    int r1, r2, c1, c2, i, j;
    printf("Number of rows in matrix 1: ");
    scanf("%d", &r1);
    printf("Number of columns in matrix 1: ");
    scanf("%d", &c1);
    printf("Number of rows in matrix 2: ");
    scanf("%d", &r2);
    if(c1 != r2){
        printf("First column and second row number must be same!\n");
        return 0;
    }
    printf("Number of columns in matrix 2: ");
    scanf("%d", &c2);
    int **arr1 = malloc(r1 * sizeof(int*));

    if (arr1 == NULL){
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (i = 0; i < r1; i++){
        *(arr1 + i) = malloc(c1 * sizeof(int));
        if(*(arr1 + i) == NULL){
            printf("Memory allocation failed.\n");
            for(j = 0; j < i; j++) free(*(arr1 + j));
            free(arr1);
            return 0;
        }
    }
    printf("\nAllocating values for 1st matrix...\n");

    for(i = 0; i < r1; i++){
        for(j = 0; j < c1; j++){
            printf("Value at row %d column %d: ", i + 1, j + 1);
            scanf("%d", *(arr1 + i) + j);
        }
    }

    int **arr2 = malloc(r2 * sizeof(int*));

    if (arr2 == NULL){
        printf("Memory allocation failed.\n");
        for(j = 0; j < r1; j++) free(*(arr1 + j));
        free(arr1);
        return 0;
    }

    for (i = 0; i < r2; i++){
        *(arr2 + i) = malloc(c2 * sizeof(int));
        if(*(arr2 + i) == NULL){
            printf("Memory allocation failed.\n");
            for(j = 0; j < i; j++) free(*(arr2 + j));
            for(j = 0; j < r1; j ++) free(*(arr1 + j));
            free(arr2);
            free(arr1);
            return 0;
        }
    }
    printf("\nAllocating values for 2nd matrix...\n");

    for(i = 0; i < r2; i++){
        for(j = 0; j < c2; j++){
            printf("Value at row %d column %d: ", i + 1, j + 1);
            scanf("%d", *(arr2 + i) + j);
        }
    }
    
    int **arr3 = malloc( r1 * sizeof(int*));

    if (arr3 == NULL){
        printf("Memory allocation failed.\n");
        for(j = 0; j < r1; j++) free(*(arr1 + j));
        for(j = 0; j < r2; j ++) free (*(arr2 + j));
        free(arr2);
        free(arr1);
        return 0;
    }
    
    for (i = 0; i < r1; i++){
        *(arr3 + i) = malloc(c2 * sizeof(int));
        if(*(arr3 + i) == NULL){
            printf("Memory allocation failed.\n");
            for(j = 0; j < i; j++) free(*(arr3 + j));
            for(j = 0; j < r1; j ++) free(*(arr1 + j));
            for(j = 0; j < r2; j++) free(*(arr2 + j));
            free(arr3);
            free(arr2);
            free(arr1);
            return 0;
        }
    }

    for(i = 0; i < r1; i++){
        for(j = 0; j < c2; j++){
            int sum = 0;
            for(int k = 0; k < c1; k++) sum += (*(*(arr1 + i) + k)) * (*(*(arr2 + k) + j));
            *(*(arr3 + i) + j) = sum;
        }
    }
    printf("\n");
    for (i = 0; i < r1; i ++){
        for(j = 0; j < c2; j++) printf("%d ", *(*(arr3 + i) + j));
        printf("\n");
    }
        
    for(i = 0; i < r1; i++) free(*(arr1 + i));
    for(i = 0; i < r2; i++) free(*(arr2 + i));
    for(i = 0; i < r1; i++) free(*(arr3 + i));
    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}
