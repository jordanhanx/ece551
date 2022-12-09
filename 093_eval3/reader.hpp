/*------------------------------  reader.hpp  -------------------------------*/
#ifndef __READER_HPP__
#define __READER_HPP__

#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

#include "book.hpp"
#include "key.hpp"

/*****************************************************************************
 * Class: Reader            // represent a reader of the "cyoa" story book   *
 * @field: book             // a const pointer to the "cyoa" story Book      *
 * @field: page_num         // the page where the reader has arrived now     *
 * @field: bag              // the reader's bag storing keys and values      *
 * @method: user_input()    // read a size_t from std::cin                   *
 * @method: fetch_dest_page_num() //fetch destination page num by user input *
 * @method: open_book()     // open a new Book to read, initialize all fields*
 * @method: read_page()     // print current page                            *
 * @method: goto_dest_page()// read user input, goto destination page        *
 * @method: is_final()      // whether reader reaches a final page           *
 *****************************************************************************/
class Reader {
  const Book * book;
  size_t page_num;
  kvMap bag;

  static size_t user_input();
  size_t fetch_dest_page_num() const;

 public:
  Reader() : book(NULL), page_num(0) {}
  explicit Reader(const Book & bk, size_t st = 0) : book(&bk), page_num(st) {}
  ~Reader() {}

  Reader & open_book(const Book & bk, size_t start_page = 0);
  Reader & read_page();
  Reader & goto_dest_page();
  bool is_final() const;
};

#endif
/*--------------------------------  EOF  ------------------------------------*/
