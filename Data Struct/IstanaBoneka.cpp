#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

struct Node {
    char nama [100];
    char type [20];
    struct Node* next;
}*head;

int count = 0;

Node* createNode (char *nama, char *type){
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nama,nama);
    strcpy(newNode->type,type);
    newNode->next = NULL;
    return newNode;
}

void registerNode (char *nama, char* type){
    Node* newNode = createNode(nama,type);
    if (!head){
        head = newNode;
    }

    if (strcmp(newNode->type, "FAST_TRACK") == 0){
        if (strcmp (head->type, "REGULER") == 0){
            newNode->next = head;
            head = newNode;
        }

        Node* temp = head;
        while (temp != NULL && strcmp (temp->type, "FAST_TRACK") == 0){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }

    count++;
}

void call (){
    if (!head){
        printf("Antrian Kosong\n");
        return;
    }

    int out = (count < 4) ? count : 4;
    for (int i = 0; i < out; i++){
        Node* temp = head;
        head = head->next;
        printf ("%s ", temp->nama);
        free (temp);
        count--;
    }
    printf( " got into the boat.\n");
    printf ("%d queues remaining. \n", count);
}

void Remove (char *nama){
    if (!head){
        printf ("Antrian Kosong\n");
        return;
    }

    if (strcmp (head->nama, nama) == 0){
        Node* temp = head;
        head = head->next;
        free (temp);
        count--;
        return;
    }

    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL && strcmp (temp->nama, nama) != 0){
        prev = temp;
        temp = temp->next;
    }

    if (!temp){
        printf ("Nama tidak ditemukan\n");
        return;
    } else {
        prev->next = temp->next;
        free (temp);
        count--;
        return;
    }
}

int main (){
    

}