#include <stdio.h>
#include <string.h>
#include <math.h>

int total = 0;
typedef struct {
    int id;
    char guest_name[100];
    int room_number;
    char room_type[20];
    char date[11];
    float rent;
    int status;
} Reservation;

void add_new(Reservation reserve[], Reservation room[]){
     if (total == 100){
        printf("Sorry!We have reached maximum reservation!\n");
     }
     else{
        int num_room;
        char check_date[11];
        printf("Your name: ");
        scanf("%s", reserve[total].guest_name);
        printf("Reservation ID: ");
        scanf("%d", &reserve[total].id);
        printf("Which room do you want to occupy(1-10)? ");
        scanf("%d", &num_room);
        if(num_room < 1 || num_room > 10){
            printf("Invalid room number.\n");
            return;
        }
        printf("Reservation date(DD/MM/YYYY): ");
        scanf("%s", check_date);        
        if (room[num_room - 1].status == 0){
            room[num_room - 1].status = 1;
            strcpy(room[num_room - 1].date , check_date);
            room[num_room - 1].id = reserve[total].id;
            strcpy(room[num_room - 1].guest_name, reserve[total].guest_name);
            reserve[total].room_number = room[num_room - 1].room_number;
            strcpy(reserve[total].room_type, room[num_room - 1].room_type);
            strcpy(reserve[total].date, check_date);  
            reserve[total].rent = room[num_room - 1].rent;
            reserve[total].status = 1;
            total += 1;                     
        }
        else if(strcmp(room[num_room - 1].date, check_date) != 0){
            reserve[total].room_number = room[num_room - 1].room_number;
            strcpy(reserve[total].room_type, room[num_room - 1].room_type);
            strcpy(reserve[total].date, check_date);  
            reserve[total].status = 1;
            reserve[total].rent = room[num_room - 1].rent;
            total += 1;             
        }
        else printf("The room is already reserved for your chosen date.\n");         
     } 
}

void search(Reservation reserve[], Reservation room[]){
    int check_id, i;
    printf("ID: ");
    scanf("%d", &check_id);
    for(i = 0; i < total; i++){
        if(reserve[i].id == check_id){
            printf("Name: %s\n", reserve[i].guest_name);
            printf("Room number: %d\n", reserve[i].room_number);
            printf("Room type: %s\n", reserve[i].room_type);
            printf("Reservation Date: %s\n", reserve[i].date);
            printf("Rent: %0.2f\n",reserve[i].rent);
            break;
        }
    }
    if (i == total) printf("Reservation for this ID does not exist.\n");
}

void show_date(Reservation reserve[], Reservation room[]){
    char check_date[11];
    int i;
    printf("Give the date(DD/MM/YYYY) you want to check: ");
    scanf("%s", check_date);
    printf("Reservations on this date are below:--> \n");
    for(i = 0; i < total; i++){
        if(strcmp(reserve[i].date, check_date) == 0){
            printf("ID: %d, Name: %s, Room: %d, Type: %s, Rent: %0.2f\n", reserve[i].id, reserve[i].guest_name, reserve[i].room_number, reserve[i].room_type, reserve[i].rent);
        }
    }     
}

void cancel(Reservation reserve[], Reservation room[]){
    int check_id, i;
    printf("Reservation ID you want to cancel: ");
    scanf("%d", &check_id);
    for(i = 0; i < total; i++){
        if(reserve[i].id == check_id){
            for(int j = 0; j < 10; j++){
                if(room[j].id == check_id){
                    room[j].id = 0;
                    room[j].guest_name[0] = '\0';
                    room[j].date[0] = '\0';
                    room[j].status = 0;
                    break;
                }
            }
            for(int j = i; j < total - 1; j++){
                reserve[j] = reserve[j+1];              
            }
            total--;
            break;
        }
    }

}

void show_vacant(Reservation reserve[], Reservation room[]){
     int i;
     printf("Vacant rooms are below:-->\n");
     for(i = 0; i < 10; i++){
        if(room[i].status == 0){
            printf("Room: %d, Type: %s, Rent: %0.2f\n",room[i].room_number, room[i].room_type, room[i].rent);
        }
     }      
}

void calc(Reservation reserve[]){
     int i;
     float sum = 0;
     for(i = 0; i < total; i++){
        if(reserve[i].status == 1) sum += reserve[i].rent;
     }
     printf("Total Yearly Revenue: %0.2f", sum);
}

int main(){
    int option,i, j;
    Reservation room[10];
    Reservation reserve[100];
    for(i = 0; i < 10; i++) room[i].status = 0;
    room[0].rent = 500;
    for(i = 0; i < 10; i++) room[i].room_number = 100 + i;
    for(i = 1; i < 10; i++) room[i].rent = room[i-1].rent + fmod(room[i-1].rent, 3);
    for(i = 0; i < 10; i++){
        if(i < 3) strcpy(room[i].room_type, "Single");
        else if (i < 7) strcpy(room[i].room_type, "Double");
        else strcpy(room[i].room_type, "Suite");
    }
    
    printf("WELCOME TO THE HOTEL!\n\n");

    while(1){
        printf("1. Add New Reservation\n");
        printf("2. Search Reservation by Reservation ID\n");
        printf("3. Display All Reservation by Date\n");
        printf("4. Cancel Reservation\n");
        printf("5. Display Vacant Rooms\n");
        printf("6. Calculate Total Yearly Revenue\n\n"); 
        printf("Press 0 if you want to exit\n");       
        printf("Choice: ");
        scanf("%d", &option);
        if(option == 1) add_new(reserve, room);
        else if(option == 2) search(reserve, room);
        else if(option == 3) show_date(reserve, room);
        else if(option == 4) cancel(reserve, room);
        else if(option == 5) show_vacant(reserve, room);
        else if(option == 6) calc(reserve);
        else if(option == 0) break;
    }
}
