#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t length) {
  if (maxSeq(array, n) != length) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(NULL, 0, 0);

  int array2[] = {0, 1, 1, 3, 4};
  run_check(array2, 5, 3);

  int array4[] = {0, -1, -2, -3, -4};
  run_check(array4, 5, 1);

  return EXIT_SUCCESS;
}
