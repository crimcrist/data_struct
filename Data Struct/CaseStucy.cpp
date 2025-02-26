#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#define SIZE 50 
 
struct Data{ 
 char coin[5]; 
 double price; 
 Data *next; 
} *arr[SIZE]; 
 
int midSquare(char coin[]){ 
 int sum = 0;
 for (int i = 0; i < strlen(coin); i++){
    sum += coin[i];
 }

 sum *= sum;
 char mid[20];
 sprintf (mid, "%d", sum);

 int x = strlen (mid);
 int hashKey = -1;

 if (x % 2 == 1){
    hashKey = (mid[x/2 - 1] - '0') * 100 + (mid[x/2] - '0') * 10 + (mid[x/2 + 1] - '0') * 1;
 } else {
    hashKey = (mid[x/2 - 1] - '0') * 10 + (mid[x/2] - '0') * 1;
 }

 return hashKey % SIZE;
} 
 
void insert(char coin[], double price){ 
 Data *data = (Data*)malloc(sizeof(Data)); 
 data->price = price; 
 strcpy(data->coin, coin); 
 data->next = NULL; 
  
 int index = midSquare(coin); 
 printf("Index: %d\n", index);

 if (arr[index] == NULL){
    arr[index] = data;
 } else {
    Data *temp = arr[index];
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = data;
 }
} 
 
int main(){ 
 insert("BTC", 97000.00); 
 insert("ETH", 2700.00); 
 insert("SOL", 172.59); 
 insert("XRP", 2.57); 
  
 return 0; 
} 