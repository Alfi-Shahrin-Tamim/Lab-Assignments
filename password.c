#include <stdio.h>

int main(){
   char b;
   printf("Give a password: \n");
   int cap,small, spcl,digt, length;
   cap = 0;
   small = 0;
   spcl = 0;
   digt = 0;
   while(1){
   printf("Enter password length: ");
   scanf("%d", &length);
   if( length >= 8) break;
   }
   printf("Enter a password: ");
   for(int i = 1; i<= length;i++){
       scanf("%c", &b);
       int a=b;
       if(a >= 65 && a<=90){
        cap = 1;
       }
       if(a >= 97 && a<= 122){
        small = 1;
       }
       if((a>=32 && a <=47) || (a>=58 && a<=64) || (a>=91 && a <=96) || (a>=123 && a <=126)){
        spcl = 1;
       }
       if(a>= 48 && a<=57){
        digt = 1;
       }
   }
   if (cap == 1 && spcl == 1 && small == 1 && digt == 1){
    printf("Valid password\n");
   }
   else printf("Invalid password.\n");
}
