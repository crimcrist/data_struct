#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_SIZE 10

struct Node {
    char nopol[15];
    char merk[50];
    char warna[20];
    struct Node* next;
}*hash_table[HASH_SIZE];

int hashFunction (const char* nopol){
    int sum = 0;
    for (int i = 0; nopol[i] != '\0'; i++){
        sum += nopol[i];
    }
    return sum % HASH_SIZE;
}

void insertKendaraan(){
    struct Node *newNode = (Node*)malloc(sizeof(Node));
    printf ("Masukkan Nomor Polisi : ");
    scanf ("%[^\n]", newNode->nopol); getchar();

    printf ("Masukkan Merk Kendaraan : ");
    scanf ("%[^\n]", newNode->merk); getchar();

    printf ("Masukkan Warna Kendaraan : ");
    scanf ("%[^\n]", newNode->warna); getchar();

    newNode->next = NULL;
    int index = hashFunction(newNode->nopol);
    if (hash_table[index] == NULL){
        hash_table[index] == newNode;
    } else {
        Node *temp = hash_table[index];
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf ("Kendaraan berhasil ditambahlkan\n");
}

void searchKendaraan(){
    char nopol[15];
    printf ("Masukkan Nomor Polisi Yang dicari : ");
    scanf ("%[^\n]", nopol); getchar();

    int index = hashFunction(nopol);
    Node *temp = hash_table[index];
    int flag = 0;
    while (temp != NULL){
        if (strcmp(temp->nopol, nopol) == 0){
            flag = 1;
            printf ("Kendaraan ditemukan\n");
            printf ("Nomor Polisi : %s\n", temp->nopol);
            printf ("Merk         : %s\n", temp->merk);
            printf ("Warna        : %s\n", temp->warna);
            return;
        }
        temp = temp->next;
    }
    printf ("Kendaraan dengan Nomor polisi %s tidak ditemukan\n", nopol);
}

void deleteKendaraan(){
    char nopol[15];
    printf ("Masukkan Nomor Polisi Yang dihapus : ");
    scanf ("%[^\n]", nopol); getchar();

    int index = hashFunction(nopol);
    Node *temp = hash_table[index];
    while (temp != NULL && strcmp (temp->next->nopol, nopol) == 0){
        temp = temp->next;
    }
    Node* toPop = temp->next;
    if (toPop->next == NULL){
        free(toPop);
    } else {
        temp->next = toPop->next;
        free(toPop);
    }
    printf ("Kendaraan dengan Nomor polisi %s telah dihapus\n", nopol);
}


void viewAll(){
    printf ("Daftar Kendaraan di parkiran\n");
    for (int i = 0; i < HASH_SIZE; i++){
        if (hash_table[i] != NULL){
            Node* temp = hash_table[i];
            while(temp){
                printf ("No pol : %s\n", temp->nopol);
                printf ("Merk   : %s\n", temp->merk);
                printf ("Warna  : %s\n", temp->warna);
                temp = temp->next;
            }
        }
    }
}

void exitProgram(){
    for (int i = 0; i < HASH_SIZE; i++){
        Node *temp;
        while (hash_table[i] != NULL){
            temp = hash_table[i];
            hash_table[i] = hash_table[i]->next;
            free(temp);
        }
    }
    printf ("Semua data terhapus.Goodbye\n");
}

int main() {
    int choice;
    
    while (1) {
        printf("\n=== SISTEM PARKIRAN ===\n");
        printf("1. Tambah Kendaraan\n");
        printf("2. Cari Kendaraan\n");
        printf("3. Hapus Kendaraan\n");
        printf("4. Lihat Semua Kendaraan\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                insertKendaraan();
                break;
            case 2:
                searchKendaraan();
                break;
            case 3:
                deleteKendaraan();
                break;
            case 4:
                viewAll();
                break;
            case 5:
                exitProgram();
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}
