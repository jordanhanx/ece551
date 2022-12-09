#include <cstdlib>
#include <iostream>

#include "book.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./cyoa-step1 /usr/local/ece551/cyoa/story1\n";
    exit(EXIT_FAILURE);
  }
  Book game_book(argv[1]);
  game_book.print_book();

  return EXIT_SUCCESS;
}
