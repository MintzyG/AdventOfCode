#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(clock());
  int array[10];

  for (int i = 0; i < 10; i++) {
    array[i] = rand() % 1000;
    printf("%d ", array[i]);
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 1; j < 10 - i; j++) {
      if (array[j-1] > array[j]) {
        int tmp = array[j-1];
        array[j-1] = array[j];
        array[j] = tmp;
      }
    }
  }

  printf("\n");
  for (int i = 0; i < 10; i++) {
    printf("%d ", array[i]);
  }

  return 0;
}
