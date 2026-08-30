#include <stdio.h>
#define MAX_SIZE 150
typedef struct {
    int id;
    char name[101];
    float mid;
    float final;
    float total;
} Student;
int checkStudents(const Student roster[], int size, int searchID) {
    for (int i = 0; i < size; i++) {
        if (roster[i].id == searchID) {
            return 1;
        }
    }
    return 0;
}
void promptStudentDetails(Student *studentPtr) {
    printf("Name of Student: ");
    scanf("%s", studentPtr->name);
    printf("Mid term marks: ");
    scanf("%f", &studentPtr->mid);
    printf("Final term marks: ");
    scanf("%f", &studentPtr->final);
    studentPtr->total = studentPtr->mid + studentPtr->final;
}
void displayStudent(const Student *studentPtr) {
    printf("ID: %d\n", studentPtr->id);
    printf("Name: %s\n", studentPtr->name);
    printf("Mid term marks: %.2f\n", studentPtr->mid);
    printf("Final term marks: %.2f\n", studentPtr->final);
    printf("Total marks: %.2f\n", studentPtr->total);
}
int findStudentIndexByID(const Student roster[], int size, int searchID) {
    for (int i = 0; i < size; i++) {
        if (roster[i].id == searchID) {
            displayStudent(&roster[i]);
            return i;
        }
    }
    printf("Student does not exist.\n");
    return -1;
}
int findTopStudentIndex(const Student roster[], int size) {
    if (size == 0) {
        printf("There are no students.\n");
        return -1;
    }
    int maxIndex = 0;
    float maxTotal = roster[0].total;
    for (int i = 1; i < size; i++) {
        if (roster[i].total > maxTotal) {
            maxTotal = roster[i].total;
            maxIndex = i;
        }
    }
    printf("Top student:\n");
    displayStudent(&roster[maxIndex]);
    return maxIndex;
}
int main() {
    Student courseRoster[MAX_SIZE];
    int rosterSize = 0;

    printf("STUDENT ENROLLMENT DOCUMENTATION\n\n");

    while (1) {
        int option;
        printf("\n1. Add Student\n2. Display Full Roster\n3. Find Student by ID\n4. Show Top Student\n0. Exit\n");
        printf("Choice: ");
        scanf("%d", &option);

        if (option == 0) {
            break;
        }
        else if (option == 1) {
            int id;
            printf("Enter ID of Student: ");
            scanf("%d", &id);

            if (checkStudents(courseRoster, rosterSize, id)) {
                printf("Student ID already exists.\n");
            }
            else if (id < 1) {
                printf("Invalid ID.\n");
            }
            else if (rosterSize >= MAX_SIZE) {
                printf("Roster is full.\n");
            }
            else {
                courseRoster[rosterSize].id = id;
                promptStudentDetails(&courseRoster[rosterSize]);
                rosterSize++;
            }
        }
        else if (option == 2) {
            printf("List of Students:\n");
            if (rosterSize == 0) {
                printf("No students enrolled.\n");
            }
            for (int i = 0; i < rosterSize; i++) {
                displayStudent(&courseRoster[i]);
                printf("\n");
            }
        }
        else if (option == 3) {
            int id;
            printf("Enter ID of Student: ");
            scanf("%d", &id);
            findStudentIndexByID(courseRoster, rosterSize, id);
        }
        else if (option == 4) {
            findTopStudentIndex(courseRoster, rosterSize);
        }
        else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}
