#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

typedef struct node{
    int val;
    int height;
    node *left;
    node *right;
};

node* createNode(int val, int height) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->val = val;
    newNode->height = height;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int max (int a, int b){
    return (a > b) ? a : b;
}

int height(node *root){
    if (root == NULL){
        return 0;
    } else {
        return root->height;
    }
}

int getBalance(node *root){
    if (root == NULL){
        return 0;
    }
    return height(root->left) - height(root->right);
}


node* leftRotate(node *root){
    node *currRight = root->right;
    node *currRightLeft = currRight->left;

    currRight->left = root;
    root->right = currRightLeft;

    root->height = 1 + max(height(root->left), height(root->right));
    currRight->height = 1 + max(height(currRight->left), height(currRight->right));

    return currRight;
}

node* rightRotate(node *root){
    node *currLeft = root->left;
    node *currLeftRight = currLeft->right;

    currLeft->right = root;
    root->left = currLeftRight;

    root->height = 1 + max(height(root->left), height(root->right));
    currLeft->height = 1 + max(height(currLeft->left), height(currLeft->right));

    return currLeft;
}

node* insert (node *root, int val){
    if (root == NULL){
        return createNode(val, 1);
    }
    if (val < root->val){
        root->left = insert(root->left, val);
    } else if (val > root->val){
        root->right = insert(root->right, val);
    } else {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    if (getBalance(root) > 1 && getBalance(root->left) >= 0){
        return rightRotate(root);
    }

    if (getBalance(root) < -1 && getBalance(root->right) <= 0){
        return leftRotate(root);
    }

    if (getBalance(root) > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (getBalance(root) < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(node *root){
    if (root){
        inOrder(root->left);
        printf ("%d ", root->val);
        inOrder(root->right);
    }
}               

int main (){
    node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    inOrder(root);
    return 0;
}
// Output: 10 20 25 30 40 50