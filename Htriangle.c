#include <stdio.h>

int main(){
    int n,cp,l,r;
    printf("Give a value for n: \n");
    scanf("%d", &n);
    cp = 2*n -1;
    l = n - 1;
    r = n + 1;
    for(int i = 1;i<=n; i++){
        if(i == 1){
            for(int j=1;j<=cp;j++){
            if(j == n) {printf("*");}
                else {printf(" ");}
            }
            printf("\n");
            continue;
        }
        if(i == n){
            for(int j=1;j<=cp;j++) printf("*");
            printf("\n");
            continue;
        }       
        for(int j=1;j<=cp;j++){
            if(j == l || j == r){
                printf("*");
            }else {
            printf(" ");
            }            
        }
        l--;
        r++;
        printf("\n");
    } 
}
