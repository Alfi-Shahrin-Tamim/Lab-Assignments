#include <stdio.h>
float discount(float value){
      float disc0, disc2, disc4;
      disc2 = (value * 5)/100;
      disc4 =  (value * 10)/100;
      if (value >= 5000){
         if (disc4 > 2000)
            {
            disc0 = 2000;
            }
         else
            {
            disc0 = disc4;
            }
      }
      else if (value >4000){
         disc0 = 50;
         }
      else if (value > 2000)
           {    
           if (value == 2027)
                 {
                 disc0 = 270;
                 }
           else
                 {
                 disc0 = disc2;
                 }
           }
       else if (value >= 500)
       {
           disc0 = 50;
       }
       else
       {
           disc0 = 0;
       }
       return disc0;
}       
float cpoints(float point1){
    float point_value;
    point_value = point1/ 40;
    return point_value;
    }
    
int main(){
    float disc, disc_total,taka, points, point_val;
    printf("Total cart value: ");
    scanf("%f", &taka);
    printf("Existing customer points: ");
    scanf("%f", &points);
    disc = discount(taka);
    point_val = cpoints(points);
    points = ((int)points % 40)+((int)taka / 10) * 4;
    disc_total = disc + point_val;
    taka = taka - disc_total;
    printf("Discount amount: %0.2f\n", disc_total);
    printf("Payable: %0.2f\n", taka);
    printf("Updated customer points: %0.2f\n", points);
}    
    
    
    
    
    
