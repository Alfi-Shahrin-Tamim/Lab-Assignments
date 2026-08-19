#include <stdio.h>
#include <string.h>

int main(){
    FILE *file = fopen("titanic.csv", "r");
    if (file == NULL){
        printf("Error opening file!\n");
        return 1;
    }

    char words[1000];

    int male_total = 0, male_survived = 0;
    int female_total = 0, female_survived = 0;

    fgets(words, sizeof(words), file);

    while(fgets(words, sizeof(words), file)){
        char *first = strchr(words, ',');
        if(first == NULL) continue;
        char survived = *(first + 1);
        if(strstr(words, ",male,") != NULL){
            male_total++;
            if(survived == '1') male_survived++;
        }
        else if(strstr(words, ",female,") != NULL){
            female_total++;
            if(survived == '1') female_survived++;
        }       
    }
    float male_percent = 0, female_percent = 0;
    if(male_total != 0) male_percent = ((float)male_survived / male_total) * 100;
    if(female_total != 0) female_percent = ((float)female_survived/ female_total) * 100;

    printf("Total males: %d  Male survivors: %d\n", male_total, male_survived);
    printf("Percentage of male survivors: %0.2f\n", male_percent);
 
    printf("Total females: %d  Female survivors: %d\n", female_total, female_survived);
    printf("Percentage of female survivors: %0.2f\n", female_percent);  
    fclose(file);
    return 0;

}
