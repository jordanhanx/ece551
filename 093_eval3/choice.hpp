/*------------------------------  choice.hpp  -------------------------------*/
#ifndef __CHOICE_HPP__
#define __CHOICE_HPP__

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "key.hpp"

/*****************************************************************************
 * Class: Choice          // represent choice at the end of story's page     *
 * @field: dest_num       // the number of destination page                  *
 * @field: text           // the description of the choice                   *
 * @method: duplicate()   // return the address of a deep copy of self       *
 * @method: get_dest()    // return destination page's number                *
 * @method: get_text()    // return the description                          *
 *****************************************************************************/
class Choice {
  friend class
      Book;  // Book need access dest_num directly in check() & print_all_win_ways()

 protected:  // child class need access following fields
  const size_t dest_num;
  const std::string text;

 public:
  Choice() : dest_num(-1), text("default choice") {}
  Choice(size_t n, const std::string & t) : dest_num(n), text(t) {}
  virtual ~Choice() {}

  virtual Choice * duplicate();
  virtual size_t get_dest(const kvMap & kvs = kvMap()) const;
  virtual std::string get_text(const kvMap & kvs = kvMap()) const;
};

/*****************************************************************************
 * Class: keyChoice      // special choice including a pair of key&value     *
 * @field: dest_num      // (inherited from Class Choice)                    *
 * @field: text          // (inherited from Class Choice)                    *
 * @field: kv_pair       // a pair of key&value                              *
 * @method: duplicate()  // (inherited from Class Choice, but overrided here)*
 * @method: get_dest()   // (inherited from Class Choice, but overrided here)*
 * @method: get_text()   // (inherited from Class Choice, but overrided here)*
 *****************************************************************************/
class keyChoice : public Choice {
  const kvPair kv_pair;

 public:
  keyChoice() {}
  keyChoice(size_t n, const std::string & t, const kvPair & kv) :
      Choice(n, t), kv_pair(kv) {}
  virtual ~keyChoice() {}

  virtual Choice * duplicate();
  virtual size_t get_dest(const kvMap & kvs = kvMap()) const;
  virtual std::string get_text(const kvMap & kvs = kvMap()) const;
};

/*****************************************************************************
 * Class: choiceList      // list of choices                                 *
 * @field: choice_vector  // a STL vector containing pointers to choices     *
 * @method: append_choice()       // add a normal choice into the list       *
 * @method: append_key_choice()   // add a special choice into the list      *
 * @method: size()        // calculate how many choices in the list          *      
 * @method: []            // return a reference to the specific choice       *
 *****************************************************************************/
class choiceList {
  std::vector<Choice *> choice_vector;

 public:
  choiceList() {}
  choiceList(const choiceList & rhs);
  choiceList & operator=(const choiceList & rhs);
  ~choiceList();

  choiceList & append_choice(size_t dest_num, const std::string & text);
  choiceList & append_key_choice(size_t dest_num,
                                 const std::string & text,
                                 const kvPair & kv);
  size_t size() const;
  const Choice & operator[](size_t idx) const;
};

#endif
/*--------------------------------  EOF  ------------------------------------*/
