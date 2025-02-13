#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nama[50];
    int umur;
    int status;  // status diubah menjadi integer
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct PriorityQueue {
    Node* head;
    Node* tail;
} PriorityQueue;

Node* createNode(char nama[], int umur, int status) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nama, nama);
    newNode->umur = umur;
    newNode->status = status;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

PriorityQueue* createQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    pq->tail = NULL;
    return pq;
}

int getPriorityText(const char* priority) { // 
    if (strcmp(priority, "High") == 0) {
        return 1; 
    } else if (strcmp(priority, "Mid") == 0) {
        return 2;
    } else if (strcmp(priority, "Low") == 0) {
        return 3;
    }
}

void enqueue(PriorityQueue* pq, char nama[], int umur, int status) {
    Node* newNode = createNode(nama, umur, status);

    if (pq->head == NULL) {
        pq->head = newNode;
        pq->tail = newNode;
        return;
    }

    if (newNode->status < pq->head->status) { // 1 2 3
        newNode->next = pq->head;
        pq->head->prev = newNode;
        pq->head = newNode;
        return;
    }

    Node* current = pq->head;
    while (current->next != NULL && current->next->status <= newNode->status) {
        current = current->next;
    }

    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    } else {
        pq->tail = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

void dequeue(PriorityQueue* pq) {
    if (pq->head == NULL) {
        printf("Antrian kosong. Tidak ada elemen yang dihapus.\n");
        return;
    }

    Node* temp = pq->head;
    printf("Menghapus: \nNama: %s\nUmur: %d\nStatus: %d\n\n", temp->nama, temp->umur, temp->status);

    pq->head = pq->head->next;
    if (pq->head != NULL) {
        pq->head->prev = NULL;
    } else {
        pq->tail = NULL;
    }
    free(temp);
}

void displayAll(PriorityQueue* pq) {
    Node* current = pq->head;
    if (!current) {
        printf("Antrian kosong.\n");
        return;
    }
    while (current != NULL) {
        printf("Nama: %s, Umur: %d, Status: %d\n", current->nama, current->umur, current->status);
        current = current->next;
    }
}

int main() {
    PriorityQueue* pq = createQueue();

    enqueue(pq, "Rizki", 33, getPriorityText("Low"));
    enqueue(pq, "Richard", 26, getPriorityText("Low"));
    enqueue(pq, "Andi", 16, getPriorityText("High"));
    enqueue(pq, "Nur", 74, getPriorityText("Mid"));
    enqueue(pq, "Coki", 66, getPriorityText("Low"));

    printf("Linked List after enqueue operations:\n");
    displayAll(pq);


    int input = -1;
    while (1){
    do{
        puts ("~~ Queue ~~");
        puts ("===================");
        puts ("1. Create");
        puts ("2. View");
        puts ("3. Delete");
        puts ("4. Exit");
        printf (">> ");
        scanf ("%d", &input);
    } while (input < 1 || input > 4);

     switch (input) {
            case 1: {
                char nama[20];
                int umur;
                char status[20];
                printf("Masukkan nama: ");
                scanf("%s", nama); getchar();
                printf("Masukkan umur: ");
                scanf("%d", &umur); getchar();
                do {
                    printf("Masukkan status (High, Mid, Low): ");
                    scanf("%s", status); getchar();
                } while (strcmp (status,"High") != 0 && strcmp (status,"Low") != 0 && strcmp (status,"Mid") != 0);

                int statusValue = getPriorityText(status);
                enqueue(pq, nama, umur, statusValue);
                displayAll(pq);
                break;
            }
            case 2:
                displayAll(pq);
                break;
            case 3:
                dequeue(pq);
                dequeue(pq);
                dequeue(pq);
                displayAll(pq);
                break;
            case 4:
                return 0;
            default:
                break;
        }
    }

    // printf("\nDequeue operation:\n");
    // dequeue(pq);

    // printf("\nLinked List after dequeue operation:\n");
    // displayAll(pq);

    return 0;
}
