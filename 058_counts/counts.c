#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * CntArr = malloc(sizeof(*CntArr));
  CntArr->arr = NULL;
  CntArr->len = 0;
  CntArr->num_unknown = 0;
  return CntArr;
}

// create an one_count in heap, value = inputname, initial num = 1
// return a pointer to the one_count
one_count_t * get_one_count(const char * name) {
  one_count_t * one = malloc(sizeof(*one));
  size_t n = strlen(name) + 1;  // one more place for '\0'
  one->value = malloc(n);
  strncpy(one->value, name, n);
  one->num = 1;
  return one;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->num_unknown++;
    return;
  }
  for (size_t i = 0; i < c->len; i++) {
    if (strcmp(name, c->arr[i]->value) == 0) {
      c->arr[i]->num++;
      return;
    }
  }
  // if name doesn't exist, append a new element to the array
  c->arr = realloc(c->arr, (c->len + 1) * sizeof(*c->arr));
  c->arr[c->len] = get_one_count(name);
  c->len++;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %lu\n", c->arr[i]->value, c->arr[i]->num);
  }
  if (c->num_unknown > 0) {
    fprintf(outFile, "<unknown> : %lu\n", c->num_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    free(c->arr[i]->value);
    free(c->arr[i]);
  }
  free(c->arr);
  free(c);
}
