#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  int index = 1;
  int flag_no_reuse = 0;  // flag: whether prohibit the used word, default is NO.
  if (argc == 3) {
    index = 1;
    flag_no_reuse = 0;
  }
  else if ((argc == 4) && (strcmp(argv[1], "-n") == 0)) {
    index = 2;
    flag_no_reuse = 1;
  }
  else {
    fprintf(stderr, "!!! Usage:./story_step4 [-n] words.txt story.txt\n");
    exit(EXIT_FAILURE);
  }

  FILE * f_words = fopen(argv[index], "r");
  FILE * f_story_tp = fopen(argv[index + 1], "r");
  if (f_words == NULL) {
    fprintf(stderr, "Fails to open %s\n", argv[index]);
    exit(EXIT_FAILURE);
  }
  if (f_story_tp == NULL) {
    fprintf(stderr, "Fails to open %s\n", argv[index + 1]);
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = parse_catarray(f_words);
  parse_story(f_story_tp, cats, flag_no_reuse);
  free_catarray(cats);

  if (fclose(f_words) != 0) {
    fprintf(stderr, "Fails to close %s\n", argv[index]);
    exit(EXIT_FAILURE);
  }
  if (fclose(f_story_tp) != 0) {
    fprintf(stderr, "Fails to close %s\n", argv[index + 1]);
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
