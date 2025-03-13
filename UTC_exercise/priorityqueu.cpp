#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char nama[50];
    char idKorban[15];
    char kondisi[20];
    int priority;
    struct Node* next;
    struct Node* prev;
} *head = NULL, *tail = NULL;

int getPriority(const char* kondisi) {
    if (strcmp(kondisi, "Ekstrem") == 0) return 1;
    if (strcmp(kondisi, "Luka") == 0) return 2;
    if (strcmp(kondisi, "Sehat") == 0) return 3;
    return 4;
}

void insertKorban() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    printf("Enter your name: ");
    scanf("%[^\n]", newNode->nama); getchar();

    printf("Enter your ID: ");
    scanf("%[^\n]", newNode->idKorban); getchar();

    printf("Enter your kondisi (Ekstrem/Luka/Sehat): ");
    scanf("%[^\n]", newNode->kondisi); getchar();

    newNode->priority = getPriority(newNode->kondisi);
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = tail = newNode;
    } else {
        struct Node* temp = head;

        while (temp->next != NULL && temp->priority <= newNode->priority) {
            temp = temp->next;
        }

        // Masukkan setelah temp
        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next != NULL) {
            temp->next->prev = newNode;
        } else {
            tail = newNode;
        }
        temp->next = newNode;
    }

    printf("Pasien berhasil ditambahkan ke antrean!\n");
}

void extractMin() {
    if (head == NULL) {
        printf("Tidak ada pasien dalam antrean!\n");
        return;
    }

    struct Node* temp = head;
    printf("\nPasien yang ditangani:\n");
    printf("Nama     : %s\n", temp->nama);
    printf("ID       : %s\n", temp->idKorban);
    printf("Kondisi  : %s\n", temp->kondisi);
    printf("Priority : %d\n", temp->priority);
    printf("PASIEN MELUNCURRRR 🚑\n");

    if (head == tail) { 
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
    }

    free(temp);
}

void viewAll() {
    if (head == NULL) {
        printf("Tidak ada antrean!\n");
        return;
    }

    printf("\nDaftar antrean pasien:\n");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("- %s (ID: %s, Kondisi: %s, Priority: %d)\n",
               temp->nama, temp->idKorban, temp->kondisi, temp->priority);
        temp = temp->next;
    }
}

void exitProgram() {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Antrean telah dibersihkan. Goodbye!\n");
}

int main() {
    int choice;
    
    while (1) {
        printf("\n=== SISTEM ANTREAN IGD ===\n");
        printf("1. Tambah Pasien\n");
        printf("2. Tangani Pasien (Extract Min)\n");
        printf("3. Lihat Semua Pasien\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                insertKorban();
                break;
            case 2:
                extractMin();
                break;
            case 3:
                viewAll();
                break;
            case 4:
                exitProgram();
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}
