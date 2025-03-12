#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define HASH_SIZE 100

struct metroPark {
    char jenisKendaraan [50];
    char platKendaraan [50];
    char id [10];
    metroPark* next;
} *hash_Table[HASH_SIZE];

void printMenu(){
    puts ("METROPARK PARKIR");
    puts ("1. Tambah Kendaraan");
    puts ("2. View Kendaraan");
    puts ("3. Hapus Kendaraan");
    puts ("4. Exit");
}

int hashKey (char*id){
    int sum = 0;
    for (int i = 0; i < 5; i++){
        sum += id[i] - '0';
    }
    return sum % HASH_SIZE;
}

char* generatedID (char* plat){
    char* id = (char*)malloc(5 * sizeof(char));
    sprintf (id , "%c%c%d%d%d", plat[0], plat[1], rand() % 10, rand() % 10, rand() % 10);
}

void tambahKendaraan(){
    metroPark* newKendaraan = (metroPark*)malloc(sizeof(metroPark));
    int flag = 0;
    do{
        printf ("Masukkan Plat Kendaraan : ");
        scanf("%[^\n]", newKendaraan->platKendaraan);
        for (int i = 3; i < 7; i++){
            if (!isdigit(newKendaraan->platKendaraan[i])) {
                flag = 1;
                break;
            }
        }
        
    } while (!isupper(newKendaraan->platKendaraan[0]) || !isupper(newKendaraan->platKendaraan[1]) || newKendaraan->platKendaraan[2] != ' ' || flag == 1 || newKendaraan->platKendaraan != ' ' ||
            !isupper(newKendaraan->platKendaraan[8]) || !isupper(newKendaraan->platKendaraan[9]));
    
    do{
        printf ("Masukkan Jeni Kendaraan : ");
        scanf("%[^\n]", newKendaraan->jenisKendaraan);
    } while (strcmp(newKendaraan->jenisKendaraan, "Motor") != 0 &&
            strcmp(newKendaraan->jenisKendaraan, "Mobil") != 0 &&
            strcmp(newKendaraan->jenisKendaraan, "Bus") != 0);
    
}

void push (metroPark *newNode){
    int index = hashKey(newNode->id);
    if (hash_Table[index] == NULL){
        hash_Table[index] = newNode;
    } else {
        metroPark* temp = hash_Table[index];
        while (temp != NULL){
            temp= temp->next;
        }
        temp->next = newNode;
    }
}

int main(){
    int input = -1;
    while (1){
        printMenu();
        do
        {
            printf (">> ");
            scanf ("%d", input);
        } while (input < 1 || input > 4);
        switch (input)
        {
        case 1:
            /* code */
            break;
        
        default:
            break;
        }
        

    }
    
}