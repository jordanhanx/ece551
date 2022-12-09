/*------------------------------  reader.cpp  -------------------------------*/
#include "reader.hpp"

#include "my_str_tools.hpp"
/*****************************************************************************
 * method: Reader::open_book() // open a new book, initialize all fields     *
 * @param: bk                  // a const reference to a Book                *
 * @param: start_page          // default start page is page0                *
 * @return: reference                                                        *
 *****************************************************************************/
Reader & Reader::open_book(const Book & bk, size_t start_page) {
  try {
    book = &bk;
    page_num = start_page;
    bag.clear();
    return *this;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************
 * method: Reader::read_page() // print the page which reader has arrived at *
 * @return: reference                                                        *
 *****************************************************************************/
Reader & Reader::read_page() {
  try {
    bag.insert_from_kvList((*book)[page_num].kvs());  // update bag
    (*book)[page_num].print_page(bag);
    return *this;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************
 * method: Reader::goto_dest_page() // read user input, goto destination page*
 * @return: reference                                                        *
 *****************************************************************************/
Reader & Reader::goto_dest_page() {
  try {
    size_t dest_num = page_num;
    while (dest_num == page_num) {  // repeat until dest_num changed sucessfully
      dest_num = fetch_dest_page_num();
    }
    page_num = dest_num;  // jump to destination page
    return *this;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************
 * method: Reader::user_input()    // read a size_t from std::cin            *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t Reader::user_input() {
  std::string line;
  while (line.find_first_not_of(' ') == std::string::npos) {  // detect blank/empty line
    getline(std::cin, line);
  }
  return my_stost(line);
}

/*****************************************************************************
 * method: Reader::fetch_dest_page_num()//fetch des page num by user input   *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t Reader::fetch_dest_page_num() const {
  try {
    return (*book)[page_num].choices()[user_input() - 1].get_dest(bag);
  }
  // if exception, return current page num
  catch (const key_value_mismatch & e) {
    std::cout << "That choice is not available at this time, please try again\n";
    return page_num;
  }
  catch (const std::exception & e) {
    std::cout << "That is not a valid choice, please try again\n";
    return page_num;
  }
}

/*****************************************************************************
 * method: Reader::is_final()   // whether reader reaches a final page       * 
 * @return: bool                                                             *
 *****************************************************************************/
bool Reader::is_final() const {
  try {
    return (*book)[page_num].is_final();
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*--------------------------------  EOF  ------------------------------------*/
