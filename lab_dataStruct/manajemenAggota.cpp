#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define HASH_SIZE 100

struct Anggota {
    char fullName [50];
    char nomorAnggota [10];
    char nomorTelp[20];
    int usia;
    char jenisKeanggotaan[10];
    Anggota* next;
}*hash_Table [HASH_SIZE];

int hash_key (char* nomorAnggota){
    int sum = 0;
    for (int i = 3; i < 8; i++){
        sum += nomorAnggota[i] - '0';
    }
    return sum % HASH_SIZE;
}

void push (Anggota* newNode){
    int index = hash_key (newNode->nomorAnggota);
    if (hash_Table[index] == NULL){
        hash_Table[index] = newNode;
    } else {
        Anggota* temp = hash_Table[index];
        while (temp != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

char* id (char* namaLengkap){
    char* id = (char*)malloc(7* sizeof(char));
    sprintf (id, "%c%c%d%d%d%d%d",toupper(namaLengkap[0]), toupper(namaLengkap[1]), rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    return id;
}

void addAnggota(){
    Anggota *newAnggota = (Anggota*)malloc(sizeof(Anggota));
    do{
       printf ("Masukkan Nama Lengkap : ");
       scanf ("%[^\n]", newAnggota->fullName);
    } while (strlen(newAnggota->fullName) < 3 ||strlen(newAnggota->fullName) > 30 );

    int flag = 0;
    do{
        printf ("Masukkan Nomor Anggota : ");
        scanf ("%s", newAnggota->nomorAnggota); getchar();
        for (int i = 3; i < 8; i++){
            if (!isdigit(newAnggota->nomorAnggota[i])){
                flag = 1;
                break;
            }
        }
    } while (strncmp(newAnggota->nomorAnggota, "LIB", 3) != 0 || flag = 1 || strlen (newAnggota->nomorAnggota) != 8);
    
    do{
        printf ("Masukkan Nomor Telepon : ");
        scanf ("%[^\n]", newAnggota->fullName);
    } while (strlen(newAnggota->fullName) < 3 ||strlen(newAnggota->fullName) > 30 );
 
    do{
        printf ("Masukkan Usia : ");
        scanf ("%[^\n]", newAnggota->fullName);
    } while (strlen(newAnggota->fullName) < 3 ||strlen(newAnggota->fullName) > 30 );
 
}

void viewAnggota(){
    int found = 0;
    for (int i = 0; i < HASH_SIZE; i++){
        if (hash_Table[i] != NULL){
            Anggota* temp = hash_Table[i];
            while (temp){
                printf ("Nama Anggota");

                temp = temp->next;
            }
        }
    }
    
}

void deleteAnggota(){
// cek found
    char id[20];
    scanf ("%s", id);
    int index = hash_key(id);
    if (hash_Table[index] == NULL){
        printf ("Tidak ada");
    } 
    
    Anggota* temp = hash_Table[index];
    if (strcmp(hash_Table[index]->nomorAnggota, id) == 0){
        hash_Table[index] = temp->next;
        free(temp);
    } else {
        while (temp->next != NULL && strcmp(temp->next->nomorAnggota, id) != 0){
            temp = temp->next;
        }
        Anggota* toPop = temp->next;
        temp->next = toPop->next;
        free(toPop);
    }
}

void printMenu(){
    puts ("Sistem Manajemen Anggota Perpustakaan Nusantara");
    puts ("1. Tambah Anggota");
    puts ("2. Lihat Daftar Anggota");
    puts ("3. Hapus Anggota");
    puts ("Keluar");
}

int main(){
    int input;
    while(1){
        printMenu();
        do{
           printf (">> ");
           scanf ("%d", &input);getchar();
        } while (input < 1|| input > 4);
    }
}

