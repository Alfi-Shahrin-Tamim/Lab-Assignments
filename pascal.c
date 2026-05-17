#include <stdio.h>

int main(){
   int n,i,j,k,val;
   val = 1;
   printf("Give a value for n: \n");
   scanf("%d", &n);
   for(i = 0; i < n;i++){
    val = 1;
    for(k=0;k<=i;k++){
        printf("%d ", val);
        val = val *((i-k)/(k+1));
    }
    printf("\n");
   }
}
