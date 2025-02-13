#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct tnode {
    char value;
    struct tnode *left;
    struct tnode* right;
}tnode;

tnode* createNode (char value){
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int isOperator (char c){
    return (c == '+' || c == '-' || c == '*'|| c == '/' || c == '^' );
}

void buildPrefTree(tnode** root, char prefeq[], int *pos){
    if (*root == NULL){
        *root = createNode(prefeq[*pos]);
    }
        if(isOperator(prefeq[*pos])){
            *pos = *pos + 1; // Untuk mengeser char berikutnya
            (*root)->left = createNode(prefeq[*pos]); // membuat yang sebelah kiri
            buildPrefTree (&(*root)->left, prefeq, pos); // mengecek apakah ada operator lagi atau ga

            *pos = *pos + 1;
            (*root)->right = createNode(prefeq[*pos]);
            buildPrefTree (&(*root)->right, prefeq, pos);
        }
}

void inorder(tnode* root) {
    if (root != NULL){
        inorder(root->left);
        printf ("%c ", root->value);
        inorder(root->right);
    }
}

void preorder(tnode* root) {
    if (root != NULL){
        printf ("%c ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(tnode* root) {
    if (root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf ("%c ", root->value);
    }
}

tnode* buildPostTree (char postfix[]){
    tnode* stack[100];
    int top = -1;
    for (int i = 0; postfix[i] != 0; i++){
        tnode* newNode = createNode(postfix[i]);
        if (isdigit(postfix[i])){
            stack[++top] = newNode;
        } else if (isOperator(postfix[i])){
            newNode ->right = stack [top--];
            newNode ->left = stack [top--];
            stack[++top] = newNode;
        }
    }
    return stack[top]; 
}

// Fungsi untuk menentukan prioritas operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0; // Untuk tanda kurung
}

// Fungsi untuk membangun pohon ekspresi dari infix (mendukung tanda kurung)
tnode* buildInfixTree(char infix[]) {
    tnode* valueStack[100]; // Stack untuk operand (angka)
    char opStack[100];      // Stack untuk operator
    int valTop = -1, opTop = -1;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {  // Jika angka, buat node dan push ke valueStack
            valueStack[++valTop] = createNode(infix[i]);
        } 
        else if (infix[i] == '(') { // Jika menemukan tanda kurung buka, push ke opStack
            opStack[++opTop] = infix[i];
        } 
        else if (infix[i] == ')') { // Jika menemukan tanda kurung tutup, proses hingga '('
            while (opTop >= 0 && opStack[opTop] != '(') {
                tnode* newNode = createNode(opStack[opTop--]); // Ambil operator dari stack
                newNode->right = valueStack[valTop--];  // Ambil operand kanan
                newNode->left = valueStack[valTop--];   // Ambil operand kiri
                valueStack[++valTop] = newNode; // Masukkan subtree ke valueStack
            }
            opTop--; // Hapus '(' dari stack
        } 
        else if (isOperator(infix[i])) { // Jika menemukan operator
            while (opTop >= 0 && precedence(opStack[opTop]) >= precedence(infix[i])) {
                tnode* newNode = createNode(opStack[opTop--]); // Ambil operator dari stack
                newNode->right = valueStack[valTop--];  // Ambil operand kanan
                newNode->left = valueStack[valTop--];   // Ambil operand kiri
                valueStack[++valTop] = newNode; // Masukkan subtree ke valueStack
            }
            opStack[++opTop] = infix[i]; // Push operator ke stack
        }
    }

    // Jika masih ada operator di opStack, buat subtree terakhir
    while (opTop >= 0) {
        tnode* newNode = createNode(opStack[opTop--]);
        newNode->right = valueStack[valTop--];
        newNode->left = valueStack[valTop--];
        valueStack[++valTop] = newNode;
    }

    return valueStack[valTop]; // Root dari pohon ekspresi
}

int evaluate (tnode* root){
    if(root->value == '+'){
        return evaluate(root->left) + evaluate(root->right);
    } else if (root->value == '-'){
        return evaluate(root->left) - evaluate(root->right);
    }else if (root->value == '*'){
        return evaluate(root->left) * evaluate(root->right);
    }else if (root->value == '/'){
        return evaluate(root->left) / evaluate(root->right);
    }else if (root->value == '^'){
        return (int) pow(evaluate(root->left), evaluate(root->right));
    }else {
        return root->value - '0';
    }
}

int main (){
    char prefeq[] = "+*234";
    char posteq[] = "351^+";
    int pos = 0;
    tnode *root = NULL;
    tnode* rootPostfix = NULL;

    buildPrefTree(&root, prefeq, &pos);
    rootPostfix = buildPostTree(posteq);

    printf("Inorder Traversal: ");
    inorder(root); 
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root); 
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root); 
    printf("\n");

    int res = evaluate(root);
    printf ("result : %d\n", res);

    printf("\nInorder Traversal (Postfix): ");
    inorder(rootPostfix); 
    printf("\n");

    printf("Preorder Traversal (Postfix): ");
    preorder(rootPostfix); 
    printf("\n");

    printf("Postorder Traversal (Postfix): ");
    postorder(rootPostfix); 
    printf("\n");

    int resPostfix = evaluate(rootPostfix);
    printf("Result (Postfix): %d\n", resPostfix);

    char infix[] = "(3+5)*2"; // Ekspresi infix yang akan dibangun menjadi pohon
    tnode* rootInfix = buildInfixTree(infix);

    printf("Inorder Traversal (Infix): ");
    inorder(rootInfix);
    printf("\n");

    printf("Preorder Traversal (Prefix): ");
    preorder(rootInfix);
    printf("\n");

    printf("Postorder Traversal (Postfix): ");
    postorder(rootInfix);
    printf("\n");

    return 0;
}