#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa {
    int age;
    char name[100];
    struct Mahasiswa *left;
    struct Mahasiswa *right;
    int height;
};

typedef struct Mahasiswa Mahasiswa;

Mahasiswa *createNewMhs(int age, char name[]) {
    Mahasiswa *newMhs = (Mahasiswa *) malloc(sizeof(Mahasiswa));
    newMhs->age = age;
    strcpy(newMhs->name, name);
    newMhs->left = newMhs->right = NULL;
    newMhs->height = 1;
    return newMhs;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Mahasiswa *curr) {
    return (curr == NULL) ? 0 : curr->height;
}

int getBalance(Mahasiswa *curr) {
    return (curr == NULL) ? 0 : getHeight(curr->left) - getHeight(curr->right);
}

Mahasiswa *rightRotate(Mahasiswa *curr) {
    Mahasiswa *x = curr->left;
    Mahasiswa *T2 = x->right;

    x->right = curr;
    curr->left = T2;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Mahasiswa *leftRotate(Mahasiswa *curr) {
    Mahasiswa *y = curr->right;
    Mahasiswa *T2 = y->left;

    y->left = curr;
    curr->right = T2;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

Mahasiswa *insertAVL(Mahasiswa *node, int age, char *name) {
    if (node == NULL)
        return createNewMhs(age, name);

    if (age < node->age)
        node->left = insertAVL(node->left, age, name);
    else if (age > node->age)
        node->right = insertAVL(node->right, age, name);
    else {
        printf("Age %d already exists. Skipping insert.\n", age);
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && age < node->left->age)
        return rightRotate(node);
    if (balance < -1 && age > node->right->age)
        return leftRotate(node);
    if (balance > 1 && age > node->left->age) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && age < node->right->age) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Mahasiswa *search(Mahasiswa *node, int age) {
    if (node == NULL || node->age == age)
        return node;

    if (age < node->age)
        return search(node->left, age);
    else
        return search(node->right, age);
}

void updateTree(Mahasiswa *node, int age, char newName[]) {
    Mahasiswa *target = search(node, age);
    if (target == NULL) {
        printf("Age %d not found.\n", age);
    } else {
        strcpy(target->name, newName);
        printf("Updated name for age %d to %s.\n", age, newName);
    }
}

Mahasiswa *getMinValueNode(Mahasiswa *node) {
    Mahasiswa *curr = node;
    while (curr && curr->left != NULL)
        curr = curr->left;
    return curr;
}

Mahasiswa *pop(Mahasiswa *root, int age) {
    if (root == NULL)
        return root;

    if (age < root->age)
        root->left = pop(root->left, age);
    else if (age > root->age)
        root->right = pop(root->right, age);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Mahasiswa *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Mahasiswa *temp = getMinValueNode(root->right);
            root->age = temp->age;
            strcpy(root->name, temp->name);
            root->right = pop(root->right, temp->age);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Mahasiswa *node) {
    if (node == NULL)
        return;
    inorder(node->left);
    printf("Age: %d, Name: %s\n", node->age, node->name);
    inorder(node->right);
}

int main() {
    Mahasiswa *root = NULL;
    int choice, age;
    char name[100];

    do {
        printf("\n===== Menu AVL Tree Mahasiswa =====\n");
        printf("1. Insert Mahasiswa\n");
        printf("2. Update Nama Mahasiswa\n");
        printf("3. Delete Mahasiswa\n");
        printf("4. Search Mahasiswa\n");
        printf("5. Tampilkan (Inorder)\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1:
                printf("Masukkan umur: ");
                scanf("%d", &age);
                getchar();
                printf("Masukkan nama: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                root = insertAVL(root, age, name);
                break;

            case 2:
                printf("Masukkan umur yang ingin di-update: ");
                scanf("%d", &age);
                getchar();
                printf("Masukkan nama baru: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                updateTree(root, age, name);
                break;

            case 3:
                printf("Masukkan umur yang ingin dihapus: ");
                scanf("%d", &age);
                root = pop(root, age);
                printf("Mahasiswa dengan umur %d telah dihapus (jika ada).\n", age);
                break;

            case 4:
                printf("Masukkan umur yang ingin dicari: ");
                scanf("%d", &age);
                Mahasiswa *found = search(root, age);
                if (found) {
                    printf("Ditemukan: Age: %d, Name: %s\n", found->age, found->name);
                } else {
                    printf("Tidak ditemukan.\n");
                }
                break;

            case 5:
                printf("\n== Data Mahasiswa (Inorder) ==\n");
                inorder(root);
                break;

            case 0:
                printf("Keluar dari program...\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 0);

    return 0;
}
