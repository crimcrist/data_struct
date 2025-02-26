#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 200

typedef struct {
    char key[20];
    int value;
} HashEntry;

HashEntry hashTable[TABLE_SIZE];

// Function to initialize the hash table
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].value = -1; // -1 indicates empty slot
    }
}

// Hash function to generate index
int hashFunction(char *key) {
    unsigned long long product = 1;
    int length = strlen(key);

    // Stage 1: Multiply ASCII values of characters
    for (int i = 0; i < length; i++) {
        product *= key[i];
    }

    printf ("Hasil Multiply decimal character = %d\n", product);

    // Convert product to string to extract middle digits
    char str_product[30];
    sprintf(str_product, "%llu", product);
    int str_len = strlen(str_product);

    // Stage 2: Extract middle digit(s)
    int middle_digits;
    if (str_len % 2 == 0) {
        middle_digits = (str_product[str_len / 2 - 1] - '0') * 10 + (str_product[str_len / 2] - '0');
    } else {
        middle_digits = str_product[str_len / 2] - '0';
    }

    printf ("Middle Digits adalah %d\n", middle_digits);

    // Stage 3: Modulo operation
    return middle_digits % TABLE_SIZE;
}

// Function to insert key-value pair using linear probing
void insert(char *key, int value) {
    int index = hashFunction(key);

    // Linear probing to resolve collisions
    while (hashTable[index].value != -1) {
        index = (index + 1) % TABLE_SIZE;
    }

    strcpy(hashTable[index].key, key);
    hashTable[index].value = value;
}

// Function to display the hash table
void displayTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].value != -1) {
            printf("Index %d: %s -> %d\n", i, hashTable[i].key, hashTable[i].value);
        }
    }
}

// Function to compute the sum of all values in the hash table
int sumValues() {
    int sum = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].value != -1) {
            sum += hashTable[i].value;
        }
    }
    return sum;
}

// Main function
int main() {
    initializeTable();

    // Insert key-value pairs
    insert("pineapple", 45);
    insert("papaya", 32);
    insert("banana", 12);
    insert("coconut", 67);

    // Display the hash table
    printf("Hash Table Entries:\n");
    displayTable();

    // Compute and print the sum of values
    printf("\nTotal Sum of Values: %d\n", sumValues());

    return 0;
}
