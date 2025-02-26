#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_VMs 10

typedef struct Vulnerability {
    int id;
    int impact;
    int likelihood;
    int severity; 
    struct Vulnerability* next;
} Vulnerability;

Vulnerability* head = NULL;
Vulnerability* hashTable[MAX_VMs] = {NULL}; 

int getSeverity(int impact, int likelihood) {
    if (impact == 1 && likelihood == 1) return 2; // Critical 
    if (impact == 1 && likelihood == 0) return 1; // High
    if (impact == 0 && likelihood == 1) return 0; // Medium
    return -1; // Low
}

int getVM(int id) {
    return id % MAX_VMs;
}

void enqueue(int id, int impact, int likelihood) {
    Vulnerability* newV = (Vulnerability*)malloc(sizeof(Vulnerability));
    newV->id = id;
    newV->impact = impact;
    newV->likelihood = likelihood;
    newV->severity = getSeverity(impact, likelihood);
    newV->next = NULL;

    if (head == NULL || head->severity < newV->severity || 
        (head->severity == newV->severity && head->id > newV->id)) {
        newV->next = head;
        head = newV;
    } else {
        Vulnerability* temp = head;
        while (temp->next != NULL && 
            (temp->next->severity > newV->severity || 
            (temp->next->severity == newV->severity && temp->next->id < newV->id))) {
            temp = temp->next;
        }
        newV->next = temp->next;
        temp->next = newV;
    }
}

Vulnerability* dequeue() {
    if (head == NULL) return NULL;
    Vulnerability* temp = head;
    head = head->next;
    return temp;
}

void processVulnerability() {
    printf("Stored Processed Vulnerabilities:\n");
    while (head != NULL && head->severity == 2) { 
        Vulnerability* temp = dequeue();
        int hashIndex = getVM(temp->id);
        temp->next = hashTable[hashIndex];
        hashTable[hashIndex] = temp;
        printf("Index %d -> ID: %d\n", hashIndex, temp->id);
    }
}

void printQueue() {
    printf("Vulnerability Queue:\n");
    Vulnerability* temp = head;
    while (temp != NULL) {
        printf("ID: %d - %s\n", temp->id, 
            (temp->severity == 2) ? "Critical" : 
            (temp->severity == 1) ? "High" : 
            (temp->severity == 0) ? "Medium" : "Low");
        temp = temp->next;
    }
    printf("\n");
}

void displayVulnerability() {
    int collisionCount = 0;
    for (int i = 0; i < MAX_VMs; i++) {
        printf("Index %d: ", i);
        Vulnerability* temp = hashTable[i];
        int count = 0;
        while (temp != NULL) {
            printf("[%d, %d, %d] -> ", temp->id, temp->impact, temp->likelihood);
            temp = temp->next;
            count++;
        }
        if (count > 1) {
            collisionCount += (count - 1);
        }
        printf("NULL\n");
    }
    printf("Total Collisions: %d\n", collisionCount);
}

int main() {
    enqueue(3001, 0, 0);
    enqueue(3002, 1, 1);
    enqueue(3003, 1, 0);
    enqueue(3004, 0, 1);
    enqueue(3005, 1, 1);

    printQueue();

    printf("Processing Vulnerabilities...\n");
    processVulnerability();
    printf("\n");

    printQueue();

    displayVulnerability();

    while (1) {
        puts("~~ MENU ~~");
        puts("1. Add Vulnerability");
        puts("2. Process Vulnerability");
        puts("3. View Hash Index");
        puts("4. Exit");
        printf(">> ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                int id, impact, likelihood;
                printf("Masukkan ID: ");
                scanf("%d", &id);
                printf("Masukkan Impact (0/1): ");
                scanf("%d", &impact);
                printf("Masukkan Likelihood (0/1): ");
                scanf("%d", &likelihood);
                enqueue(id, impact, likelihood);
                printQueue();
                break;
            }
            case 2:
                processVulnerability();
                printQueue();
                break;
            case 3:
                displayVulnerability();
                break;
            case 4:
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}
