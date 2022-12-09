/*------------------------------  path.cpp  ---------------------------------*/
#include "path.hpp"

#include "my_str_tools.hpp"
/*****************************************************************************
 * method: Path's default constructor                                        *
 *****************************************************************************/
Path::Path() : last_page_num(0) {
  path += x2str<size_t>(0);
  visited_page_set.insert(0);
}

/*****************************************************************************
 * method: Path's constructor                                                *
 *****************************************************************************/
Path::Path(size_t n) : last_page_num(n) {
  path += x2str<size_t>(n);
  visited_page_set.insert(n);
}

/*****************************************************************************
 * method: Path::extend()     // extend the path with option and page num    *
 * @param: option             // size_t, the index of choice                 *
 * @param: page_num           // size_t, destination page number             *
 * @return: reference                                                        *
 *****************************************************************************/
Path & Path::extend(size_t option, size_t page_num) {
  path += "(" + x2str<size_t>(option) + ")," + x2str<size_t>(page_num);
  visited_page_set.insert(page_num);
  last_page_num = page_num;
  return *this;
}

/*****************************************************************************
 * method: Path::contain()      // whether page number belongs to this path  *
 * @param: page_num             // size_t, page number                       *
 * @return: bool                                                             *
 *****************************************************************************/
bool Path::contain(const size_t page_num) const {
  if (visited_page_set.find(page_num) == visited_page_set.end()) {
    return false;
  }
  else {
    return true;
  }
}

/*****************************************************************************
 * method: Path()::get_path()    // return the string of path                *
 * @return: reference                                                        *
 *****************************************************************************/
const std::string & Path::get_path() const {
  return path;
}

/*****************************************************************************
 * method: Path::get_num()      // return the last page's number             *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t Path::get_num() const {
  return last_page_num;
}

/*--------------------------------  EOF  ------------------------------------*/
