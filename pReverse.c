#include <stdio.h>

void rev(char *word, int size, int i, int j){
     if( j > i){
        char temp = word[i];
        word[i] = word[j];
        word[j] = temp;
        rev(word, size, i + 1, j - 1);
     }
}
int main(){
    int size;
    printf("Size of word: ");
    scanf("%d", &size);
    char word[size + 1];
    printf("Text: ");
    scanf("%s", word);
    rev(word, size, 0, size - 1);
    printf("%s\n", word);
}
