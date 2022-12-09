#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

size_t readstdin(char *** ptr) {
  *ptr = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&curr, &sz, stdin) >= 0) {
    *ptr = realloc(*ptr, (i + 1) * sizeof(**ptr));
    (*ptr)[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  return i;
}

size_t readfiles(char *** ptr, char * filename) {
  *ptr = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error: fail to open %s", filename);
    exit(EXIT_FAILURE);
  }

  while (getline(&curr, &sz, f) >= 0) {
    *ptr = realloc(*ptr, (i + 1) * sizeof(**ptr));
    (*ptr)[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);

  if (fclose(f) != 0) {
    fprintf(stderr, "Error: fail to close %s", filename);
    exit(EXIT_FAILURE);
  }
  return i;
}

void show(char ** lines, size_t row) {
  sortData(lines, row);
  for (size_t i = 0; i < row; i++) {
    fprintf(stdout, "%s", lines[i]);
    free(lines[i]);
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char ** lines = NULL;
  size_t row = 0;
  if (argc == 1) {
    row = readstdin(&lines);
    show(lines, row);
    free(lines);
  }
  else {
    for (int i = 1; i < argc; i++) {
      row = readfiles(&lines, argv[i]);
      show(lines, row);
      free(lines);
    }
  }

  return EXIT_SUCCESS;
}
