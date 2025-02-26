#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
    char id[20];
    char address[25];
    char type [10];
    int priority; // 1 Instant, 2 Standart, 3 Economy
    struct Node* next;
} *head;


void generateID (char* id){
    id[0] = 'C';
    id[1] = 'P';
    id[2] = 'X';

    for (int i = 3; i < 6; i++){
        int r = rand() % 36;
        id[i] = (r < 10) ? r + '0' : r - 10 + 'A';
    }
    id[6] = '\0';
}

int priority (char* type){
    if (strcmp (type, "Instant") == 0) return 1;
    if (strcmp (type, "Standard") == 0) return 2;
    if (strcmp (type, "Economy") == 0) return 3;
}

void insertPackage(){
    struct Node *newNode = (Node*)malloc(sizeof(Node));
    do {
    printf ("Enter the Address: ");
    scanf ("%[^\n]", newNode->address);
    } while (strncmp (newNode->address, "Jl.", 3) != 0 || strlen(newNode->address) < 5 || strlen(newNode->address) > 25);

    do {
        printf ("Enter the Type [Instant/Standart/Economy]: ");
        scanf ("%s", newNode->type);
    } while (strcmp(newNode->type, "Instant") != 0 && strcmp(newNode->type, "Standard") != 0 && strcmp(newNode->type, "Economy") != 0);

    newNode->priority = priority(newNode->type);
    generateID(newNode->id);

    if (head == NULL) {
        newNode->next = head;
        head = newNode;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL && temp->next->priority <= newNode->priority){
            temp = temp->next;
        } 
        if (temp->next == NULL){
            temp->next = newNode;
        }else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    printf ("Package Copied Successfully\n");
}

void sendPackage (){
    if (head == NULL) {
        printf ("No Package Available\n");
        return;
    }

    Node* temp = head;
    head = head->next;

    printf ("Package ID: %s\n", temp->id);
    printf ("Address: %s\n", temp->address);
    printf ("Type: %s\n", temp->type);
    printf ("Priority: %d\n", temp->priority);
    free (temp);
    printf ("Package Sent Successfully\n");
}

void viewAll (){
    if (head == NULL){
        printf ("No Package Available\n");
        return;
    }
    Node *temp = head;
    while (temp != NULL){
        puts ("====================");
        printf ("Package ID: %s\n", temp->id);
        printf ("Address: %s\n", temp->address);
        printf ("Type: %s\n", temp->type);
        printf ("Priority: %d\n", temp->priority);
        temp = temp->next;
        puts ("====================");
    }
}

void exitProgram (){
    Node* temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free (temp);
    }
    printf ("Thank You\n");
}

int main (){
    int choice = 0;
    while (1){
        printf ("\n COPI EXPRESS \n");
        printf ("1. Insert new Packages\n");
        printf ("2. Send Package\n");
        printf ("3. View All\n");
        printf ("4. Exit\n");

        do {
            printf (">> ");
            scanf ("%d" , &choice);
        } while (choice < 1 || choice > 4);
     
        switch (choice){
            case 1 :
                insertPackage();
                break;
            case 2 :
                sendPackage();
                break;
            case 3 :
                viewAll();
                break;
            case 4 :
                exitProgram();
                return 0;
        }
    }
}