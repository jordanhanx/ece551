/*------------------------------  path.hpp  ---------------------------------*/
#ifndef __PATH_HPP__
#define __PATH_HPP__

#include <cstdlib>
#include <set>
#include <string>

#include "key.hpp"
/*****************************************************************************
 * Class: Path            // represent the path in a story book              *
 * @field: visited_set    // set of numbers of all visited pages             *
 * @field: path           // the string of path so far                       *
 * @field: last_page_num  // the last page's number in current path          * 
 * @method: extend()      // extend the path with option and page number     *
 * @method: get_path()    // return the string of path                       *
 * @method: contain()     // check whether page number belongs to this path  *
 * @method: get_num()     // return the last page's number                   *
 *****************************************************************************/
class Path {
  std::set<size_t> visited_page_set;
  std::string path;
  size_t last_page_num;

 public:
  Path();
  Path(size_t n);
  ~Path() {}

  Path & extend(size_t option, size_t page_num);
  bool contain(size_t page_num) const;
  const std::string & get_path() const;
  size_t get_num() const;
};

#endif
/*--------------------------------  EOF  ------------------------------------*/
