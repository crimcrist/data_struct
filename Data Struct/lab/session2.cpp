/*
Course Outline
====================
Single Linked List
- Insert -> pushHead, pushTail, pushMid
- View
- Search
- Delete -> popHead, popTail, popMid


Stack & Queue


*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    int key;
    char nama[100];
    struct Data* next;
} *head = NULL, *tail = NULL;

struct Data *createData(int key, const char *name) {
    struct Data* newData = (struct Data*)malloc(sizeof(struct Data)); 
    newData->key = key;
    strcpy(newData->nama, name);
    newData->next = NULL;
    return newData;
}

void pushHead(struct Data* newData) {
    if (head == NULL) {
        head = tail = newData;
    } else {
        newData->next = head;
        head = newData;
    }
}

void pushTail(struct Data* newData) {
    if (head == NULL) {
        head = tail = newData;
    } else {
        tail->next = newData;
        tail = newData;
    }
}

void pushMid(struct Data* newData) {
    if (head == NULL) {
        pushHead(newData);
    } else if (strcmp(head->nama, newData->nama) > 0){
    	pushHead(newData);
	} else if (strcmp(tail->nama, newData->nama) < 0){
		pushTail(newData);
	}else {
        struct Data* temp = head;
        while (strcmp(temp->next->nama, newData->nama) < 0){
        	temp = temp->next;
		}
		newData->next = temp->next;
		temp->next = newData;
    }
}

void view() {
    struct Data *curr = head;
    while (curr != NULL) {
        printf("%d - %s\n", curr->key, curr->nama);
        curr = curr->next;
    }
}

struct Data* search (char* name){
	if (head == NULL){
		return NULL;
	}
	struct Data*curr = head;
	while (curr != NULL){
		if (strcmp(curr->nama, name) == 0){
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

void pop (char *nama){
	if (strcmp(head->nama, nama) == 0){
		struct Data* temp = head;
		head = head->next;
		temp->next = NULL;
		free(temp);
	}else if (strcmp(tail->nama, nama) == 0){
		struct Data *curr = head;
		while (curr->next != tail){
			curr = curr->next;
		}
		free(tail);
		tail = curr;
		tail->next = NULL;
	}else {
		struct Data* temp1 = head;
		struct Data* temp2 = head->next;
		while (strcmp (temp2->nama, nama) != 0){
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		temp1->next = temp2->next;
		temp2->next = NULL;
		free(temp2);
	}
}

int main() {
    pushMid(createData(4, "Budi"));
    pushMid(createData(7, "Agung"));
    pushMid(createData(3, "Handoyo"));
    pushMid(createData(10, "Barle"));

    view();
    printf("\n");
    pop("Barle");
    view();
    
    struct Data* res = search ("Budi");
    if (res == NULL){
    	puts("Not Found");
	} else {
		printf ("%s has key %d\n",res->nama, res->key);
	}
    
    return 0;
}

