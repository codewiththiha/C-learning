#include <stdio.h>
#include <stdlib.h>

int main() {

  int size = 5;
  int *arr = (int *)malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    printf("Malloced values%d:%d\n", i, arr[i]);
  }
  printf("Resize (extend) demo\n");
  int newsize = 7;
  int *resize = (int *)realloc(arr, newsize * sizeof(int));
  if (resize == NULL) {
    free(arr);
    return 1;
  }
  for (int i = 0; i < newsize; i++) {
    printf("Extended values%d:%d\n", i, resize[i]);
  }

  printf("Initialize values before shrinking\n");

  for (int i = 0; i < newsize; i++) {
    resize[i] = i * 10;
  }

  int shrink_size = 3;
  int *shrinked = (int *)realloc(resize, shrink_size * sizeof(int));

  if (shrinked == NULL) {
    free(resize);
    return 1;
  }

  for (int i = 0; i < shrink_size; i++) {
    printf("Shrinked values%d:%d\n", i, shrinked[i]);
  }

  free(shrinked);

  printf("Demo of calloc");
  int *zeroed = calloc(5, sizeof(int));

  for (int i = 0; i < 5; i++) {
    printf("Initialized values(calloc test):%d:%d\n", i, zeroed[i]);
  }

  free(zeroed);

  typedef struct {
    char brand[50];
    int id;
    float cost;
  } Car;

  Car *car1 = (Car *)calloc(5, sizeof(Car));

  for (int i = 0; i < 5; i++) {
    printf("Initialized values check for Car%d,%d,%s,%f\n", i, car1[i].id,
           car1[i].brand, car1[i].cost);
  }

  //// When to use arrow operator
  //   Student *arr[5];          // Array of pointers to structs
  //
  // for (int i = 0; i < 5; i++) {
  //     arr[i] = calloc(1, sizeof(Student));
  // }
  //
  // arr[0]->id = 1;           // ✅ Arrow operator!
  // arr[1]->score = 95.5;     // ✅ Arrow operator!
  // arr[i]->id                // ✅ Arrow operator

  free(car1);

  return 0;
}
