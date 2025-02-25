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

int getHashIndex(char* bookingID){
    int x = 0;
    for (int i = 2; i < 5; i++){
        x += bookingID[i] - '0';
    }
    return (x-1) % HASH_SIZE;
}

char toUpper(char c){
    if (c >= 'a' && c <= 'z'){
        return c - 32;
    }
    return c;
}

char* generateID (char* roomtype){
    //rand() % (max_number + 1 - minimum_number) + minimum_number
    char *id = (char*) malloc (sizeof(char) * 7);
    for (int i = 0; i < 5 ; i++){
        id[i] = i < 2 ? toUpper(roomtype[i]) : (rand() % 10) + '0';
    }
    id[5] = '\0';
    return id;
}

struct Booking* newBooking(char* nama, char* phoneNumber, int age, char* roomType, int stayDuration){
    Booking *temp = (Booking*) malloc (sizeof(Booking));
    strcpy(temp->nama, nama);
    strcpy(temp->phoneNumber, phoneNumber);
    temp->age = age;
    strcpy(temp->roomType, roomType);
    temp->stayDuration = stayDuration;
    strcpy(temp->bookingID, generateID(roomType));
    temp->next = NULL;
    return temp;
}


void pushTail (struct Booking* newBooking){
    int index = getHashIndex(newBooking->bookingID);
    if (!bookings[index]){
        bookings[index] = newBooking;
    } else {
        Booking *temp = bookings[index];
        while (temp->next){
            temp = temp->next;
        }
        temp->next = newBooking;
    }
}


void createBooking(){
    char nama[100];
    char phoneNumber [20];
    int age;
    char roomType[100];
    int stayDuration;

    do {
    printf ("Input Full Name [3..30] : ");
    scanf ("%[^\n]", nama);getchar();
        if (strlen(nama) < 3 || strlen(nama) > 30){
            puts ("Full Name lenght must between 3-30 characters");
        }
    } while (strlen(nama) < 3 || strlen(nama) > 30);
    
    int space = 0;
    do {
    printf ("Input Phone Number [10..12] : ");
    scanf ("%[^\n]", phoneNumber);getchar();
        if (strlen(phoneNumber) < 10 || strlen(phoneNumber) > 12){
            puts ("Phone Number lenght must between 10-12 characters");
        }
        
    for (int i = 3; i < strlen(phoneNumber); i++){
        if (phoneNumber[i] == ' '){
            space++;
        }
    }
    } while (strncmp(phoneNumber, "+62 ",  4) != 0 || strlen (phoneNumber) - (space + 3) != 11|| space < 1);

    do {
    printf ("Input Age [Minimum 18] : ");
    scanf ("%d", &age);getchar();
        if (age < 18){
            puts ("Age must be 18 or above");
        }
    } while (age < 18);

    do {
    printf ("Input Room Type [Reguler, Deluxe, Suite] : ");
    scanf ("%[^\n]", roomType);getchar();
        if (strcmp(roomType, "Reguler") != 0 && strcmp(roomType, "Deluxe") != 0 && strcmp(roomType, "Suite") != 0){
            puts ("Room Type must be Reguler, Deluxe, or Suite");
        }
    } while (strcmp(roomType, "Reguler") != 0 && strcmp(roomType, "Deluxe") != 0 && strcmp(roomType, "Suite") != 0);

    do {
    printf ("Input How Many Night You will Stay [1..30] : ");
    scanf ("%d", &stayDuration);getchar();
        if (stayDuration < 1 || stayDuration > 30){
            puts ("You can't stay less than 1 night or more than 30 nights");
        }
    } while (stayDuration < 1 || stayDuration > 30);

    pushTail(newBooking(nama, phoneNumber, age, roomType, stayDuration));
    puts ("Booking Success");
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

void popMid (int index, char* bookingID){
    Booking *temp = bookings[index];
    Booking *prev = NULL;
    while (temp && strcmp(temp->bookingID, bookingID) != 0){
        prev = temp;
        temp = temp->next;
    }
    if (temp){
        if (!prev){
            bookings[index] = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
    }
}

void printmenu(){
    puts ("+---------------------+");
    puts ("|  Hotel Gransylvania |");
    puts ("+---------------------+");
    puts ("1. Booking Hotel");
    puts ("2. View Bookings");
    puts ("3. Delete Booking"); 
    puts ("4. Exit");
}

int main (){
    int input = -1;
    srand(time(NULL));
    while (1){
        printmenu();
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