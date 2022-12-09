/*------------------------------  page.cpp  ---------------------------------*/
#include "page.hpp"

/*****************************************************************************
 * method: Page::verify_file_path()  // check whether the file can be opened *
 * @return: reference                                                        *
 *****************************************************************************/
const Page & Page::verify_file_path() const {
  std::ifstream ifs(file_path.c_str());
  if (!ifs) {
    throw std::domain_error("Invalid path: " + file_path + " is not found");
  }
  ifs.close();
  return *this;
}

/*****************************************************************************
 * method: Page::append_kv()  // add a key-value pair into the kv_list       *
 * @param: k               // a const reference to a string                  *
 * @param: v               // a long int                                     *
 * @return: reference                                                        *
 *****************************************************************************/
Page & Page::append_kv(const std::string & k, long int v) {
  kv_list.append(k, v);
  return *this;
}

/*****************************************************************************
 * method: Page::kvs()   // return const reference to the kv_list            *
 * @return: reference                                                        *
 *****************************************************************************/
const kvList & Page::kvs() const {
  return kv_list;
}

/*****************************************************************************
 * method: Page::print_page() // read from the file_path,print the whole page*
 * @param: kvs                // a kvMap, ignored here                       *
 * @return: reference                                                        *
 *****************************************************************************/
const Page & Page::print_page(const kvMap & kvs) const {
  std::ifstream ifs(file_path.c_str());
  if (!ifs) {
    throw std::domain_error("Invalid path: " + file_path + " is not found");
  }
  //First, print the text of the page
  std::string line;
  while (std::getline(ifs, line)) {
    std::cout << line << "\n";
  }
  ifs.close();
  return *this;
}

/*****************************************************************************
 * method: normalPage::print_page()// print the whole page, including choices*
 * @param: kvs                     // a kvMap to lookup                      *
 * @return: reference                                                        *
 *****************************************************************************/
const normalPage & normalPage::print_page(const kvMap & kvs) const {
  Page::print_page();
  std::cout << "\nWhat would you like to do?\n\n";
  for (size_t i = 0; i < c_list.size(); ++i) {
    std::cout << " " << i + 1 << ". " << c_list[i].get_text(kvs) << "\n";
  }
  return *this;
}

/*****************************************************************************
 * method: normalPage::duplicate()//allocate new memory, do deep copy of self*
 * @return: pointer               // the address of the new object           *
 *****************************************************************************/
normalPage * normalPage::duplicate() const {
  return new normalPage(*this);
}

/*****************************************************************************
 * method: normalPage::is_final() // return whether this page is a final     *
 * @return: bool                                                             *
 *****************************************************************************/
bool normalPage::is_final() const {
  return false;
}

/*****************************************************************************
 * method: normalPage::is_won() // return whether this page is a win page    *
 * @return: bool                                                             *
 *****************************************************************************/
bool normalPage::is_won() const {
  return false;
}

/*****************************************************************************
 * method: normalPage::add_choice()//add a choice into page's choice list    *
 * @param: dest_num          // page's number of the destination             *
 * @param: text              // choice's description                         *
 * @return: reference                                                        *
 *****************************************************************************/
normalPage & normalPage::add_choice(size_t dest_num, const std::string & text) {
  c_list.append_choice(dest_num, text);
  return *this;
}

/*****************************************************************************
 * method: normalPage::add_key_choice()//add a special choice into list      *
 * @param: dest_num          // page's number of the destination             *
 * @param: text              // choice's description                         *
 * @param: k                 // a const reference to a string                *
 * @param: v                 // a long int                                   *
 * @return: reference                                                        *
 *****************************************************************************/
normalPage & normalPage::add_key_choice(size_t dest_num,
                                        const std::string & text,
                                        const std::string & k,
                                        long int v) {
  c_list.append_key_choice(dest_num, text, kvPair(k, v));
  return *this;
}

/*****************************************************************************
 * method: normalPage::choices() // return const reference to choices list   *
 * @return: reference                                                        *
 *****************************************************************************/
const choiceList & normalPage::choices() const {
  return c_list;
}

/*****************************************************************************
 * method: finalPage::print_page() // print the whole page, including final  *
 * @param: kvs                     // a kvMap, ignored here                  *
 * @return: reference                                                        *
 *****************************************************************************/
const finalPage & finalPage::print_page(const kvMap & kvs) const {
  Page::print_page();
  //Next, print a blank line.
  std::cout << "\n";
  //Then print either "Congratulations! You have won. Hooray!"
  if (win_bit) {
    std::cout << "Congratulations! You have won. Hooray!\n";
  }
  // or "Sorry, you have lost. Better luck next time!"
  else {
    std::cout << "Sorry, you have lost. Better luck next time!\n";
  }
  return *this;
}

