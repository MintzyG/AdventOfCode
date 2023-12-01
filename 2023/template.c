#include <stdio.h>
#include <stdlib.h>

int main()
{

  FILE* file;
  file = fopen("in.txt", "r");
  if (!file) {
    puts("Could not open file");
    exit(1);
  }

  int answer = 0;

  /* Code goes here */

  printf("Answer: %d", answer);

  return 0;
}
