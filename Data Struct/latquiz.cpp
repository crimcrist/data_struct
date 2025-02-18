#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nama[50];
    int status;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node *head;
    Node *tail;
} PriorityQueue;

Node* createNode(char nama[], int status) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nama, nama);
    newNode->status = status;
    newNode->next = NULL;
    return newNode;
}

PriorityQueue* createQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    pq->tail = NULL;
    return pq;
}

int getPriority(const char* priority) {
    if (strcmp(priority, "FAST_TRACK") == 0) {
        return 1;
    } else if (strcmp(priority, "REGULER") == 0) {
        return 2;
    }
    return 3; // Default untuk kesalahan input
}

void enqueue(PriorityQueue* pq, char nama[], int status) {
    Node *newNode = createNode(nama, status);
    if (pq->head == NULL || newNode->status < pq->head->status) {
        newNode->next = pq->head;
        pq->head = newNode;
        if (pq->tail == NULL) pq->tail = newNode;
        return;
    }
    
    Node *current = pq->head;
    while (current->next != NULL && current->next->status <= newNode->status) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == NULL) {
        pq->tail = newNode;
    }
}

void dequeue(PriorityQueue* pq, char* nama) {
    if (pq->head == NULL) {
        printf("Tidak ada Antrian\n");
        return;
    }
    
    Node *current = pq->head;
    Node *prev = NULL;
    
    while (current != NULL && strcmp(current->nama, nama) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Nama tidak ditemukan dalam antrian.\n");
        return;
    }
    
    if (prev == NULL) {
        pq->head = current->next;
    } else {
        prev->next = current->next;
    }
    
    if (current == pq->tail) {
        pq->tail = prev;
    }
    
    free(current);
}

void displayALL(PriorityQueue* pq) {
    Node* current = pq->head;
    if (!current) {
        printf("Antrian Kosong\n");
        return;
    }
    int index = 1;
    while (current != NULL) {
        printf("%d. %s %s\n", index++, current->nama, current->status == 1 ? "FAST_TRACK" : "REGULER");
        current = current->next;
    }
}

void freeQueue(PriorityQueue* pq) {
    Node* current = pq->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(pq);
}

int main() {
    PriorityQueue *pq = createQueue();
    while (1) {
        printf("ISTANA BONEKA\n");
        printf("1. REGISTER\n");
        printf("2. CALL\n");
        printf("3. REMOVE\n");
        printf("4. EXIT\n");
        
        char menu[20];
        printf("Pilih Menu: ");
        scanf("%s", menu);
        
        if (strcmp(menu, "REGISTER") == 0) {
            int angka;
            scanf("%d", &angka);
            char nama[50], status[20];
            for (int i = 0; i < angka; i++) {
                scanf("%s %s", nama, status);
                enqueue(pq, nama, getPriority(status));
            }
            displayALL(pq);
        } 
        else if (strcmp(menu, "REMOVE") == 0) {
            int angka;
            scanf("%d", &angka);
            char nama[50];
            for (int i = 0; i < angka; i++) {
                scanf("%s", nama);
                dequeue(pq, nama);
            }
            displayALL(pq);
        } 
        else if (strcmp(menu, "CALL") == 0) {
            printf("\n");
            int count = 0;
            while (pq->head != NULL && count < 3) {
                printf("%s got into the boat.\n", pq->head->nama);
                dequeue(pq, pq->head->nama);
                count++;
            }
            printf("%d queues remaining.\n", pq->head ? count : 0);
            displayALL(pq);
        } 
        else if (strcmp(menu, "EXIT") == 0) {
            break;
        }
    }
    freeQueue(pq);
    return 0;
}
