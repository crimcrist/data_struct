#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char title[100];
    struct Song *prev;
    struct Song *next;
} *head, *tail, *current;

void addSong(const char *title) {
    Song *newSong = (Song *)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    newSong->prev = NULL;
    newSong->next = NULL;

    if (head == NULL) {
        head = newSong;
        tail = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    if (current == NULL) {
        current = newSong;
    }
}

void displayPlaylist() {
    Song *temp = head;
    printf("\nPlaylist:\n");
    while (temp != NULL) {
        printf("- %s\n", temp->title);
        temp = temp->next;
    }
}

void nextSong() {
    if (current == NULL) {
        printf("No songs in the playlist.\n");
        return;
    }

    if (current->next != NULL) {
        current = current->next;
    } else {
        current = head;
    }

    printf("Now playing: %s\n", current->title);
}

void previousSong() {
    if (current == NULL) {
        printf("No songs in the playlist.\n");
        return;
    }

    if (current->prev != NULL) {
        current = current->prev;
    } else {
        current = tail;
    }

    printf("Now playing: %s\n", current->title);
}

int main() {
    int choice;
    char title[100];

    do {
        printf("\nMenu:\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Next Song\n");
        printf("4. Previous Song\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf(" %[^\n]", title);
                addSong(title);
                break;
            case 2:
                displayPlaylist();
                break;
            case 3:
                nextSong();
                break;
            case 4:
                previousSong();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}
