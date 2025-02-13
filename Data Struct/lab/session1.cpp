#include <stdio.h>
#include <stdlib.h>

struct Student{
  int age;
  int height;
}student2, student3;

int main(){

  struct Student student;
  // int a = 10;
  // int* ptr = &a;
  
  // printf("memory dari ptr: %d\n", &ptr);
  // printf("value dari ptr: %d\n", ptr);
  // printf("value dari memory yang disimpan: %d\n", *ptr);
  
  // // a = *ptr
  // *ptr = 20;
  
  // printf("nilai a sekarang: %d\n", a);
  
  // Memory allocation example
  // malloc(sizeof(int))

  int* ptr = (int *)malloc(sizeof(int));
  
  struct arrStudent;
  
  *ptr = 20;

  printf("alamat baru: %d, value dari alamat: %d", ptr, *ptr);

  // Alokasi memori untuk struct
  Student* ptr2 = (Student*)malloc(sizeof(Student));

  //akses anggota dari struct pointer
  ptr2->age = 21;
  ptr2->height = 175;

  printf("age: %d, height: %d", ptr2->age, ptr2->height);

  // melepaskan alokasi memori
  free(ptr2);

  

  //akses anggota dari array of struct
  arrStudent[0].age = 12;
  arrStudent[1].age = 13;

}