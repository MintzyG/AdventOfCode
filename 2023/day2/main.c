#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
  FILE* file;
  file = fopen("in.txt", "r");
  if (!file) {
    puts("Could not open file");
    exit(1);
  }

  size_t answer = 0, bufsize = 64, next = 0, id = 0;
  char* line, *game;
  int validator = 0;

  while (1) {
    getline(&line, &bufsize, file);
    game = strstr(line, ":");
    // puts(line);
    // puts(game);

    if(feof(file)){ break; }

    id += 1;
    while (1) {
      while (*game) {
        if (isdigit(*game)) {
          validator = strtoul(game, NULL, 10);
          break;
        } else {
          game += 1;
          if (game[0] == '\n') { answer += id; /* printf("valid game\n") */; next = 1; break; }
        }
      }
      if (next == 1) { next = 0; break;}

      // printf("%d ", validator);
      // Aligns color with text start for reading;
      char color;
      if (validator - 10 >= 0) {
        game += 3;
        color = game[0];
      } else {
        game += 2;
        color = game[0];
      }

      // printf("%c ", color);
      if (validator < 13) {
        continue;
      } else if (validator > 14) {
        // printf("invalid game\n");
        break;
      } else if (validator == 13 && color == 'r') {
        // printf("invalid game\n");
        break;
      } else if (validator == 14 && color != 'b') {
        // printf("invalid game\n");
        break;
      } else {
        continue;
      }
    }
  }
  printf("Answer: %ld", answer);
  return 0;
}
