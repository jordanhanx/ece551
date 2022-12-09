#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
/*
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    std::cerr << "Fails to open:" << fname << "\n";
    exit(EXIT_FAILURE);
  }
  uint64_t * arr = new uint64_t[257]();
  int c = 0;
  while ((c = fgetc(f)) != EOF) {
    arr[c]++;
  }
  arr[256]++;
  if (fclose(f) != 0) {
    std::cerr << "Fails to close:" << fname << "\n";
    exit(EXIT_FAILURE);
  }
  return arr;
}
*/

uint64_t * readFrequencies(const char * fname) {
  std::ifstream ifs(fname);
  if (!ifs) {
    std::cerr << "Fails to open:" << fname << "\n";
    exit(EXIT_FAILURE);
  }
  uint64_t * arr = new uint64_t[257]();
  int c = ifs.get();
  while (ifs) {
    arr[c]++;
    c = ifs.get();
  }
  arr[256]++;
  ifs.close();
  return arr;
}
