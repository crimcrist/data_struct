#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Struktur data untuk contact person
typedef struct Contact {
    char name[50];
    char phone[20];
    char email[50];
    struct Contact* next;
} Contact;

// Hash table
Contact* hashTable[TABLE_SIZE];

// Fungsi hash menggunakan metode Mid Square dan Division
int hashFunction(char* name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    
    // Mid Square: Mengkuadratkan hasil penjumlahan ASCII
    long long squared = (long long)sum * sum;
    
    // Ambil nilai tengah dari hasil kuadrat
    char squaredStr[20];
    sprintf(squaredStr, "%lld", squared);
    printf ("%s", squaredStr);
    int len = strlen(squaredStr);
    
    int midValue;
    if (len % 2 == 0) {
        midValue = (squaredStr[len / 2 - 1] - '0') * 10 + (squaredStr[len / 2] - '0');
    } else {
        midValue = squaredStr[len / 2] - '0';
    }
    
    return midValue % TABLE_SIZE;
}

// Fungsi untuk menambahkan contact person
void insertContact(char* name, char* phone, char* email) {
    int index = hashFunction(name);
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    newContact->next = NULL;
    
    if (hashTable[index] == NULL) {
        hashTable[index] = newContact;
    } else {
        Contact* temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newContact;
    }
}

// Fungsi untuk mencari contact person
Contact* searchContact(char* name) {
    int index = hashFunction(name);
    Contact* temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Fungsi untuk menghapus contact person
void deleteContact(char* name) {
    int index = hashFunction(name);
    Contact* temp = hashTable[index];
    Contact* prev = NULL;
    
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Contact not found!\n");
        return;
    }
    
    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Contact deleted successfully!\n");
}

// Fungsi untuk menampilkan seluruh contact person
void displayContacts() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Contact* temp = hashTable[i];
        while (temp != NULL) {
            printf("[%s, %s, %s] -> ", temp->name, temp->phone, temp->email);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Fungsi utama
int main() {
    insertContact("Alice", "123456789", "alice@example.com");
    insertContact("Bob", "987654321", "bob@example.com");
    insertContact("Charlie", "555123456", "charlie@example.com");
    
    displayContacts();
    
    Contact* found = searchContact("Alice");
    if (found) {
        printf("\nContact Found: %s, %s, %s\n", found->name, found->phone, found->email);
    } else {
        printf("\nContact Not Found\n");
    }
    
    deleteContact("Bob");
    displayContacts();
    
    return 0;
}
