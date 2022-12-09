#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define matrix_size 10

void rotMatrix(FILE * f) {
  char matrix[matrix_size][matrix_size + 2];  // 2 more spaces for '\n' and '\0'
  int idx = 0;
  while (fgets(matrix[idx], matrix_size + 2, f) != NULL) {
    if (strchr(matrix[idx], '\n') != &matrix[idx][matrix_size]) {
      fprintf(stderr, "line %d has too few/many chars, instead of 10\n", idx);
      exit(EXIT_FAILURE);
    }
    idx++;
  }

  if (idx != matrix_size) {
    fprintf(stderr, "Input has %d lines, instead of 10\n", idx);
    exit(EXIT_FAILURE);
  }

  char rotM[matrix_size][matrix_size];
  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      rotM[i][j] = matrix[matrix_size - j - 1][i];
      fprintf(stdout, "%c", rotM[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Error : too few/many arguments\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error of fopen");
    return EXIT_FAILURE;
  }

  rotMatrix(f);

  if (fclose(f) != 0) {
    perror("Error of fclose");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