/*****************************************************************************
 * method: finalPage::duplicate()//allocate new memory, do deep copy of self *
 * @return: pointer              // the address of the new object            *
 *****************************************************************************/
finalPage * finalPage::duplicate() const {
  return new finalPage(*this);
}

/*****************************************************************************
 * method: finalPage::is_final() // return whether this page is a final      *
 * @return: bool                                                             *
 *****************************************************************************/
bool finalPage::is_final() const {
  return true;
}

/*****************************************************************************
 * method: finalPage::is_won() // return whether this page is a win page    *
 * @return: bool                                                             *
 *****************************************************************************/
bool finalPage::is_won() const {
  return win_bit;
}

/*****************************************************************************
 * method: finalPage::add_choice() // add a choice into page's choice list   *
 * @param: dest_num          // page's number of the destination             *
 * @param: text              // choice's description                         *
 * @return: reference                                                        *
 *****************************************************************************/
finalPage & finalPage::add_choice(size_t dest_num, const std::string & text) {
  throw std::domain_error("add_choices(): cannot add choice to a final page!");
}

/*****************************************************************************
 * method: finalPage::add_key_choice()//add a special choice into choice list*
 * @param: dest_num          // page's number of the destination             *
 * @param: text              // choice's description                         *
 * @param: k                 // a const reference to a string                *
 * @param: v                 // a long int                                   *
 * @return: reference                                                        *
 *****************************************************************************/
finalPage & finalPage::add_key_choice(size_t dest_num,
                                      const std::string & text,
                                      const std::string & k,
                                      long int v) {
  throw std::domain_error("add_key_choices(): cannot add choice to a final page!");
}

/*****************************************************************************
 * method: finalPage::choices() // return const reference to choices list    *
 * @return: reference                                                        *
 *****************************************************************************/
const choiceList & finalPage::choices() const {
  throw std::domain_error("choices(): final page has no choice!");
}

/*****************************************************************************
 * method: pageList's copy constructor                                       *
 *****************************************************************************/
pageList::pageList(const pageList & rhs) {
  std::vector<Page *>::const_iterator it = rhs.page_vector.begin();
  while (it != rhs.page_vector.end()) {
    page_vector.push_back((*it)->duplicate());
    ++it;
  }
}

/*****************************************************************************
 * method: pageList's copy assignment                                        *
 *****************************************************************************/
pageList & pageList::operator=(const pageList & rhs) {
  if (this != &rhs) {
    pageList temp(rhs);
    std::swap(page_vector, temp.page_vector);
  }
  return *this;
}

/*****************************************************************************
 * method: pagelist's destructor                                             *
 *****************************************************************************/
pageList::~pageList() {
  std::vector<Page *>::iterator it = page_vector.begin();
  while (it != page_vector.end()) {
    delete *it;
    ++it;
  }
}

/*****************************************************************************
 * method: pageList::append_page()  // add a page into the list              *
 * @param: type                     // a const reference to a string         *
 * @param: filename                 // a const reference to a string         *
 * @return: reference                                                        *
 *****************************************************************************/
pageList & pageList::append_page(const std::string & type, const std::string & filename) {
  if ((type == "N")) {
    page_vector.push_back(new normalPage(filename));
  }
  else if (type == "W") {
    page_vector.push_back(new finalPage(filename, true));
  }
  else if (type == "L") {
    page_vector.push_back(new finalPage(filename, false));
  }
  else {
    throw std::domain_error("append_page(): illeagl page type: " + type);
  }
  return *this;
}

/*****************************************************************************
 * method: pageList::size()  // calculate how many pages in the list         *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t pageList::size() const {
  return page_vector.size();
}

/*****************************************************************************
 * method: pageList::[]    // return a reference to the specific page        *
 * @param: idx             // a size_t type index                            * 
 * @return: reference                                                        *
 *****************************************************************************/
Page & pageList::operator[](size_t page_num) {
  if (page_num >= 0 && page_num < page_vector.size()) {
    return *page_vector[page_num];
  }
  else {
    throw std::invalid_argument("pages[]: out of range");
  }
}

/*****************************************************************************
 * method: pageList::[]    // return a const reference to the specific page  *
 * @param: idx             // a size_t type index                            * 
 * @return: reference                                                        *
 *****************************************************************************/
const Page & pageList::operator[](size_t page_num) const {
  if (page_num >= 0 && page_num < page_vector.size()) {
    return *page_vector[page_num];
  }
  else {
    throw std::invalid_argument("pages[]: out of range");
  }
}

/*--------------------------------  EOF  ------------------------------------*/
