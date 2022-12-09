#include <cstdlib>
#include <iostream>

#include "book.hpp"
#include "reader.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./cyoa-step2 story1\n";
    exit(EXIT_FAILURE);
  }
  Book game_book(argv[1]);
  game_book.check();

  Reader reader(game_book);
  while (!reader.is_final()) {
    reader.read_page();
    reader.goto_dest_page();
  }
  reader.read_page();  // print story's final

  return EXIT_SUCCESS;
}
