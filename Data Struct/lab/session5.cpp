#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    int id;
    char nama[101];
    struct Student *left, *right;
};

struct Student *createStudent(int id, char *name){
    struct Student *newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->id = id;
    strcpy (newStudent->nama, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

struct Student *insert (struct Student *root, int id, char *name){
    // Case 1 : Kalo tree belum kebuat, kita bikin root Nodenya saja
    if (root == NULL){
        return createStudent(id, name);
    }

    // Case 2 : ID yang kita mau insert > current node punya id
    if (id > root->id){
        root->right = insert(root->right, id, name);
    }

    // Case 3 : ID yang kita mau insert < current node punya id
    else if (id < root->id) {
        root->left = insert (root->left, id, name);
    }

    // Case 4 : Kalo valuenya udah ada (duplicate) , kita return nodenya saja
    return root;
}

void inorder (struct Student *root){
    if (root == NULL) return;
    inorder(root->left);
    printf("Student ID : %d\nName: %s\n",root->id, root->nama);
    inorder(root->right);
}

void preorder (struct Student *root){
    if (root == NULL) return;
    printf("Student ID : %d\nName: %s\n",root->id, root->nama);
    preorder(root->left);
    preorder(root->right);
}

void postorder (struct Student *root){
    if (root == NULL) return; 
    postorder(root->left);
    postorder(root->right);
    printf("Student ID : %d\nName: %s\n",root->id, root->nama);
}

struct Student *search (struct Student *root, int id){
    // Case 1 : Kalo search ga ketemu
    if (root == NULL){
        puts ("Not found");
        return NULL;
    }

    // Case 2 : Kalau seacrh ketemu
    else if (root->id == id){
        puts("found");
        return root;
    }

    // Case 3 : Kalau id yang mau di search itu lebih gede dari current id
    else if (id > root->id){
        return search(root->right, id);
    }

    // Case 3 : Kalau id yang mau di search itu lebih kecil dari current id
    else if (id < root->id){
        return search(root->left, id);
    }
}
struct Student *update (struct Student *root,int id, char *newName){
    // Case 1 : Kalo search ga ketemu
    if (root == NULL){
        puts ("Not Found");
        return NULL;
    }

    // Case 2 : Kalau search ketemu tinggalganti namanya
    else if (root->id == id){
        puts ("Found");
        strcpy (root->nama, newName);
        return root;
    }

    // Case 3 : Kalau id yang mau di update itu lebih gede dari current id
    else if (id > root->id){
        return update(root->right, id);
    }

    // Case 3 : Kalau id yang mau di update itu lebih kecil dari current id
    else if (id < root->id){
        return update(root->left, id);
    }
}

int main(){
    struct Student *root = NULL;
    puts ("Inserting... ");
    root = insert (root, 1 , "bill");
    root = insert (root, 2 , "tom");
    root = insert (root, 5 , "jake");
    root = insert (root, 7 , "diana"); 
    root = insert (root, 378 , "eve");
    root = insert (root, 8 , "kay"); 

    puts ("Insert Successfull.....!!!!!");

    inorder(root);
    printf ("%d -> %s\n", root->id, root->nama);

    struct Student *searchStudent = update(root, 378);
    if (searchStudent!= NULL){
        printf ("Found Student with id %d and name %s\n", searchStudent->id, searchStudent->nama);
    }

    //Updating
    puts ("Updating");
    struct Student *updateStudent = search(root, 1, "tommy");
    if (updateStudent != NULL){
        printf ("Update Student with id %d, New NAme is %s\n", updateStudent->id, updateStudent->nama);
    }



    return 0;
}
