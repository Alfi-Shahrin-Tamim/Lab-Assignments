#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *file = fopen("titanic.csv", "r");
    FILE *new_file = fopen("titanic_new.csv", "w");

    if (file == NULL || new_file == NULL){
        printf("Error opening files!\n");
        return 1;
    }

    char line[1000];

    if(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = '\0';
        fprintf(new_file, "%s,Age Category\n", line);      
    }
    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = '\0';
        int commas = 0;
        int in_quotes = 0;
        char *age_start = NULL;
        char *p = line;

        while(*p != '\0'){
            if(*p == '"') in_quotes = !in_quotes;
            else if (*p == ',' && in_quotes == 0){ 
               commas++;
               if(commas == 5){
                   age_start = p + 1;
                   break;
               }
            }   
            p++;
        }
        int category = 0;
        if(age_start != NULL && *age_start != ','){
            float age = atof(age_start);
            if(age >= 0 && age <= 18) category = 1;
            else if(age > 18 && age <= 40) category = 2;
            else if(age > 40) category = 3;
        }
        fprintf(new_file, "%s,%d\n", line, category);                
    }
    fclose(file);
    fclose(new_file);
    printf("Successfully created new csv file with the Age Category column.\n");
    return 0;
}
