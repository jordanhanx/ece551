#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = strlen(inputName);
  char * outputName = malloc(len + 8);
  strncpy(outputName, inputName, len);
  char suffix[] = ".counts";
  strncpy(outputName + len, suffix, 7);
  outputName[len + 7] = '\0';
  return outputName;
}
