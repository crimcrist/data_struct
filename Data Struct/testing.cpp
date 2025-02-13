#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 100

typedef struct Contact {
    char nama [50];
    char phone [20];
    char email [50];
    struct Contact* next;
}Contact;

Contact* hashTable[TABLE_SIZE];

int hashFunction (char* name){
    int sum = 0;
    for (int i = 0; name[i] != '\0' ; i++){
        sum += name[i];
    }

    int midValue;
    char sumStr[20];
    sprintf(sumStr, "%d", sum);
    
    int len = strlen(sumStr);

    if (len % 2 == 0){
        midValue = (sumStr[len / 2 - 1] - '0') * 10 + (sumStr[len / 2] - '0');
    } else {
        midValue = sumStr[len / 2]
    }
    
}