#include <cstdlib>
#include <iostream>

#include "book.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./cyoa-step3 /usr/local/ece551/cyoa/story1\n";
    exit(EXIT_FAILURE);
  }
  Book game_book(argv[1]);
  game_book.check().print_all_win_ways();

  return EXIT_SUCCESS;
}
