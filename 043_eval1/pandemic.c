#include "pandemic.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

/*
write my function: str to integer
One reason is strtoll's max return value, LLONG_MAX, is less than UINT64_MAX
*/
uint64_t my_strtoi_u64(char * nptr, char ** endptr) {
  uint64_t result = 0;
  size_t idx = 0;
  // (1)initial *endptr points to the first char of string
  if (endptr != NULL) {
    *endptr = nptr;
  }
  // (2)skip space before numbers
  while (*nptr == ' ') {
    nptr++;
  }
  // (3)convert chars into integers
  while ((nptr[idx] != '\0') && (nptr[idx] != '\n')) {
    if (nptr[idx] == '-') {
      // check whether first char is negative sign
      fprintf(stderr, "negative number{%s} is not welcome\n", nptr);
      exit(EXIT_FAILURE);
    }
    // check digit
    if ((nptr[idx] >= '0') && (nptr[idx] <= '9')) {
      // check overflow
      if ((10 * result + (nptr[idx] - '0')) < result) {
        fprintf(stderr, "nuber{%s} oveflow (more than UINT64_MAX)!\n", nptr);
        exit(EXIT_FAILURE);
      }
      // convert to integer
      result = 10 * result + (nptr[idx] - '0');
      // move *endptr point to next char
      if (endptr != NULL) {
        *endptr = &nptr[idx + 1];
      }
    }
    // point the endptr to first non-numeric char
    else if (endptr != NULL) {
      *endptr = &nptr[idx];
      break;
    }
    idx++;
  }
  // (4)return result
  return result;
  // my str to integer function is finished
}

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // check whether line points to NULL
  if (line == NULL) {
    fprintf(stderr, "Input is NULL!\n");
    exit(EXIT_FAILURE);
  }
  // check whether line has a '\0'
  if (strchr(line, '\0') == NULL) {
    fprintf(stderr, "Input:{%s} has no '\\0'!\n", line);
    exit(EXIT_FAILURE);
  }
  // check whether line's length < 1
  if (strlen(line) < 1) {
    fprintf(stderr, "Input:{%s} is empty!\n", line);
    exit(EXIT_FAILURE);
  }
  // find ','
  if (strchr(line, ',') == NULL) {
    fprintf(stderr, "Input:{%s} has no comma!\n", line);
    exit(EXIT_FAILURE);
  }

  // parse countries' name
  int idx = 0;
  while (line[idx] != ',') {
    // check whether the name has exceeded MAX_NAME_LEN
    if (idx >= (MAX_NAME_LEN - 1)) {
      fprintf(stderr, "Input:{%s} has exceeded MAX_NAME_LEN!\n", line);
      exit(EXIT_FAILURE);
    }
    ans.name[idx] = line[idx];
    idx++;
  }
  ans.name[idx] = '\0';

  // parse countries' population
  // ptr points to the start of population number
  char * ptr = &line[idx + 1];
  char * eptr = NULL;
  //ans.population = strtoll(ptr, &eptr, 10);
  ans.population = my_strtoi_u64(ptr, &eptr);

  // check whether the entire string is valid number
  if ((*eptr != '\0') && (*eptr != '\n')) {
    fprintf(stderr,
            "Popupation of input:{%s} contains non-numeric char: %c !\n",
            line,
            *eptr);
    exit(EXIT_FAILURE);
  }
  if (*eptr == *ptr) {
    fprintf(stderr, "Popupation of input:{%s} has no numbers!\n", line);
    exit(EXIT_FAILURE);
  }
  // return parsed answer
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (data == NULL) {
    fprintf(stderr, "data points to NULL!\n");
    exit(EXIT_FAILURE);
  }
  // calcaulate running average when n_days > 6 only
  if (n_days > 6) {
    // build a 7-day window
    uint64_t window = data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6];
    avg[0] = window / (double)7;
    for (size_t i = 1; i < (n_days - 6); i++) {
      // move the window day after day
      window = window - data[i - 1] + data[i + 6];
      avg[i] = window / (double)7;
    }
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (data == NULL) {
    fprintf(stderr, "data points to NULL!\n");
    exit(EXIT_FAILURE);
  }
  if (n_days < 1) {
    fprintf(stderr, "Data size (n_days) is less than 1!\n");
    exit(EXIT_FAILURE);
  }
  uint64_t cum_total = 0;
  for (size_t i = 0; i < n_days; i++) {
    cum_total += data[i];
    cum[i] = (100000 * (double)cum_total) / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (data == NULL) {
    fprintf(stderr, "data points to NULL!\n");
    exit(EXIT_FAILURE);
  }
  if (countries == NULL) {
    fprintf(stderr, "countries points to NULL!\n");
    exit(EXIT_FAILURE);
  }

  uint64_t number_cases = data[0][0];
  char * country_name = countries[0].name;

  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++)
      if (number_cases < data[i][j]) {
        number_cases = data[i][j];
        country_name = countries[i].name;
      }
  }

  printf("%s has the most daily cases with %lu\n", country_name, number_cases);
}
