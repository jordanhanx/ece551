#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// split a line into 2 parts: key and value
// return a point to the kvpair
kvpair_t * get_kvPair(char * line) {
  // allocate kvpair
  kvpair_t * ptr_kv = malloc(sizeof(*ptr_kv));
  ptr_kv->key = NULL;
  ptr_kv->value = NULL;
  // find '=' and '\0'
  char * ptr_end = strchr(line, '\n');
  if (ptr_end == NULL) {
    ptr_end = strchr(line, '\0');
  }
  char * ptr_eq = strchr(line, '=');
  if (ptr_eq != NULL) {
    size_t len_key = ptr_eq - line;
    size_t len_value = ptr_end - (ptr_eq + 1);
    // allocate kvpair.key
    ptr_kv->key = malloc(len_key + 1);  // one more place for '\0'
    strncpy(ptr_kv->key, line, len_key);
    ptr_kv->key[len_key] = '\0';
    // allocate kvpair.value
    ptr_kv->value = malloc(len_value + 1);  // one more place for '\0'
    strncpy(ptr_kv->value, ptr_eq + 1, len_value);
    ptr_kv->value[len_value] = '\0';
  }
  return ptr_kv;
}

// read file line by line, get a kvpair each line and append it to the array of kvpairs
// return a pointer to the kvarray
kvarray_t * get_kvArray(FILE * f) {
  // malloc kvarray
  kvarray_t * ptr_kvarr = malloc(sizeof(*ptr_kvarr));
  ptr_kvarr->arr = NULL;
  ptr_kvarr->len = 0;
  // read and split each line
  char * line = NULL;
  size_t s_line = 0;
  while (getline(&line, &s_line, f) >= 0) {
    // reallocate the array of kvpair
    ptr_kvarr->arr =
        realloc(ptr_kvarr->arr, (ptr_kvarr->len + 1) * sizeof(*ptr_kvarr->arr));
    // append new kvpair to the array
    ptr_kvarr->arr[ptr_kvarr->len] = get_kvPair(line);
    // update length of the array
    if (ptr_kvarr->arr[ptr_kvarr->len]->key == NULL) {
      free(ptr_kvarr->arr[ptr_kvarr->len]);
    }
    else {
      ptr_kvarr->len++;
    }
    free(line);
    line = NULL;
  }
  free(line);
  return ptr_kvarr;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to open %s", fname);
    exit(EXIT_FAILURE);
  }
  kvarray_t * kvarr = get_kvArray(f);

  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close %s", fname);
    exit(EXIT_FAILURE);
  }

  return kvarr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    free(pairs->arr[i]->key);
    free(pairs->arr[i]->value);
    free(pairs->arr[i]);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i]->key, pairs->arr[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * v = NULL;
  for (size_t i = 0; i < pairs->len; i++) {
    if (strcmp(key, pairs->arr[i]->key) == 0) {
      v = pairs->arr[i]->value;
      break;
    }
  }
  return v;
}
