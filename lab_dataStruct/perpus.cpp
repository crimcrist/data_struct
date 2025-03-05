#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 50

// Struktur untuk data peminjaman
typedef struct Loan {
    char id[6];
    char name[41];
    char category[15];
    int duration;
    struct Loan* next;
} Loan;

// Hash table
Loan* hashTable[TABLE_SIZE];

// Fungsi untuk menghitung hash key
int getHashKey(char* id) {
    int lastDigits = (id[2] - '0') * 10 + (id[3] - '0');
    return (lastDigits - 2) % TABLE_SIZE;
}

// Fungsi untuk membuat ID peminjaman
void generateLoanID(char* id, char* category) {
    snprintf(id, 6, "%c%c%03d", category[0], category[1], rand() % 9 + 1);
}

// Fungsi untuk menambahkan peminjaman
void addLoan() {
    Loan* newLoan = (Loan*)malloc(sizeof(Loan));
    if (!newLoan) return;

    printf("Nama Peminjam: ");
    fgets(newLoan->name, 41, stdin);
    newLoan->name[strcspn(newLoan->name, "\n")] = 0;

    printf("Kategori Buku (Fiksi/Non-Fiksi/Referensi): ");
    fgets(newLoan->category, 15, stdin);
    newLoan->category[strcspn(newLoan->category, "\n")] = 0;

    printf("Durasi Peminjaman (1-30 hari): ");
    scanf("%d", &newLoan->duration);
    getchar();

    generateLoanID(newLoan->id, newLoan->category);
    int key = getHashKey(newLoan->id);

    newLoan->next = hashTable[key];
    hashTable[key] = newLoan;

    printf("Peminjaman Berhasil! ID: %s\n", newLoan->id);
}

// Fungsi untuk melihat semua peminjaman
void viewLoans() {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Loan* temp = hashTable[i];
        while (temp) {
            printf("ID: %s | Nama: %s | Kategori: %s | Durasi: %d hari\n", temp->id, temp->name, temp->category, temp->duration);
            temp = temp->next;
            found = 1;
        }
    }
    if (!found) printf("Tidak ada peminjaman.\n");
}

// Fungsi untuk menghapus peminjaman
void deleteLoan() {
    char id[6];
    printf("Masukkan ID Peminjaman: ");
    fgets(id, 6, stdin);
    getchar();

    int key = getHashKey(id);
    Loan* temp = hashTable[key];
    Loan* prev = NULL;

    while (temp) {
        if (strcmp(temp->id, id) == 0) {
            if (prev) prev->next = temp->next;
            else hashTable[key] = temp->next;
            free(temp);
            printf("Peminjaman berhasil dihapus!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("ID tidak ditemukan.\n");
}

// Menu utama
int main() {
    srand(time(NULL));
    int choice;

    do {
        printf("\n1. Tambah Peminjaman\n2. Lihat Peminjaman\n3. Hapus Peminjaman\n4. Keluar\nPilihan: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addLoan(); break;
            case 2: viewLoans(); break;
            case 3: deleteLoan(); break;
            case 4: printf("Keluar dari program.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (choice != 4);

    return 0;
}
