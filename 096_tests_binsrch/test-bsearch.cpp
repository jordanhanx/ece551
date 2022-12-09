#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  // write code below
  int token = 1;
  if (low < high) {
    token = (int)log2(high - low) + 1;
  }
  CountedIntFn counted_int_fn(token, f, mesg);
  int actual_ans = binarySearchForZero(&counted_int_fn, low, high);
  if (expected_ans != actual_ans) {
    std::cerr << "expected_ans(" << expected_ans << ") != actual_ans(" << actual_ans
              << ") in " << mesg << "\n";
    exit(EXIT_FAILURE);
  }
}

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

int main(void) {
  SinFunction sin_fn;
  check(&sin_fn, 0, 157080, 52359, "SinFunction testcase 1");
  check(&sin_fn, 0, 52359, 52358, "SinFunction testcase 2");
  return EXIT_SUCCESS;
}
