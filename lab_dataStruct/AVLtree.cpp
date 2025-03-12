// AVL Tree -> bst self balancing
// Insert & Update

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Mahasiswa {
    int age;
    char name[100];
    Mahasiswa *left;
    Mahasiswa *right;
    int height;
};

Mahasiswa *createNewMhs(int age, char name[100]){
    Mahasiswa *newMhs = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    newMhs->age = age;
    strcpy (newMhs->name, name);
    newMhs->left = NULL;
    newMhs->right = NULL;
    newMhs->height = 1;

    return newMhs;
}

int max (int a, int b){
    return (a > b) ? a : b;
}

int getHeight (Mahasiswa *curr){
    if (curr == NULL){
        return 0;
    } else {
        return curr->height;
    }
}

int getBalance(Mahasiswa * curr){
    return getHeight(curr->left) - getHeight(curr->right);
}

Mahasiswa *rightRotatet (Mahasiswa* curr){
    Mahasiswa *currLeft = curr->left;
    Mahasiswa *currLeftRight = curr->left->right;

    curr->left->right = curr;
    curr->left = currLeftRight;

    curr->height = 1 + max(getHeight(curr->left),getHeight(curr->right));
    currLeft->height = 1 + max(getHeight(currLeft->left),getHeight(currLeft->right));

    return currLeft;
}

Mahasiswa *leftRotatet (Mahasiswa* curr){
    Mahasiswa *currRight = curr->right;
    Mahasiswa *currRightLeft = curr->right->left;

    curr->right->left= curr;
    curr->right = currRightLeft;

    curr->height = 1 + max(getHeight(curr->left),getHeight(curr->right));
    currRight->height = 1 + max(getHeight(currRight->left),getHeight(currRight->right));

    return currRight;
}

Mahasiswa *insertAVL(Mahasiswa *curr, int age, char name[100]){
    // Kosong
    if (curr == NULL){
        return createNewMhs(age,name);
    }
    if (age < curr->age){
        curr->left = insertAVL(curr->left, age, name);
    } else if (age > curr->age){
        curr->right = insertAVL(curr->right, age, name);
    }

    //update height
    // curr->heigh = 1 + max
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    //identify imbalance
    // LL
    if (getBalance(curr) > 1 && getBalance(curr->left) >= 0){
        // right rotate
        return rightRotatet(curr);
    }

    // RR
    if (getBalance(curr) < -1 && getBalance(curr->right) <= 0){
        // left rotate
        return leftRotatet(curr);
    }

    // LR
    if (getBalance(curr) > 1 && getBalance(curr->left) < 0){
        // left rotate subtree, right rotate tree
        curr->left = leftRotatet(curr->left);
        return rightRotatet(curr);
    }

    // RL
    if (getBalance(curr) < -1 && getBalance(curr->right) > 0){
        // right rotate subtree, left rotate tree
        curr->right = rightRotatet(curr->right);
        return leftRotatet(curr);
    }

    return curr;
}


void inOrder(Mahasiswa *curr){
    if(curr){
        inOrder(curr->left);
        printf ("Age : %d, name: %s\n", curr->age, curr->name);
        inOrder(curr->right);
    }
}

void updateTree (Mahasiswa* root, int age, char newName[100]){
    if(!root) printf ("Not Found\n");
    else if (age < root->age){
        updateTree(root->left, age, newName);
    }
    else if (age > root->age){
        updateTree(root->right, age, newName);
    }
    else if (age == root->age){
        strcpy (root->name, newName);
        printf ("Name updated\n");
    }
}

int main (){
    Mahasiswa *root = NULL;
    root = insertAVL(root, 3, "samudra");
    root = insertAVL(root, 18, "samudra");
    root = insertAVL(root, 21, "samudra");
    root = insertAVL(root, 8, "samudra");
    root = insertAVL(root, 7, "samudra");
    root = insertAVL(root, 6, "samudra");
    root = insertAVL(root, 23, "samudra");

    inOrder(root);
    updateTree(root, 21, "jovita");
    printf ("UPDATE\n");
    inOrder(root);
    return 0;


}