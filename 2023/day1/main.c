#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
  FILE* file;
  file = fopen("in.txt", "r");
  if (!file) {
    puts("Could not open file");
    exit(1);
  }

  char** text = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}; 
  int answer = 0;
  size_t buf_size = 64, counter = 0;
  char* line;
  int* numbers = (int*)calloc(64, sizeof(int));

  while (1) {
    getline(&line, &buf_size, file);
    if(feof(file)) { break; }

    for (int i = 0; i < 64; i++) {
      if (line[i] == '\n') {
        break;
      }
      if (isdigit(line[i])) {
        numbers[counter] += line[i] - '0'; 
        counter += 1;
      }
    }

    int tmp = 0;
    if (counter > 2) {
      for (int i = 0; i < 64; i++) {
        if(numbers[i] == 0) {
          tmp += (numbers[0]*10 + numbers[i-1]);
          break;
        }
      }
      answer += tmp;
    } else if (counter == 1) {
      tmp += (numbers[0]*10 + numbers[0]);
      answer += tmp;
    } else if (counter == 2) {
      tmp += (numbers[0]*10 + numbers[1]);
      answer += tmp;
    }

    for (int i = 0; i < 64; i++) {
      numbers[i] = 0;
    }
    counter = 0;
  }

  printf("Answer: %d", answer);

  return 0;
}
