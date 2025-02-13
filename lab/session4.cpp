#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_table 10

// Struktur node
struct Node {
    char name[40];
    struct Node *next;
} *head[max_table] = {NULL}; // Inisialisasi array head ke NULL

// Fungsi untuk membuat node baru
struct Node *createNewNode (char *nama) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, nama);
    newNode->next = NULL;
    return newNode;
}

// Fungsi hash
int hash (char *name) {
    int key = 0;
    for (int i = 0; i < strlen(name); i++) {
        key += name[i];
    }
    return key % max_table;
}

// Fungsi untuk menambahkan elemen ke hash table (chaining)
void push (char *nama) {
    struct Node *newNode = createNewNode(nama);
    int pos = hash(nama);

    // Jika tidak ada elemen, langsung masukkan
    if (head[pos] == NULL) {
        head[pos] = newNode;
        return;
    }

    // Jika sudah ada elemen, tambahkan ke belakang (push tail)
    struct Node *temp = head[pos];
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Fungsi untuk mencetak isi hash table
void print() {
    for (int i = 0; i < max_table; i++) {
        struct Node *temp = head[i];
        printf("%d: ", i+1);
        while (temp) {
            printf("%s -> ", temp->name);
            temp = temp->next;
        }
        printf("NULL!!\n");
    }
}

void pop (char *name){
    int pos = hash (name);
    if (head[pos] == NULL){
        printf ("GA ADAA\n");
        return;
    }else {
        if (strcmp (head[pos]->name, name) == 0){
            Node *temp = head[pos];
            head[pos] = temp->next;
            free(temp);
        } else {
            Node *temp1 = head[pos];
            Node *temp2 = temp1->next;
            while (temp2->next != 0 && strcmp (temp1->next->name, name) != 0){
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            temp1->next = temp2->next;
            temp2->next = NULL;
            free (temp2);
        }
    }
}

// Program utama
int main () {
    push("budi");
    push("lala");
    push("andi");
    push("agus");
    push("neo");
    push("ziva");
    push("jaden");
    push("nana");
    push("webe");

   
    
    print(); // Cetak isi hash table
    pop ("neo");
    print();
    return 0;
}
