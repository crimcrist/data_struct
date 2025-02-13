#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int count = 100;
struct Node {
    int ID;
    char nama[25];
    int price;
    struct Node *next;
} *h, *t, *c;

void pushMid (char Name[]){
    srand(time(NULL));
    c = (struct Node*)malloc(sizeof(struct Node));
    strcpy(c->nama, Name);
    c->ID = count;
    count++;
    c->price = rand() % 9000 + 1000;
    c->next = NULL;
    if(!h){
        h = t = c;
    } else if (strcmp(Name, h->nama) < 0){
        c->next = h;
        h = c;
    } else if (strcmp(Name, t->nama) > 0){
        t -> next = c;
        t = c;
    } else {
        Node *temp = h;
        while (strcmp (temp->next->Name , Name) < 0){
            temp = temp->next;
        }
        c -> next = temp -> next;
        temp->next = c;
    }
}

void popHeadMid (char target[]){
    if (h == NULL){
        return;
    }
    if (strcmp(h->nama, target) == 0){
        struct Node *temp = h;
        h = h->next;
        temp -> next = NULL;
        free(temp);
    } else{
        struct Node *temp1 = h;
        struct Node *temp2 = h -> next;
        while (strcmp (temp2->nama, target) != 0){
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;
        }
        temp1 -> next = temp2 -> next;
        temp2 -> next = NULL;
        free (temp2);
    }
}

void printList(struct Node *h){
    while (h != NULL){
        printf ("ID : %d\n", h->ID);
        printf ("Nama : %s\n", h->nama);
        printf ("Price : %d\n", h->price);
        h = h -> next;
        printf ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
}

void Buy(){
    char temp[25];
    printfList(h);
    printf ("Input Card Name to Buy : ");
    scanf ("%[^\n]", temp); getchar();
    pushMid (temp);
    printf ("%s has been success input\n", temp);
    printf ("===================================\n");
}

void show(){
    printfList(h);
    printf ("========================\n");
}

void del(){
    char temp[25];
    printf ("Input Card Name to Buy : ");
    scanf ("%[^\n]", temp); getchar();
    popHeadMid(temp);
    printf ("%s has been success deleted\n");
    printf ("===================================\n");
}


void Change(){
    buy();
    del();
    show();
}

void enterToContinue(){
    puts ("Enter To Continue\n"); getchar();

}

int main(){
    char nama[25]; 
    srand (time(NULL));
    strcpy (nama, "Vulpix");
    pushMid(nama);
    
    srand (time(NULL));
    strcpy (nama, "Diglett");
    pushMid(nama);

    srand (time(NULL));
    strcpy (nama, "Zubat");
    pushMid(nama);

    srand (time(NULL));
    strcpy (nama, "Nidoran");
    pushMid(nama);

    int choice = -1;
    do{
        puts("CARD CHANGE");
        puts("1. Buy Card");
        puts("2. Show Card");
        puts("3. Change Card");
        puts("4. Delete Card");
        puts("5. Exit");
        do {
            printf (">> ");
            scanf ("%d", &choice);
            getchar ();
            if (choice < 1 || choice > 5){
                printf ("Invalid Input\n");
            }
        } while (choice < 1 || choice > 5);

        switch (choice){
            case 1:
                buy();
                enterToContinue();
                break;
            case 2:
                show();
                enterToContinue();
                break;
            case 3:
                Change();
                enterToContinue();
                break;
            case 4:
                del();
                enterToContinue();
                break;
        }
        system("cls");
    } while (choice != 5);
    return 0;
}


