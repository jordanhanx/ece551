#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  int flag_no_reuse = 0;  // useful in step4, not here

  if (argc != 3) {
    fprintf(stderr, "!!! Usage:./story_step3 words.txt story.txt\n");
    exit(EXIT_FAILURE);
  }
  FILE * f1 = fopen(argv[1], "r");
  FILE * f2 = fopen(argv[2], "r");
  if (f1 == NULL) {
    fprintf(stderr, "Fails to open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if (f2 == NULL) {
    fprintf(stderr, "Fails to open %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = parse_catarray(f1);
  parse_story(f2, cats, flag_no_reuse);
  free_catarray(cats);

  if (fclose(f1) != 0) {
    fprintf(stderr, "Fails to close %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if (fclose(f2) != 0) {
    fprintf(stderr, "Fails to close %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
