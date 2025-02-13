#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur Node untuk menyimpan data pasien
typedef struct Node {
    char nama[50];
    int umur;
    int status; // 1 = Low, 2 = Mid, 3 = High
    struct Node* next;
    struct Node* prev;
} Node;

// Struktur PriorityQueue untuk menyimpan head dan tail dari linked list
typedef struct PriorityQueue {
    Node* head;
    Node* tail;
} PriorityQueue;

// Fungsi untuk membuat node baru
Node* createNode(char nama[], int umur, int status) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nama, nama);
    newNode->umur = umur;
    newNode->status = status;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Fungsi untuk inisialisasi PriorityQueue
PriorityQueue* createQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    pq->tail = NULL;
    return pq;
}

// Fungsi untuk menambahkan node berdasarkan prioritas (enqueue)
void enqueue(PriorityQueue* pq, char nama[], int umur, int status) {
    Node* newNode = createNode(nama, umur, status);

    // Jika list kosong, tambahkan sebagai head dan tail
    if (pq->head == NULL) {
        pq->head = newNode;
        pq->tail = newNode;
        return;
    }

    // Jika prioritas lebih tinggi, tambahkan di depan
    if (newNode->status > pq->head->status) {
        newNode->next = pq->head;
        pq->head->prev = newNode;
        pq->head = newNode;
        return;
    }

    // Cari posisi yang sesuai untuk menyisipkan node
    Node* current = pq->head;
    while (current->next != NULL && current->next->status >= newNode->status) {
        current = current->next;
    }

    // Sisipkan node di antara current dan current->next
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    } else {
        pq->tail = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

// Fungsi untuk menghapus elemen dengan prioritas tertinggi (dequeue)
void dequeue(PriorityQueue* pq) {
    if (pq->head == NULL) {
        printf("Antrian kosong. Tidak ada elemen yang dihapus.\n");
        return;
    }

    Node* temp = pq->head;
    printf("Menghapus: Nama: %s, Umur: %d, Status: %s\n", temp->nama, temp->umur, temp->status == 3 ? "High" : temp->status == 2 ? "Mid" : "Low");

    pq->head = pq->head->next;
    if (pq->head != NULL) {
        pq->head->prev = NULL;
    } else {
        pq->tail = NULL;
    }
    free(temp);
}

// Fungsi untuk mengonversi prioritas dari string ke nilai numerik
int getPriorityText(const char* priority) {
    if (strcmp(priority, "High") == 0) {
        return 1;
    } else if (strcmp(priority, "Mid") == 0) {
        return 2;
    } else if (strcmp(priority, "Low") == 0) {
        return 3;
    } else {
        return 0; // Tidak dikenal
    }
}

// Fungsi untuk menampilkan semua data pasien
void displayAll(PriorityQueue* pq) {
    Node* current = pq->head;
    if (!current) {
        printf("Antrian kosong.\n");
        return;
    }
    while (current != NULL) {
        printf("Nama: %s, Umur: %d, Status: %s\n", current->nama, current->umur, getPriorityText(current->status));
        current = current->next;
    }
}

// Fungsi utama
int main() {
    // Inisialisasi PriorityQueue
    PriorityQueue* pq = createQueue();

    // Menambahkan data pasien ke antrian
    enqueue(pq, "Rizki", 33, getPriorityText("Low"));   // Low
    enqueue(pq, "Richard", 26, getPriorityText("Low")); // Low
    enqueue(pq, "Andi", 16, getPriorityText("High"));    // High
    enqueue(pq, "Nur", 74,getPriorityText("Mid"));     // Mid
    enqueue(pq, "Coki", 66, getPriorityText("High"));    // Low

    // Menampilkan semua data
    printf("Linked List after enqueue operations:\n");
    displayAll(pq);

    // Menghapus elemen dengan prioritas tertinggi
    printf("\nDequeue operation:\n");
    dequeue(pq);

    // Menampilkan semua data setelah dequeue
    printf("\nLinked List after dequeue operation:\n");
    displayAll(pq);

    return 0;
}
