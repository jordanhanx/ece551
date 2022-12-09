#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int getKey(FILE * f) {
  int arr[26] = {0};
  int c;
  int idx = 0;
  int k;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      arr[tolower(c) - 'a']++;
    }
  }

  for (int i = 0; i < 26; i++) {
    idx = (arr[i] > arr[idx]) ? i : idx;
  }

  k = idx + 'a' - 'e';
  if (k < 0) {
    k = 26 + k;
  }

  return k;
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Error : too few arguments\n");
    return EXIT_FAILURE;
  }
  if (argc > 2) {
    fprintf(stderr, "Error : too many arguments\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error of fopen");
    return EXIT_FAILURE;
  }
  int k = getKey(f);

  if (fclose(f) != 0) {
    perror("Error of fclose");
    return EXIT_FAILURE;
  }

  fprintf(stdout, "%d\n", k);

  return EXIT_SUCCESS;
}
