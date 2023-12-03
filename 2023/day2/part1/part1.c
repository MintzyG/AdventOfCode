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
    id += 1;

    if(feof(file)){ break; }
    while (1) {
      while (*game)
        if (isdigit(*game)) {
          validator = strtoul(game, NULL, 10);
          break;
        } else {
          game += 1;
          if (game[0] == '\n') { answer += id; /* printf("valid game\n") */; next = 1; break; }
        }
      if (next == 1) { next = 0; break;}

      char color;
      if (validator - 10 >= 0) { game += 3; color = game[0]; } 
      else { game += 2; color = game[0]; }

      if (validator < 13)
        continue;
      else if (validator > 14)
        break;
      else if (validator == 13 && color == 'r')
        break;
      else if (validator == 14 && color != 'b')
        break;
      else
        continue;
    }
  }
  printf("Answer: %ld", answer);
  return 0;
}
