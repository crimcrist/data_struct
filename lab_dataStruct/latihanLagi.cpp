#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define TABLE_SIZE 100

struct Borrower {
    char nama[100];
    char libraryID[50];
    char borrowingID[50];
    char bookTitle[55];
    int duration;
    struct Borrower* next;
} *hash_table[TABLE_SIZE];

int hashKey(char* id) {
    long long int idInt = atoi(&id[2]);
    idInt *= idInt;
    char string[100];
    sprintf(string, "%lld", idInt);
    int x = strlen(string);
    int key = -1;
    if (x % 2 == 1) {
        key = string[x / 2] - '0';
    } else {
        key = (string[x / 2 - 1] - '0') * 10 + (string[x / 2] - '0');
    }
    return key % TABLE_SIZE;
}

char* createId(char* bookTitle) {
    char* id = (char*)malloc(7 * sizeof(char));
    sprintf(id, "%c%c%d%d%d", toupper(bookTitle[0]), toupper(bookTitle[1]), rand() % 10, rand() % 10, rand() % 10);
    return id;
}

void push(struct Borrower* newNode) {
    int index = hashKey(newNode->borrowingID);
    newNode->next = NULL;
    if (hash_table[index] == NULL) {
        hash_table[index] = newNode;
    } else {
        struct Borrower* temp = hash_table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void enterToContinue() {
    puts("Press ENTER to continue..."); getchar();
}

void borrowBook() {
    system("cls");
    struct Borrower* newBorrow = (struct Borrower*)malloc(sizeof(struct Borrower));
    newBorrow->next = NULL;
    
    do {
        printf("Enter your full name: ");
        scanf(" %[^\n]", newBorrow->nama);
        getchar();
    } while (strlen(newBorrow->nama) < 3 || strlen(newBorrow->nama) > 30);

    int flagNum = 0;
    do {
        printf("Enter your Library ID (format: LIB-xxxxx): ");
        scanf("%s", newBorrow->libraryID);
        getchar();

        flagNum = 1;
        for (int i = 4; i < 9; i++) {
            if (!isdigit(newBorrow->libraryID[i])) {
                flagNum = 0;
                break;
            }
        }
    } while (strncmp(newBorrow->libraryID, "LIB-", 4) != 0 || flagNum == 0 || strlen(newBorrow->libraryID) != 9);

    do {
        printf("Enter your Book Title: ");
        scanf(" %[^\n]", newBorrow->bookTitle);
        getchar();
    } while (strlen(newBorrow->bookTitle) < 3 || strlen(newBorrow->bookTitle) > 30);

    do {
        printf("Enter Borrowing duration (1-30 days): ");
        scanf("%d", &newBorrow->duration);
    } while (newBorrow->duration < 1 || newBorrow->duration > 30);

    strcpy(newBorrow->borrowingID, createId(newBorrow->bookTitle));
    push(newBorrow);
    
    puts("----------------------------------");
    puts("Book Borrowed Successfully");
    puts("----------------------------------");
    printf("Borrowing ID: %s\n", newBorrow->borrowingID);
    printf("Borrowing Name: %s\n", newBorrow->nama);
    printf("Library ID: %s\n", newBorrow->libraryID);
    printf("Book Title: %s\n", newBorrow->bookTitle);
    printf("Duration: %d days\n", newBorrow->duration);
}

void viewBorrow() {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != NULL) {
            found = 1;
            struct Borrower* temp = hash_table[i];
            while (temp != NULL) {
                printf("Borrowing ID: %s\n", temp->borrowingID);
                printf("Borrower Name: %s\n", temp->nama);
                printf("Library ID: %s\n", temp->libraryID);
                printf("Book Title: %s\n", temp->bookTitle);
                printf("Duration: %d\n", temp->duration);
                puts("=========================================================");
                temp = temp->next;
            }
        }
    }
    if (found == 0) puts("No books borrowed yet");
}

void returnBook(){
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++){
        if(hash_table[i] != NULL){
            found = 1;
            Borrower *temp = hash_table[i];
            while (temp != NULL){
                printf ("Borrowing ID : %s\n", temp->borrowingID);
                printf ("Borrower Name : %s\n", temp->nama);
                printf ("Library ID : %s\n", temp->libraryID);
                printf ("Book Title : %s\n", temp->bookTitle);
                printf ("Duration : %d\n", temp->duration);
                puts ("=========================================================");
                temp = temp->next;
            }
        }
    }
    if (found == 0) {
        puts ("No books borrowed yet");
        enterToContinue();
        return;
    }

    char borrowingID[10];
    printf ("Enter Borrowing ID to return: ");
    scanf ("%[^\n]", borrowingID); getchar();
    int key = hashKey(borrowingID);
    Borrower *temp = hash_table[key];
    if (temp == NULL){
        puts ("No books found");
        enterToContinue();
        return;
    }

    if (strcmp(temp->borrowingID, borrowingID) == 0){
        hash_table[key] == NULL;
        free(temp);
    } else {
        while (temp->next != NULL && strcmp(temp->next->borrowingID, borrowingID) != 0){
            temp = temp->next;
        }

        Borrower *toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
    }
    puts ("Book Returned Succesfully");
    printf ("Borrowing ID : %s has been removed\n", borrowingID);
    enterToContinue();
}


void printMenu() {
    printf("1. Borrow Book\n");
    printf("2. View Borrowed Books\n");
    printf("3. Return Book\n");
    printf("4. Exit\n");
}

void menu() {
    srand(time(NULL));
    int input;
    while (1) {
        printMenu();
        do {
            printf(">> ");
            scanf("%d", &input);
        } while (input < 1 || input > 4);

        switch (input) {
            case 1: borrowBook(); break;
            case 2: viewBorrow(); break;
            case 3: returnBook(); break;
            case 4: return;
        }
    }
}

int main() {
    menu();
    return 0;
}
