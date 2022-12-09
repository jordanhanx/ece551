/*------------------------------  book.cpp  ---------------------------------*/
#include "book.hpp"

#include "my_str_tools.hpp"

/*****************************************************************************
 * method: Book::print_book()   // print whole book correctly                *
 * @return: reference                                                        *
 *****************************************************************************/
const Book & Book::print_book() const {
  try {
    for (size_t i = 0; i < pages.size(); ++i) {
      std::cout << "Page " << i << "\n";
      std::cout << "==========\n";
      pages[i].print_page();
    }
    return *this;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************
 * method: Book::[]       // return a const reference to the specific page   *
 * @return: reference                                                        *
 *****************************************************************************/
const Page & Book::operator[](size_t page_num) const {
  try {
    return pages[page_num];
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************
 * method: Book::load_book() // load book's everything from the directory    *
 * @param: directory         // the input directory                          *
 * @param: fname             // the "boot" file's name, default is story.txt *
 * @return: reference                                                        *
 *****************************************************************************/
Book & Book::load_book(const std::string directory, const std::string fname) {
  try {
    std::ifstream ifs((directory + "/" + fname).c_str());
    if (!ifs) {
      std::cerr << "load_book(): " << directory + "/" + fname << " is not found\n";
      exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(ifs, line)) {
      parse_line(line, directory);
    }
    ifs.close();
    return *this;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************
 * method: Book::parse_line()  // parse a line of a story.txt                *
 * @param: line                // string to be parsed                        *
 * @param: directory           // the input directory                        *
 * @return: void                                                             *
 *****************************************************************************/
void Book::parse_line(const std::string & line, const std::string & directory) {
  if (line.find_first_not_of(' ') == std::string::npos) {  // skip blank line
    return;
  }
  else if (parse_page(line, directory)) {
    return;
  }
  else if (parse_variable(line)) {
    return;
  }
  else if (parse_choice(line)) {
    return;
  }
  else if (parse_key_choice(line)) {
    return;
  }
  else {
    throw std::domain_error("pase_line(): illegal line: " + line);
  }
}

/*****************************************************************************
 * method: Book::parse_page()  // try to parse a page declaration from a line*
 * @param: line                // string to be parsed                        *
 * @param: directory           // the input directory                        *
 * @return: bool               // indicate whether line isparsed successfully*
 *****************************************************************************/
bool Book::parse_page(const std::string & line, const std::string & directory) {
  try {
    size_t pos_at = line.find('@');
    size_t pos_colon = line.find(':');
    size_t page_num = my_stost(line.substr(0, pos_at));
    // Page declaration must appear in order
    if (page_num != pages.size()) {
      throw std::domain_error("page_num != pages.size()");
    }
    std::string type(line.substr(pos_at + 1, pos_colon - pos_at - 1));
    std::string file_path(directory + "/" + line.substr(pos_colon + 1));
    pages.append_page(type, file_path);
    return true;
  }
  catch (const std::exception & e) {
    return false;
  }
}

/*****************************************************************************
 * method: Book::parse_variable() // try to parse a key setting from a line  *
 * @param: line                // string to be parsed                        *
 * @return: bool               // indicate whether line isparsed successfully*
 *****************************************************************************/
bool Book::parse_variable(const std::string & line) {
  try {
    size_t pos_dollar = line.find('$');
    size_t pos_eq = line.find('=');
    size_t page_num = my_stost(line.substr(0, pos_dollar));
    std::string key(line.substr(pos_dollar + 1, pos_eq - pos_dollar - 1));
    long int value = my_stol(line.substr(pos_eq + 1));
    pages[page_num].append_kv(key, value);
    return true;
  }
  catch (const std::exception & e) {
    return false;
  }
}

/*****************************************************************************
 * method: Book::parse_choice()// try to parse a choice adding from a line   *
 * @param: line                // string to be parsed                        *
 * @return: bool               // indicate whether line isparsed successfully*
 *****************************************************************************/
bool Book::parse_choice(const std::string & line) {
  try {
    size_t pos_colon1 = line.find(':');
    size_t pos_colon2 = line.find(':', pos_colon1 + 1);
    size_t page_num = my_stost(line.substr(0, pos_colon1));
    size_t dest_num = my_stost(line.substr(pos_colon1 + 1, pos_colon2 - pos_colon1 - 1));
    std::string text(line.substr(pos_colon2 + 1));
    pages[page_num].add_choice(dest_num, text);
    return true;
  }
  catch (const std::exception & e) {
    return false;
  }
}

/*****************************************************************************
 * method: Book::parse_key_choice() // try to parse a special choice adding  *
 * @param: line                // string to be parsed                        *
 * @return: bool               // indicate whether line isparsed successfully*
 *****************************************************************************/
bool Book::parse_key_choice(const std::string & line) {
  try {
    size_t pos_colon1 = line.find(':');
    size_t pos_colon2 = line.find(':', pos_colon1 + 1);
    size_t pos_eq = line.find('=');
    size_t pos_open_brkt = line.find('[');
    size_t pos_clos_brkt = line.find(']');
    // The second colon must immediately follow the closing bracket
    if (pos_colon1 - pos_clos_brkt != 1) {
      throw std::domain_error("pos_colon1 - pos_clos_brkt != 1");
    }
    size_t page_num = my_stost(line.substr(0, pos_open_brkt));
    std::string key(line.substr(pos_open_brkt + 1, pos_eq - pos_open_brkt - 1));
    long int value = my_stol(line.substr(pos_eq + 1, pos_clos_brkt - pos_eq - 1));
    size_t dest_num = my_stost(line.substr(pos_colon1 + 1, pos_colon2 - pos_colon1 - 1));
    std::string text(line.substr(pos_colon2 + 1));
    pages[page_num].add_key_choice(dest_num, text, key, value);
    return true;
  }
  catch (const std::exception & e) {
    return false;
  }
}

/*****************************************************************************
 * method: Book::check()       // check whether book complys with all rules  *
 * @return: reference                                                        *
 *****************************************************************************/
const Book & Book::check() const {
  try {
    bool has_win_page = false;
    bool has_lose_page = false;
    // Set: store all referenced page numbers
    std::set<size_t> dest_num_set;
    // iterate each page
    for (size_t i = 0; i < pages.size(); ++i) {
      if (!pages[i].is_final()) {
        // iterate each choice
        for (size_t j = 0; j < pages[i].choices().size(); ++j) {
          // Book is friend class of Choice, so dest_num can be accessed directly here
          if (i != pages[i].choices()[j].dest_num) {
            // insert dest_num into Set only if dest_num != page_num
            dest_num_set.insert(pages[i].choices()[j].dest_num);
          }
        }
      }
    }
    dest_num_set.erase(0);  // page 0 do not need to comply with rule_3b
    // iterate each page (except page 0)
    for (size_t i = 1; i < pages.size(); ++i) {
      // check if the file can be opened
      pages[i].verify_file_path();
      /**********************************************************************
       * check rule_3b: Every page (except page 0) is referenced            *
       *                by at least one *other* page's choices.             *
       **********************************************************************/
      check_3b(dest_num_set, i);
      // if pass rule_3b, remove the page number
      dest_num_set.erase(i);
      // if has any win page, set has_win_page to true
      has_win_page = has_win_page || (pages[i].is_final() && pages[i].is_won());
      // if has any lose page, set has_lose_page to true
      has_lose_page = has_lose_page || (pages[i].is_final() && !pages[i].is_won());
    }
    /**********************************************************************
     * check rule_3a: Every page that is referenced by a choice is valid. *
     **********************************************************************/
    check_3a(dest_num_set);
    /**********************************************************************
     * check rule_3c: At least one page must be a WIN page and at least   *
     *                one page must be a LOSE page.                       *
     **********************************************************************/
    check_3c(has_win_page, has_lose_page);
    return *this;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************
 * method: Book::check_3a()  // Every page referenced by a choice is valid.  *
 * @param: pages_set         // a set of referenced page numbers             *
 * @return: void                                                             *
 *****************************************************************************/
void Book::check_3a(const std::set<size_t> & pages_set) {
  // if pass 3a, the set should be empty
  if (!pages_set.empty()) {
    std::string msg("check_3a(): referenced Pages ( ");
    std::set<size_t>::const_iterator it = pages_set.begin();
    while (it != pages_set.end()) {
      msg += x2str<size_t>(*it) + ",";
      ++it;
    }
    throw std::domain_error(msg + " ) are invalid");
  }
}

/*****************************************************************************
 * method: Book::check_3b()  // Every page (except page 0) is referenced by  *
 *                              at least one *other* page's choices.         *
 * @param: pages_set         // a set of referenced page numbers             *
 * @param: page_num          // the page number to be checked                *
 * @return: void                                                             *
 *****************************************************************************/
void Book::check_3b(const std::set<size_t> & pages_set, size_t page_num) {
  if (pages_set.find(page_num) == pages_set.end()) {
    throw std::domain_error("check_3b(): Page(" + x2str<size_t>(page_num) +
                            ") has not been referenced by other page");
  }
}

/*****************************************************************************
 * method: Book::check_3c()  // At least one page must be a WIN page and at  *
 *                              least one page must be a LOSE page.          *
 * @param: has_win_page      // bool                                         *
 * @param: has_win_page      // bool                                         *
 *****************************************************************************/
void Book::check_3c(const bool has_win_page, const bool has_lose_page) {
  if (!(has_win_page && has_lose_page)) {
    std::string msg("check_3c(): ");
    if (!has_win_page) {
      msg += "no win page ";
    }
    if (!has_lose_page) {
      msg += "no lose Page ";
    }
    throw std::domain_error(msg);
  }
}

/*****************************************************************************
 * method: Book::print_all_win_ways() // use DFS to print all ways to win    *
 * @return: reference                                                        *
 * This DFS algorithm comes from:                                            *
 *    Andrew Hilton and Anne Bracy,<<All of Programming>>,2015(page#479)     *
 *    https://play.google.com/store/books/details/Andrew_Hilton_All_of_Progra*
 *    mming?id=-zViCgAAQBAJ                                                  *
 *****************************************************************************/
const Book & Book::print_all_win_ways() const {
  try {
    std::stack<Path> todo;  // use a Stack to store readingPath(path_obj)
    todo.push(Path(0));     // push start into the Stack
    bool has_win_way = false;

    while (!todo.empty()) {  // repreat until Stack is empty
      Path path_obj(todo.top());
      todo.pop();  // pop the top path_obj in Stack
      size_t page_num = path_obj.get_num();
      if (pages[page_num].is_won()) {
        std::cout << path_obj.get_path() << "(win)\n";  // print the path string
        has_win_way = true;                             // set flag to true
      }

      else if (!pages[page_num].is_final()) {  // search new path from choices
        std::set<size_t> dest_set;             // use a local Set to memorize destinations
        for (size_t opt = 1; opt <= pages[page_num].choices().size(); ++opt) {
          size_t dest_num =
              pages[page_num].choices()[opt - 1].dest_num;    // get destination
          if ((!path_obj.contain(dest_num)) &&                // avoid loop in path
              (dest_set.find(dest_num) == dest_set.end())) {  // avoid same dest_num
            todo.push(Path(path_obj).extend(opt, dest_num));  // push new path into Stack
            dest_set.insert(dest_num);  // insert destination into local Set
          }
        }
      }
    }

    if (!has_win_way) {
      std::cout << "This story is unwinnable!\n";  // if there is no way to win
    }
    return *this;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
}

/*--------------------------------  EOF  ------------------------------------*/
