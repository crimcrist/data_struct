#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int cardCounter = 100;

struct Card {
    int ID;
    char name[25];
    int price;
    struct Card *next;
} *head, *tail, *current;

void pushCard(char* cardName) {
    srand(time(NULL));
    current = (struct Card*)malloc(sizeof(struct Card));
    strcpy(current->name, cardName);
    current->ID = cardCounter++;
    current->price = rand() % 9000 + 1000;
    current->next = NULL;

    if (!head) {
        head = tail = current;
    } else if (strcmp(cardName, head->name) < 0) {
        current->next = head;
        head = current;
    } else if (strcmp(cardName, tail->name) > 0) {
        tail->next = current;
        tail = current;
    } else {
        struct Card *temp = head;
        while (strcmp(temp->next->name, cardName) < 0) {
            temp = temp->next;   
        }
            current->next = temp->next;
            temp->next = current;
    }
}

void popCard(char cardName[]) {
    if (!head) return;

    if (strcmp(head->name, cardName) == 0) {
        struct Card *temp = head;
        head = head->next;
        if (!head) tail = NULL;
        free(temp);
    } else {
        struct Card *temp1 = head;
        struct Card *temp2 = head->next;

        while (strcmp(temp2->name, cardName) != 0) {
            temp1 = temp2;
            temp2 = temp2->next;
        }

        if (temp2) {
            temp1->next = temp2->next;
            if (temp2 == tail) {
                tail = temp1;
            }
            free(temp2);
        }
    }
}

void printCards() {
    if (!head) {
        printf("No cards available.\n");
        return;
    }

    struct Card *temp = head;
    while (temp) {
        printf("ID    : %d\n", temp->ID);
        printf("Name  : %s\n", temp->name);
        printf("Price : %d\n", temp->price);
        printf("---------------------------\n");
        temp = temp->next;
    }
}

void buyCard() {
    char cardName[25];
    printf("Enter card name to buy: ");
    scanf("%24[^\n]", cardName);
    getchar();
    pushCard(cardName);
    printf("Card '%s' has been successfully added.\n", cardName);
}

void showCards() {
    printf("Current cards:\n");
    printCards();
    printf("===========================\n");
}

void deleteCard() {
    char cardName[25];
    printf("Enter card name to delete: ");
    scanf("%24[^\n]", cardName);
    getchar();
    popCard(cardName);
    printf("Card '%s' has been successfully deleted.\n", cardName);
}

void changeCard() {
    buyCard();
    deleteCard();
    showCards();
}

void enterToContinue() {
    printf("Press Enter to continue...\n");
    getchar();
}

int main() {
    srand(time(NULL));
    char Nama[25];
    strcpy(Nama, "Vulpix");
    pushCard(Nama);
    srand(time(NULL));

    strcpy(Nama, "Diglett");
    pushCard(Nama);
    srand(time(NULL));

    strcpy(Nama, "Zubat");
    pushCard(Nama);
    srand(time(NULL));

    strcpy(Nama, "Nidoran");
    pushCard(Nama);

    int choice;
    do {
        system("cls");
        printf("CARD MANAGEMENT SYSTEM\n");
        printf("1. Buy Card\n");
        printf("2. Show Cards\n");
        printf("3. Change Card\n");
        printf("4. Delete Card\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                buyCard();
                enterToContinue();
                break;
            case 2:
                showCards();
                enterToContinue();
                break;
            case 3:
                changeCard();
                enterToContinue();
                break;
            case 4:
                deleteCard();
                enterToContinue();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n"); getchar ();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                enterToContinue();
        }
    } while (choice != 5);

    return 0;
}
