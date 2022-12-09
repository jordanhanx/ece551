/*------------------------------  page.hpp  ---------------------------------*/
#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "choice.hpp"
#include "key.hpp"

/*****************************************************************************
 * Class: Page        // represent a page of a story, abstract class         *
 * @field: file_path  // path of file which stores the text of this page     *
 * @field: kv_list    // list of key-value pairs in this page                *
 * @method: verify_file_path() // check whether the file can be opened       *
 * @method: append_kv()        // add a key-value pair into the kv_list      *
 * @method: kvs()              // return const reference to the kv_list      *
 * @method: print_page()       // print the whole page, including choices    *
 * @method: duplicate()        // return the address of a deep copy of self  *
 * @method: is_final()         // return whether this page is a final        *
 * @method: is_won()           // return whether this page is a win page     *
 * @method: add_choice()       // add a choice into this page's choice list  *
 * @method: add_key_choice()   // add a special choice into page choice list *
 * @method: choices()          // return const reference to the choice list  *
 *****************************************************************************/
class Page {
  const std::string file_path;
  kvList kv_list;

 public:
  Page() {}
  explicit Page(const std::string & fp) : file_path(fp) {}
  virtual ~Page() {}

  const Page & verify_file_path() const;
  Page & append_kv(const std::string & k, long int v);
  const kvList & kvs() const;

  virtual const Page & print_page(const kvMap & kvs = kvMap()) const;
  virtual Page * duplicate() const = 0;
  virtual bool is_final() const = 0;
  virtual bool is_won() const = 0;
  virtual Page & add_choice(size_t dest_num, const std::string & text) = 0;
  virtual Page & add_key_choice(size_t dest_num,
                                const std::string & text,
                                const std::string & k,
                                long int v) = 0;
  virtual const choiceList & choices() const = 0;
};

/*****************************************************************************
 * Class: normalPage  // represent a non-final page of a story               *
 * @field: file_path  // (inherited from Page)                               *
 * @field: kv_list    // (inherited from Page)                               *
 * @field: c_list     // list of choices                                     *
 * @method: verify_file_path() // (inherited from Page)                      *
 * @method: append_kv()        // (inherited from Page)                      *
 * @method: kvs()              // (inherited from Page)                      *
 * @method: print_page()       // (inherited from Page, but overrided here)  *
 * @method: duplicate()        // (inherited from Page, but overrided here)  *
 * @method: is_final()         // (inherited from Page, but overrided here)  *
 * @method: is_won()           // (inherited from Page, but overrided here)  *
 * @method: add_choice()       // (inherited from Page, but overrided here)  *
 * @method: add_key_choice()   // (inherited from Page, but overrided here)  *
 * @method: choices()          // (inherited from Page, but overrided here)  *
 *****************************************************************************/
class normalPage : public Page {
  choiceList c_list;

 public:
  normalPage() {}
  explicit normalPage(const std::string & fp) : Page(fp) {}
  virtual ~normalPage() {}

  virtual const normalPage & print_page(const kvMap & kvs = kvMap()) const;
  virtual normalPage * duplicate() const;
  virtual bool is_final() const;
  virtual bool is_won() const;
  virtual normalPage & add_choice(size_t dest_num, const std::string & text);
  virtual normalPage & add_key_choice(size_t dest_num,
                                      const std::string & text,
                                      const std::string & k,
                                      long int v);
  virtual const choiceList & choices() const;
};

/*****************************************************************************
 * Class: finalPage  // represent a final page of a story                    *
 * @field: file_path  // (inherited from Page)                               *
 * @field: kv_list    // (inherited from Page)                               *
 * @field: win_bit    // bool bit indicating whether this is win page        *
 * @method: verify_file_path() // (inherited from Page)                      *
 * @method: append_kv()        // (inherited from Page)                      *
 * @method: kvs()              // (inherited from Page)                      *
 * @method: print_page()       // (inherited from Page, but overrided here)  *
 * @method: duplicate()        // (inherited from Page, but overrided here)  *
 * @method: is_final()         // (inherited from Page, but overrided here)  *
 * @method: is_won()           // (inherited from Page, but overrided here)  *
 * @method: add_choice()       // (inherited from Page, but overrided here)  *
 * @method: add_key_choice()   // (inherited from Page, but overrided here)  *
 * @method: choices()          // (inherited from Page, but overrided here)  *
 *****************************************************************************/
class finalPage : public Page {
  const bool win_bit;

 public:
  finalPage() : win_bit(false) {}
  finalPage(const std::string & fp, bool w) : Page(fp), win_bit(w) {}
  virtual ~finalPage() {}

  virtual const finalPage & print_page(const kvMap & kvs = kvMap()) const;
  virtual finalPage * duplicate() const;
  virtual bool is_final() const;
  virtual bool is_won() const;
  virtual finalPage & add_choice(size_t dest_num, const std::string & text);
  virtual finalPage & add_key_choice(size_t dest_num,
                                     const std::string & text,
                                     const std::string & k,
                                     long int v);
  virtual const choiceList & choices() const;
};

/*****************************************************************************
 * Class: pageList        // list of pages                                   *
 * @field: page_vector    // a STL vector containing pointers to pages       *
 * @method: append_page() // add a page into the list                        *
 * @method: size()        // calculate how many pagess in the list           *      
 * @method: []            // return a reference to the specific page         *
 * @method: []            // return a const reference to the specific page   *
 *****************************************************************************/
class pageList {
  std::vector<Page *> page_vector;

 public:
  pageList() {}
  pageList(const pageList & rhs);
  pageList & operator=(const pageList & rhs);
  ~pageList();
  pageList & append_page(const std::string & type, const std::string & filename);
  size_t size() const;
  Page & operator[](size_t page_num);
  const Page & operator[](size_t page_num) const;
};
#endif
/*--------------------------------  EOF  ------------------------------------*/
