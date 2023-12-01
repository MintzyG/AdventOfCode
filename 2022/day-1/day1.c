#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

int main() {
  FILE* file;
  file = fopen("in.txt", "r");
  if (!file) {
    puts("Could not open file");
    exit(1);
  }

  char* line;
  size_t buf_size = 8, counter = 0, size = 1, answer = 0;
  uintmax_t num = 0;
  size_t* elfs = (size_t*)calloc(size, sizeof(size_t));

  while (!feof(file)) {
    getline(&line, &buf_size, file);
    num = strtoumax(line, NULL, 10);
    if (num == UINTMAX_MAX && errno == ERANGE) exit(1);
    if (num == 0) {
      if (answer < elfs[counter]) answer = elfs[counter];
      counter += 1;
    } else {
      if (counter >= size) {
        size *= 2;
        size_t* tmp = (size_t*)calloc(size, sizeof(size_t));
        memcpy(tmp, elfs, size/2);
        elfs = tmp;
        elfs[counter] += num;
      } else { elfs[counter] += num; }
    }
  }
  printf("Answer: %ld", answer);
  return 0;
}
