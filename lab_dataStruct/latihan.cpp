#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_SIZE 100

struct Booking{
    char nama[100];
    char phoneNumber [20];
    int age;
    char roomType[100];
    int stayDuration;
    char bookingID[10];
    Booking *next;
} *bookings[HASH_SIZE];

Booking* createBooking (char* nama, char* phoneNum, int age, char*roomType, int stayDuration){
    Booking *newBooking = (Booking*)malloc(sizeof(Booking));
    strcpy (newBooking->nama, nama);
    strcpy (newBooking->phoneNumber, phoneNum);
    newBooking->age = age;
    strcpy (newBooking->roomType, roomType);
    newBooking->stayDuration = stayDuration;
    strcpy (newBooking->bookingID, generateID(roomType));
    newBooking->next = NULL;
    return newBooking;
}

void pushHash (Booking* c){
    int key = getHashKeyMidSquare(c->bookingID);
    if (bookings[key] == NULL){
        bookings[key] = c;
    } else {
        Booking * temp = bookings[key];
        while (temp != NULL && temp->next != NULL){
            temp = temp->next;
        }
        temp->next = c;
    }
}

void pop (char* id){
    int key = getHashKeyMidSquare(id);
    if (bookings[key] == NULL){
        puts ("Not Found");
        return;
    } else if (strcmp (bookings[key]->bookingID, id) == 0){
        bookings[key] = NULL;
    } else {
        Booking* temp = bookings[key];
        while (temp != NULL && strcmp (temp->next->bookingID, id) == 0){
            temp = temp->next;
        }
        Booking* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop); 
        return;
    }
    puts ("Data Not Found");
    return;
}

void viewBookings(){
    for (int i = 0; i < HASH_SIZE; i++){
        if (bookings[i]){
            Booking *temp = bookings[i];
            while (temp){
                printf ("Nama : %s\n", temp->nama);
                printf ("Phone Number : %s\n", temp->phoneNumber);
                printf ("Age : %d\n", temp->age);
                printf ("Room Type : %s\n", temp->roomType);
                printf ("Stay Duration : %d\n", temp->stayDuration);
                printf ("Booking ID : %s\n", temp->bookingID);
                puts ("");
                temp = temp->next;
            }
        }
    }
}

void printMenu (){
    system ("clear");
    puts ("+---------------------+");
    puts ("|  Hotel GrAnsylvania |");
    puts ("+---------------------+");
    puts ("1. Booking Hotel");
    puts ("2. View Bookings");
    puts ("3. Delete Bookings");
    puts ("4. Exit");
}

char* generateID (char* roomtype){
    char* id = (char*)malloc(sizeof(char));
    sprintf (id, "%c%c%c%d%d%d", toupper(roomtype[0]), toupper(roomtype[1]), rand() % 10, rand() % 10);
    return id;
}

int getHashKeyMidSquare(char* id){
    /*
    1. Jumlahin semuanya di sum
    2. Kuadratin
    3. Ambil tengahnya
    4. Kalao ganjil  banyak digitnya ambil tengahnya
    5. Kalau genap, ambil, tengah sama sebelah kanannya*/

    int sumID = 0;
    for (int i = 2; i < 5; i++){
        sumID += id[i] - '0';
    }

    sumID *= sumID;
    char string [1000000000];
    sprintf (string, "%d", sumID);
    int l = strlen (string);
    int key = -1;

    if (l % 2 == 1){
        key = string[l / 2] - '0';
    } else {
        key = (string[l/2 - 1] - '0') * 10 + (string[l/2] - '0');
        // char mid[3] = {string[l / 2 - 1], string [l/ 2], '\0'};
        // key = atoi (mid);
    }

    return key % HASH_SIZE;
}

int main (){
    int input = -1;
    srand(time(NULL));
    while (1){
        printMenu();
        do {
        printf ("Choose menu : ");
        scanf ("%d", &input);getchar();
        } while (input < 1 || input > 4);
        int index;
        switch (input){
            case 1:
                createBooking();
                break;
            case 2:
                viewBookings();
                break;
            case 3:
                char bookingID[10];
                printf ("Input Booking ID : ");
                scanf ("%[^\n]", bookingID);getchar();
                index = getHashIndex(bookingID);
                popMid(index, bookingID);
                break;
            case 4:
                return 0;
                break;
            default:
                puts ("Invalid Input");
                break;
        }
    }
}