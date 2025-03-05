#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 50

struct Perpus {
    char Name[100];
    char nomorAnggota[30];
    int usia;
    char categoryBook[100];
    int durasi;
    char id [10];
    struct Perpus *next;
} *HashTable[HASH_SIZE];

void printMenu(){
    puts ("+--------------------------------+");
    puts ("|    Perpustakaan Nusantara      |");
    puts ("+--------------------------------+");
    puts ("1. Peminjaman Buku");
    puts ("2. Lihat Peminjaman");
    puts ("3. Hapus Peminjaman");
    puts ("4. Keluar");
}

char* generatedID (char* categoty){
    char*id = 
}

void peminjaman (){
    struct Perpus *newCustom = (Perpus*)malloc(sizeof(Perpus));
    do {
        printf ("Masukkan Nama Lengkap : ");
        scanf ("%[^\n]" , newCustom->Name);
    } while (strlen(newCustom->Name) < 5 || strlen(newCustom->Name) > 40);

    do {
        printf ("Masukkan Nomor Anggota : ");
        scanf ("%s" , newCustom->nomorAnggota);
    } while (strlen(newCustom->nomorAnggota) != 6);
    
    do {
        printf ("Masukkan Usia Pengguna : ");
        scanf ("%d" , &newCustom->usia);
    } while (newCustom->usia < 10|| newCustom->usia > 80);

    do {
        printf ("Masukkan Category Book : ");
        scanf ("%s" , newCustom->categoryBook);
    } while (strcmp(newCustom->categoryBook, "Fiksi") != 0 && strcmp(newCustom->categoryBook, "Non-Fiksi") != 0 && strcmp(newCustom->categoryBook, "Referensi") != 0);
    

}
void lihatPeminjaman(){

}

void hapusPeminjaman(){

}

int main (){
    int key = -1;
    while (1){
        printMenu();
        do {
            printf (">> ");
            scanf ("%d", &key);
        } while (key < 1 || key > 4);

        switch (key){
        case 1:
            peminjaman();
            break;
        case 2:
            lihatPeminjaman();
            break;
        case 3:
            hapusPeminjaman();
            break;
        case 4:
            return;
            break;
        }
    }
}
