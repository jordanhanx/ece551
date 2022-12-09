#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int i = low;
  int j = high - 1;
  while (i < j) {
    int mid = (i + j) / 2;
    int invoke_ans = f->invoke(mid);
    if (invoke_ans == 0) {
      return mid;
    }
    else if (invoke_ans > 0) {
      j = mid - 1;
    }
    else {
      i = mid + 1;
    }
  }
  int ans = low;
  int mid = (i + j) / 2;
  if (mid > ans) {
    if (f->invoke(mid) > 0) {
      ans = mid - 1;
    }
    else {
      ans = mid;
    }
  }
  return ans;
}
