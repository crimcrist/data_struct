#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char title[100];
    struct Song *next;
    struct Song *prev;
} Song;

typedef struct {
    Song *head;
    Song *current;
    Song *tail;
    int loop;
} Playlist;

int count = 0;

Playlist *createPlaylist() {
    Playlist *playlist = (Playlist *)malloc(sizeof(Playlist));
    playlist->head = NULL;
    playlist->current = NULL;
    playlist->tail = NULL;
    playlist->loop = 0;
    return playlist;
}

void addSong(Playlist *playlist, const char *title) {
    Song *newSong = (Song *)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (playlist->head == NULL) {
        playlist->head = newSong; 
        playlist->tail = newSong;
    } else {
        newSong->prev = playlist->tail;
        playlist->tail->next = newSong;
        playlist->tail = newSong;
    }
    count++;
}

void displayPlaylist(Playlist *playlist) {
    Song *temp = playlist->head;
    if (temp == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    printf("\n~ Playlist: ~\n");
    puts ("==========================");
    int index = 1;
    while (temp != NULL) {
        printf("%d. %s\n", index++, temp->title);
        temp = temp->next;
    }
    puts ("==========================");
}

void nextSong(Playlist *playlist) {
    if (playlist->current == NULL) {
        playlist->current = playlist->head;
    } else if (playlist->current->next != NULL) {
        playlist->current = playlist->current->next;
    } else if (playlist->loop) {
        playlist->current = playlist->head;
    } else {
        printf("End of playlist.\n");
        return;
    }
    printf("Now playing: %s\n", playlist->current->title);
}

void previousSong(Playlist *playlist) {
    if (playlist->current == NULL) {
        playlist->current = playlist->head;
    } else if (playlist->current->prev != NULL) {
        playlist->current = playlist->current->prev;
    } else if (playlist->loop) {
        playlist->current = playlist->tail;
    } else {
        printf("Start of playlist.\n");
        return;
    }
    printf("Now playing: %s\n", playlist->current->title);
}

void setLoop(Playlist *playlist) {
    playlist->tail->next = playlist->head;
    playlist->head->prev = playlist->tail;
    playlist->loop = 1;
    printf("Playlist set to loop.\n");
}

void setPlay(Playlist *playlist) {
    playlist->tail->next = NULL;
    playlist->head->prev = NULL;
    playlist->loop = 0;
    printf("Playlist set to play once.\n");
}

int main() {
    Playlist *playlist = createPlaylist();

    int choice;
    char title[100];
    do {
        printf("\n~~ MENU PLAYLIST SONG: ~~\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Set To Loop\n");
        printf("4. Set To Play Once\n");
        printf("5. Next Song\n");
        printf("6. Previous Song\n");
        printf("7. Exit\n");
        
        do {
          printf("Choose an option: ");  
          scanf("%d", &choice); getchar();
        } while (choice < 1 || choice > 7);
        
        switch (choice) {
            case 1:
                printf("Enter song title: ");
                scanf(" %[^\n]", title);
                addSong(playlist, title);
                break;
            case 2:
                displayPlaylist(playlist);
                break;
            case 3:
                setLoop(playlist);
                break;
            case 4:
                setPlay(playlist);
                break;
            case 5:
                nextSong(playlist);
                break;
            case 6:
                previousSong(playlist);
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}
