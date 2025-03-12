#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 200

// Struktur untuk menyimpan pasangan key-value
struct Bookstore {
    char key[100];
    int value;
} *hashTable[TABLE_SIZE];

// Fungsi hash untuk menghitung indeks berdasarkan nama buku
int hashFunction(const char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    int lastThreeDigits = sum % 1000;
    return lastThreeDigits % TABLE_SIZE;
}

// Fungsi quadratic probing untuk menangani tabrakan
int quadraticProbing(int index, int step) {
    return (index + step * step) % TABLE_SIZE;
}

// Fungsi untuk menyisipkan key-value ke dalam hash table
void insert(const char *key, int value) {
    int index = hashFunction(key);
    int step = 0;
    
    // Looping sampai menemukan slot kosong
    while (hashTable[index] != NULL && hashTable[index]->key[0] != '\0') {
        step++;
        index = quadraticProbing(index, step);
        if (step > TABLE_SIZE) {
            printf("Hash Table is full\n");
            return;
        }
    }
    
    // Alokasi memori untuk entri baru
    hashTable[index] = (struct Bookstore*)malloc(sizeof(struct Bookstore));
    strcpy(hashTable[index]->key, key);
    hashTable[index]->value = value;
}

// Fungsi untuk menampilkan isi hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL && hashTable[i]->key[0] != '\0') {
            printf("Index %d: (%s, %d)\n", i, hashTable[i]->key, hashTable[i]->value);
        }
    }  
}

int main() {
    srand(time(NULL));
    
    // Inisialisasi hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    
    // Menyisipkan beberapa data buku
    insert("necronomicon", 666);
    insert("eldritch_horrors", 777);
    insert("arcane_codex", 888);
    insert("grimoire_of_void", 999);
    
    display(); // Menampilkan isi hash table
    
    // Membebaskan memori yang dialokasikan
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            free(hashTable[i]);
        }
    }
    
    return 0;
}
