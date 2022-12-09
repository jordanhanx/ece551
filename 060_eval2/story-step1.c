#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  int flag_no_reuse = 0;  // useful in step4, but not here

  if (argc != 2) {
    fprintf(stderr, "!!! Usage:./story_step1 story.txt\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Fails to open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  parse_story(f, NULL, flag_no_reuse);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fails to close %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
