#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "!!! Usage:./story_step2 words.txt\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Fails to open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = parse_catarray(f);
  printWords(cats);
  free_catarray(cats);

  if (fclose(f) != 0) {
    fprintf(stderr, "Fails to close %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
