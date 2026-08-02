#include <stdio.h>
#include <stdlib.h>

void rev(char *word, int size, int i, int j){
     if( j > i){
        char temp = *(word + i);
        *(word + i) = *(word + j);
        *(word + j) = temp;
        rev(word, size, i + 1, j - 1);
     }
}
int main(){
    int size;
    printf("Size of word: ");
    scanf("%d", &size);
    char *word = malloc((size + 1) * sizeof(char));

    if(word == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Text: ");
    scanf("%s", word);
    rev(word, size, 0, size - 1);
    printf("%s\n", word);
    free(word);
}
