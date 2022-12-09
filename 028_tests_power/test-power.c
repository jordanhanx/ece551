#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);  // prototype for power function

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(1, 1, 1);
  run_check(0, 1, 0);
  run_check(1, 0, 1);
  run_check(0, 0, 1);
  run_check(-1, 2, 1);
  run_check(-1, 1, -1);

  return EXIT_SUCCESS;
}
