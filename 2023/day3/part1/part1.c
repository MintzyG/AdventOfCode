#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char** CreateMatrixPadded(FILE* file){
  char** matrix = (char**)calloc(142, sizeof(char*));
  for (int i = 0; i < 142; i++) {
    matrix[i] = (char*)calloc(142, sizeof(char));
  }

  int col = 0, line = 0;
  char cc;
  for (line = 0; line < 142; line++) {
    for (col = 0;col < 142; col++) {
      matrix[line][col] = '.';
    }
  }

  col = 1, line = 1;
  while ((cc = fgetc(file)) != EOF) {
    if (cc != '\n') {
      matrix[line][col] = cc;
      col += 1;
    } else {
      col = 1;
      line += 1;
    }
  }
  return matrix;
}

int CheckVertical(int i, int j, char** matrix) {
  if (matrix[i-1][j] != '.' && !isdigit(matrix[i-1][j])) {
    return 1;
  } else if (matrix[i+1][j] != '.' && !isdigit(matrix[i+1][j])) {
    return 1;
  }
  return 0;
}

int CheckHorizontal(int i, int j, int side, char** matrix) {
  if (matrix[i-1][j+side] != '.' && !isdigit(matrix[i-1][j+side])){
    return 1;
  } else if (matrix[i][j+side] != '.' && !isdigit(matrix[i][j+side])){
    return 1;
  } else if (matrix[i+1][j+side] != '.' && !isdigit(matrix[i+1][j+side])){
    return 1;
  }
  return 0;
}

int CheckValid(int i, int j, int size, char** matrix){
  if (size == 1) {
    if (CheckVertical(i, j, matrix)) {return 1;}
    if (CheckHorizontal(i, j, -1, matrix)) {return 1;}
    if (CheckHorizontal(i, j, 1, matrix)) {return 1;}
    return 0;
  } else if (size == 2){
    if (CheckVertical(i, j, matrix)) {return 1;}
    if (CheckHorizontal(i, j, -1, matrix)) {return 1;}
    if (CheckVertical(i, j+1, matrix)) {return 1;}
    if (CheckHorizontal(i, j+1, 1, matrix)) {return 1;}
    return 0;
  } else {
    if (CheckVertical(i, j, matrix)) {return 1;}
    if (CheckHorizontal(i, j, -1, matrix)) {return 1;}
    if (CheckVertical(i, j+1, matrix)) {return 1;}
    if (CheckVertical(i, j+2, matrix)) {return 1;}
    if (CheckHorizontal(i, j+2, 1, matrix)) {return 1;}
    return 0; 
  }
  return 0;
}

int main() {
  FILE* file;
  file = fopen("in.txt", "r");
  if (!file) {
    puts("Could not open file");
    exit(1);
  }

  int answer = 0;
  char** matrix = CreateMatrixPadded(file);
  for (int i = 0; i < 142; i++) {
    for (int j = 0; j < 142; j++) {
      if (matrix[i][j] != '.' && isdigit(matrix[i][j])) {
        int number = strtoul(*(matrix + i) + j, NULL, 10);
        if (number - 10 < 0) {
          if (CheckValid(i, j, 1, matrix)){ answer += number; }
        } else if (number - 100 >= 0) {
          if (CheckValid(i, j, 3, matrix)) { answer += number; }
          j += 3;
        } else {
          if (CheckValid(i, j, 2, matrix)) { answer += number; }
          j += 2;
        }
      }
    }
  }
  printf("Answer: %d", answer);
  return 0;
}
