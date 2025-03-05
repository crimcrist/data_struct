#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define HASH_SIZE 100

struct Borrow {
    char fullName[50];
    char id[10];
    char bookTitle[100];
    int duration;
    char libraryID[10];
    struct Borrow* next;
} *HashTable[HASH_SIZE];

int HashKey(char* id) {
    int sum = 0;
    for (int i = 2; i < 5; i++) {
        sum += id[i] - '0';
    }
    sum *= sum;
    char string[100];
    snprintf(string, sizeof(string), "%d", sum);
    int x = strlen(string);
    int hashKey = 0;
    if (sum % 2 == 1) {
        hashKey = string[x / 2] - '0';
    } else {
        hashKey = (string[x / 2 - 1] - '0') * 10 + (string[x / 2] - '0');
    }
    return hashKey % HASH_SIZE;
}

char* generatedID(char* bookTitle) {
    srand(time(NULL));
    char* id = (char*)malloc(6 * sizeof(char));
    id[0] = toupper(bookTitle[0]);
    id[1] = toupper(bookTitle[1]);
    for (int i = 2; i < 5; i++) {
        id[i] = rand() % 10 + '0';
    }
    id[5] = '\0';
    return id;
}

void push(struct Borrow* newBorrow) {
    int index = HashKey(newBorrow->id);
    newBorrow->next = NULL;
    if (HashTable[index] == NULL) {
        HashTable[index] = newBorrow;
    } else {
        struct Borrow* temp = HashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBorrow;
    }
}

void BorrowBook() {
    struct Borrow* newBorrow = (struct Borrow*)malloc(sizeof(struct Borrow));

    do {
        printf("Enter your full name: ");
        scanf(" %[^\n]", newBorrow->fullName);
        getchar();
    } while (strlen(newBorrow->fullName) < 3 || strlen(newBorrow->fullName) > 30);

    do {
        printf("Enter your Library ID (format: LIB-xxxxx): ");
        scanf(" %s", newBorrow->libraryID);
        getchar();
    } while (strncmp(newBorrow->libraryID, "LIB-", 4) != 0 || strlen(newBorrow->libraryID) != 9);

    do {
        printf("Enter your Book Title: ");
        scanf(" %[^\n]", newBorrow->bookTitle);
        getchar();
    } while (strlen(newBorrow->bookTitle) < 3 || strlen(newBorrow->bookTitle) > 30);

    do {
        printf("Enter Borrowing duration (1-30 days): ");
        scanf("%d", &newBorrow->duration);
    } while (newBorrow->duration < 1 || newBorrow->duration > 30);

    strcpy(newBorrow->id, generatedID(newBorrow->bookTitle));

    push(newBorrow);
    puts("----------------------------------");
    puts(" Book Borrowed Successfully");
    puts("----------------------------------");
    printf("Borrowing ID: %s\n", newBorrow->id);
    printf("Borrowing Name: %s\n", newBorrow->fullName);
    printf("Library ID: %s\n", newBorrow->libraryID);
    printf("Book Title: %s\n", newBorrow->bookTitle);
    printf("Duration: %d days\n", newBorrow->duration);
}

void printMenu() {
    puts("================================");
    puts("  BookHaven Library Management  ");
    puts("================================");
    puts("1. Borrow a Book");
    puts("2. View Borrowed Books");
    puts("3. Return a Book");
    puts("4. Exit");
    puts("=================================");
}

void viewBorrow() {
    int found = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (HashTable[i] != NULL) {
            struct Borrow* temp = HashTable[i];
            while (temp != NULL) {
                found = 1;
                puts("----------------------------------");
                puts(" Borrowed Books List");
                puts("----------------------------------");
                printf("Borrowing ID: %s\n", temp->id);
                printf("Borrowing Name: %s\n", temp->fullName);
                printf("Library ID: %s\n", temp->libraryID);
                printf("Book Title: %s\n", temp->bookTitle);
                printf("Duration: %d days\n", temp->duration);
                temp = temp->next;
            }
        }
    }
    if (found == 0) {
        puts("No Books Borrowed yet");
    }
}

void returnBook() {
    char id[10];
    printf("Enter Borrowing ID to return: ");
    scanf("%s", id);
    int index = HashKey(id);
    if (HashTable[index] != NULL) {
        struct Borrow* prev = NULL;
        struct Borrow* temp = HashTable[index];
        while (temp) {
            if (strcmp(temp->id, id) == 0) {
                if (prev == NULL) {
                    HashTable[index] = temp->next;
                } else {
                    prev->next = temp->next;
                }
                puts("Book Returned Successfully");
                free(temp);
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }
    puts("Book not found");
}

int main() {
    int choice;
    while (1) {
        printMenu();
        do {
        printf(">> ");
        scanf("%d", &choice);
        } while (choice < 1 || choice > 4);

        switch (choice) {
            case 1: 
                BorrowBook(); 
                break;
            case 2: 
                viewBorrow(); 
                break;
            case 3: 
                returnBook(); 
                break;
            case 4: 
                return 0;
        }
    }
}
