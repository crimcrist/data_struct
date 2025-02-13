#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a node
struct kelas {
    int id;
    char nama[50];
    struct kelas* next;
    struct kelas* prev;
};

struct kelas* head = NULL;
struct kelas* tail = NULL;

// Function to create a new node
struct kelas* createNode(int id, char nama[]) {
    struct kelas* newNode = (struct kelas*)malloc(sizeof(struct kelas));
    newNode->id = id;
    strcpy(newNode->nama, nama);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to push a node at the head
void pushHead(int id, char nama[]) {
    struct kelas* newNode = createNode(id, nama);

    if (!head) { // List is empty
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

// Function to push a node at the tail
void pushTail(int id, char nama[]) {
    struct kelas* newNode = createNode(id, nama);

    if (!tail) { // List is empty
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Function to pop a node from the head
void popHead() {
    if (!head) { // List is empty
        printf("List is empty, nothing to pop.\n");
        return;
    }

    struct kelas* temp = head;
    if (head == tail) { // Only one node in the list
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
    }
    printf("Popped from head: ID: %d, Nama: %s\n", temp->id, temp->nama);
    free(temp);
}

// Function to pop a node from the tail
void popTail() {
    if (!tail) { // List is empty
        printf("List is empty, nothing to pop.\n");
        return;
    }

    struct kelas* temp = tail;
    if (head == tail) { // Only one node in the list
        head = tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = NULL;
    }
    printf("Popped from tail: ID: %d, Nama: %s\n", temp->id, temp->nama);
    free(temp);
}

// Function to insert a node in sorted order based on ID
void pushSorted(int id, char nama[]) {
    struct kelas* newNode = createNode(id, nama);

    if (!head) { // List is empty
        head = tail = newNode;
        return;
    }

    if (id <= head->id) { // Insert at the head
        pushHead (id, nama);
        return;
    }

    if (id >= tail->id) { // Insert at the tail
        pushTail (id, nama);
        return;
    }

    // Insert in the middle
    struct kelas* current = head;
    while (current && current->id < id) {
        current = current->next;
    }

    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
}


// Function to remove a node by ID
void popById(int targetId) {
    struct kelas* current = head;

    while (current && current->id != targetId) {
        current = current->next;
    }

    if (!current) { // Target ID not found
        printf("ID %d not found. Cannot delete.\n", targetId);
        return;
    }

    if (current == head) { // Node is at the head
        popHead ();
    } else if (current == tail) { // Node is at the tail
        popTail();
    } else { // Node is in the middle
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    printf("Popped: ID: %d, Nama: %s\n", current->id, current->nama);
    free(current);
}

// Function to print the list from head to tail
void printForward() {
    struct kelas* current = head;
    while (current) {
        printf("ID: %d, Nama: %s\n", current->id, current->nama);
        current = current->next;
    }
}

// Function to print the list from tail to head
void printBackward() {
    struct kelas* current = tail;
    while (current) {
        printf("ID: %d, Nama: %s\n", current->id, current->nama);
        current = current->prev;
    }
}

int main() {
    // Example usage
    pushHead(1, "Alice");
    pushTail(2, "Bob");
    pushHead(3, "Charlie");

    printf("List from head to tail:\n");
    printForward();

    printf("\nList from tail to head:\n");
    printBackward();

    printf("\nPop operations:\n");
    popHead();
    popTail();

    printf("\nList after pop operations:\n");
    printForward();

    return 0;
}
