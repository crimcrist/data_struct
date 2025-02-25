#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct spaceShuttle{
    char name [20];
    char ticket [20];
    struct spaceShuttle *next;
} *head;

int count = 0;

spaceShuttle *createNode (char* name, char* tiket){
    spaceShuttle *newNode = (spaceShuttle*)malloc(sizeof(spaceShuttle));
    strcpy (newNode->name, name);
    strcpy (newNode->ticket, tiket);
    newNode->next = NULL;
    return newNode;
}

void registerAstronout (char *name, char* tiket){
    spaceShuttle* newNode = createNode(name, tiket);

    if (!head){
        head = newNode;
        return;
    }

    if (strcmp(tiket, "VIP") == 0){
        if (strcmp (head->ticket, "REGULER") == 0){
            newNode->next = head;
            head = newNode;
            return;
        }

        spaceShuttle* temp = head;
        while (temp->next != NULL && strcmp (temp->next->ticket, "VIP") == 0){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        spaceShuttle *temp = head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    count++;
}

void removeAstronaut (char* nama){
    if (head == NULL){
        printf ("No astronaut registered\n");
        return;
    }

    if (strcmp (head->name, nama) == 0){
        spaceShuttle *temp = head;
        head = head->next;
        free(temp);
        count--;
        return;
    }

    spaceShuttle* temp = head;
    spaceShuttle* prev = NULL;

    while (temp != NULL && strcmp(temp->name, nama) != 0){
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL){
        prev->next = temp->next;
        free(temp);
        count--;
        printf ("Astronaut removed\n");
        return;
    } else {
        printf ("Astronaut not found\n");
        return;
    }
}

void launch(){
    int max = (count < 4) ? count : 4;
    for (int i = 0; i < max; i++){
        spaceShuttle *temp = head;
        head = head->next;
        printf ("%s ", temp->name);
        free(temp);
        count--;
    } 
    printf ("Launched\n");
}

void printAstronaut(){
    if (head == NULL){
        printf ("No astronaut registered\n");
        return;
    }

    spaceShuttle *temp = head;
    while (temp != NULL){
        printf ("%s %s\n", temp->name, temp->ticket);
        temp = temp->next;
    }
}

int main(){
    char choice [10];
    while (1){
        scanf ("%s", choice);
        if (strcmp(choice, "REGISTER") == 0){
            char name [20], ticket [20];
            scanf ("%s %s", name, ticket);
            registerAstronout(name, ticket);
        } else if (strcmp(choice, "REMOVE") == 0){
            char name [20];
            scanf ("%s", name);
            removeAstronaut(name);
        } else if (strcmp(choice, "LAUNCH") == 0){
            launch();
        } else if (strcmp(choice, "PRINT") == 0){
            printAstronaut();
        } else if (strcmp(choice, "EXIT") == 0){
            break;
        }
    }

}

