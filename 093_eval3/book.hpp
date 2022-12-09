/*------------------------------  book.hpp  ---------------------------------*/
#ifndef __BOOK_HPP__
#define __BOOK_HPP__

#include <cstdlib>
#include <set>
#include <stack>
#include <string>

#include "page.hpp"
#include "path.hpp"

/*****************************************************************************
 * Class: Book        // represent a "cyoa" story book, including everything *
 * @field: pages      // pageList, including everything of a page            *
 * @method: parse_line()       // parse a line of a story.txt                *
 * @method: parse_page()       // try to parse a page declaration from a line*
 * @method: parse_variable()   // try to parse a key setting from a line     *
 * @method: parse_choice()     // try to parse a choice adding from a line   *
 * @method: parse_key_choice() // try to parse a special choice adding       *
 * @method: check_3a()         // check whether pass rule_3a                 *
 * @method: check_3b()         // check whether pass rule_3b                 *
 * @method: check_3c()         // check whether pass rule_3c                 *
 * @method: print_book()       // print whole book correctly                 *
 * @method: load_book()        // load book's everything from the directory  *
 * @method: check()            // check whether book complys with all rules  *
 * @method: []            // return a const reference to the specific page   *
 * @method: print_all_win_ways()  // use DFS to print all ways to win        *
 *****************************************************************************/
class Book {
  pageList pages;

  void parse_line(const std::string & line, const std::string & directory);
  bool parse_page(const std::string & line, const std::string & directory);
  bool parse_variable(const std::string & line);
  bool parse_choice(const std::string & line);
  bool parse_key_choice(const std::string & line);

  static void check_3a(const std::set<size_t> & pages_set);
  static void check_3b(const std::set<size_t> & pages_set, size_t page_num);
  static void check_3c(const bool has_win_page, const bool has_lose_page);

 public:
  Book() {}
  explicit Book(const std::string d) { load_book(d); }
  Book(const std::string d, const std::string fn) { load_book(d, fn); }
  ~Book() {}

  const Book & print_book() const;
  Book & load_book(const std::string directory, const std::string fname = "story.txt");
  const Book & check() const;
  const Page & operator[](size_t page_num) const;

  const Book & print_all_win_ways() const;  //DFS
};

#endif
/*--------------------------------  EOF  ------------------------------------*/
