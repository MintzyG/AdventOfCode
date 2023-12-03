#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct cube {
  char letra;
  int amount;
}Cube;

typedef struct set {
  Cube red;
  Cube green;
  Cube blue;
}Set;


int main() {
  FILE* file;
  file = fopen("in.txt", "r");
  if (!file) {
    puts("Could not open file");
    exit(1);
  }

  Set* all_sets = (Set*)calloc(100, sizeof(Set));
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
          if (game[0] == '\n') { 
            /* printf("valid game\n"); */ 
            next = 1; 
            break; 
          }
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

      // keeps track of biggest number for each cube
      switch (color) {
        case 'r':
          if (all_sets[id-1].red.amount < validator) {  
            all_sets[id-1].red.amount = validator;
            // printf("%c%d ", color, validator);
          }
          break;
        case 'g':
          if (all_sets[id-1].green.amount < validator) {  
            all_sets[id-1].green.amount = validator;
            // printf("%c%d ", color, validator);
          }
          break;
        case 'b':
          if (all_sets[id-1].blue.amount < validator) {  
            all_sets[id-1].blue.amount = validator;
            // printf("%c%d ", color, validator);
          }
          break;
      }
    }
    printf("\n");
    int red = all_sets[id-1].red.amount; 
    int green = all_sets[id-1].green.amount; 
    int blue = all_sets[id-1].blue.amount;
    answer += red * green * blue;
  }
  printf("Answer: %ld", answer);
  return 0;
}
