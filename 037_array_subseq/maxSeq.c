#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (array == NULL || n == 0) {
    return 0;
  }
  size_t res = 1;
  size_t cnt = 1;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      cnt++;
      res = (cnt > res) ? cnt : res;
    }
    else {
      cnt = 1;
    }
  }
  return res;
}
