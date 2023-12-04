#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int card_numbers[10] = {0};
int winning_numbers[25] = {0};

void print_array(int* array, int size){
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

int main() {
  FILE* file;
  file = fopen("in.txt", "r");
  if (!file) {
    puts("Could not open file");
    exit(1);
  }

  size_t answer = 0, buffer = 100;
  char* line, *tmp_line;
  int number;

  while (1) {
    getline(&line, &buffer, file);
    if (feof(file)) {
      break;
    }
    tmp_line = strstr(line, ":") + 2;

    int counter = 0, cnt = 0;
    if (*tmp_line == ' ') {
      tmp_line += 1;
    }
    while (*tmp_line) {
      if (isdigit(*tmp_line)) {
        if (counter < 10) {
          card_numbers[counter] = strtoul(tmp_line, &tmp_line, 10);
          counter++;
        } else {
          winning_numbers[cnt] = strtoul(tmp_line, &tmp_line, 10);
          cnt++;
        }
      } else {
        tmp_line++;
      }
    }

    int tracker = 0;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 25; j++) {
        if (card_numbers[i] == winning_numbers[j]) {
          tracker += 1;
        }
      }
    }

    answer += pow(2, tracker - 1);

  }


  printf("Answer: %d", answer);

  return 0;
}
