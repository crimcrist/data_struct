#include <stdio.h>
#include <string.h>

struct game {
    char nama[100];
    char rank[10];
    int HP;
    int magic;
    int gold;
};

struct game character[100];
int count = 0;

int nextInt();
void menu();
void insert();
void view();
void del();
void upgrade();

int main() {
    int input;
    while (1) {
        menu();
        do {
            printf(">> ");
            input = nextInt();
        } while (input < 1 || input > 4);

        switch (input) {
            case 1:
                insert();
                break;
            case 2:
                view();
                break;
            case 3:
                del();
                break;
            case 4:
                upgrade();
                break;
        }
    }
}

void insert() {
    struct game newCharacter;

    printf("Masukkan nama karakter: ");
    scanf("%s", newCharacter.nama);
    getchar();

    do {
        printf("Masukkan rank (bronze/silver/gold): ");
        scanf("%s", newCharacter.rank);
        getchar();
    } while (strcmp(newCharacter.rank, "bronze") != 0 && strcmp(newCharacter.rank, "silver") != 0 && strcmp(newCharacter.rank, "gold") != 0);

    printf("Masukkan HP: ");
    newCharacter.HP = nextInt();

    printf("Masukkan magic: ");
    newCharacter.magic = nextInt();

    printf("Masukkan gold: ");
    newCharacter.gold = nextInt();

    character[count++] = newCharacter;
    printf("Karakter berhasil ditambahkan!\n");
}

void view() {
    if (count == 0) {
        printf("Tidak ada karakter untuk ditampilkan.\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("No.%d\n", i + 1);
            printf("Nama Character : %s\n", character[i].nama);
            printf("Rank : %s\n", character[i].rank);
            puts("======================================");
        }
    }
}

void del() {
    if (count == 0) {
        printf("Tidak ada karakter untuk dihapus.\n");
        return;
    }

    view();

    char namadel[100];
    printf("Masukkan nama karakter yang ingin dihapus: ");
    scanf("%s", namadel);
    getchar();

    int flag = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(namadel, character[i].nama) == 0) {
            for (int j = i; j < count - 1; j++) {
                character[j] = character[j + 1];
            }
            count--;
            flag = 1;
            printf("Karakter berhasil dihapus!\n");
            return;
        }
    }

    if (!flag) {
        printf("Karakter tidak ditemukan!\n");
    }
}

void upgrade() {
    if (count == 0) {
        printf("Tidak ada karakter untuk di-upgrade.\n");
        return;
    }

    view();

    char namaupgrade[100];
    printf("Masukkan nama karakter yang ingin di-upgrade: ");
    scanf("%s", namaupgrade);
    getchar();

    int flag = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(namaupgrade, character[i].nama) == 0) {
        	if (character.gold >= 50){
        	    character[i].HP += 150;
            	character[i].magic += 150;
            	character[i].gold -= 50;
            	printf("Karakter berhasil di-upgrade!\n");
            	return;	
			} else{
			    printf("Karakter tidak berhasil di-upgrade dikarenakan gold tidak mencukupi!\n");
            	return;	
			}

        }
    }

    if (!flag) {
        printf("Karakter tidak ditemukan!\n");
    }
}

void menu() {
    puts("WELCOME TO THE GAME!!");
    puts("1. Insert");
    puts("2. View");
    puts("3. Delete");
    puts("4. Upgrade");
}

int nextInt() {
    int input;
    scanf("%d", &input);
    getchar();
    return input;
}

