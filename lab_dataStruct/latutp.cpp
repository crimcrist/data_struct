#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define HASH_TABLE 100

struct Booking {
    char fullName [50];
    char phoneNumber [20];
    int age;
    char roomType [10];
    int stayDuration;
    char id [10];
    Booking* next;
} *bookings [HASH_TABLE];

void printMenu (){
    puts ("+------------------------+");
    puts ("|   Hotel GrAnsylvania   |");
    puts ("+------------------------+");
    puts ("1. Booking Hotel");
    puts ("2. View Bookings");
    puts ("3. Delete Booking");
    puts ("4. Exit");
}

int hash (char *key){
    int sum = 0;
    for (int i = 2; i < 5; i++){
        sum += key[i] - '0';
    }
    return sum % HASH_TABLE;
}

struct Booking *newBooking (char *nama, char *phoneNumber, int age, char *roomType, int stayDuration){
    struct Booking *newBooking = (struct Booking*)malloc(sizeof(struct Booking));
    strcpy (newBooking->fullName, nama);
    strcpy (newBooking->phoneNumber, phoneNumber);
    newBooking->age = age;
    strcpy (newBooking->roomType, roomType);
    newBooking->stayDuration = stayDuration;
    strcpy (newBooking->id, generateID(roomType));
    return newBooking;
}

char* generateID (char *roomType){
    srand (time(NULL));
    char *id = (char*)malloc(sizeof(char));
    id[0] = toupper(roomType[0]);
    id[1] = toupper(roomType[1]);
    for (int i = 2; i < 5; i++){
        id[i] = rand() % 10 + '0';
    }
    return id;
}

void pushBooking (struct Booking *newBooking){
    int index = hash(newBooking->id);
    if (bookings[index] == NULL){
        bookings[index] = newBooking;
    } else {
        Booking* temp = bookings[index];
        while (temp->next){
            temp = temp->next;
        }
        temp->next = newBooking;
    }
}

void enterContinue(){
    puts ("Press ENTER to continue..."); getchar();
}
void bookingHotel (){
    char nama [50];
    char phoneNumber[20];
    int age;
    char roomType [20];
    int stayDuration;
    do {
        printf ("Input Full Name[3..30] : ");
        scanf ("%[^\n]", nama); getchar();
    } while(strlen(nama) < 3 || strlen(nama) > 30);

    do {
        printf ("Input Phone Number [10..12] : ");
        scanf ("%[^\n]", phoneNumber); getchar();   
    } while(strncmp (phoneNumber, "+62", 3) != 0 || strlen(phoneNumber) < 10 || strlen(phoneNumber) > 12);  

    do {
        printf ("Input Age [Minimum 18] : ");
        scanf ("%d", age); getchar();
    } while(age < 18);

    do {
        printf ("Input Room Type [Regular, Deluxe, Suite] : ");
        scanf ("%[^\n]", roomType); getchar();
    } while(strcmp(roomType, "Regular") != 0 && strcmp(roomType, "Deluxe") != 0 && strcmp(roomType, "Suite") != 0);

    do {
        printf ("Input Stay Duration [1..30] : ");
        scanf ("%d", stayDuration); getchar();
    } while(stayDuration < 1 || stayDuration > 30);

    pushBooking (newBooking(nama,phoneNumber, age, roomType, stayDuration));
    puts ("Booking Success");
    enterContinue();
}

void viewBookings (){
    for (int i = 0; i < HASH_TABLE; i++){
        if (bookings[i] != NULL){
            Booking* temp = bookings[i];
            while (temp){
                printf ("Full Name : %s\n", temp->fullName);
                printf ("Phone Number : %s\n", temp->phoneNumber);
                printf ("Age : %d\n", temp->age);
                printf ("Room Type : %s\n", temp->roomType);
                printf ("Stay Duration : %d\n", temp->stayDuration);
                printf ("ID : %s\n", temp->id);
                puts ("------------------------");
                temp = temp->next;
            }
        }
    }
    enterContinue();
}

void deleteBookings (){
    char id [10];
    printf ("Input ID : ");
    scanf ("%[^\n]", id); getchar();
    int index = hash(id);
    if (bookings[index] != NULL){
        Booking* temp = bookings[index];
        Booking* prev = NULL;
        while (temp){
            if (strcmp(temp->id, id) == 0){
                if (prev == NULL){
                    bookings[index] = temp->next;
                } else {
                    prev->next = temp->next;
                }
                free (temp);
                puts ("Booking Deleted");
                enterContinue();
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }
    puts ("Booking Not Found");
    enterContinue();
}

int main (){
    int choice;
    while (1){
        printMenu();
        do {
        printf (">> ");
        scanf ("%d", &choice);
        } while (choice < 1 || choice > 4);
        
        switch (choice){
            case 1 :
                bookingHotel();
                break;
            case 2 :
                viewBookings();
                break;
            case 3 :
                deleteBookings();
                break;
            case 4 :
                return 0;
        }
    }
}