/*------------------------------  choice.cpp  -------------------------------*/
#include "choice.hpp"

/*****************************************************************************
 * method: Choice::duplicate()  // allocate new memory, do deep copy of self *
 * @return: pointer             // the address of the new object             *
 *****************************************************************************/
Choice * Choice::duplicate() {
  return new Choice(*this);
}

/*****************************************************************************
 * method: Choice::get_dest()  // return destination page's number directly  *
 * @param: kvs                 // a kvMap, ignored here                      *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t Choice::get_dest(const kvMap & kvs) const {
  return dest_num;
}

/*****************************************************************************
 * method: Choice::get_text()  // return the choice's description            *
 * @param: kvs                 // a kvMap, ignored here                      *
 * @return: string                                                           *
 *****************************************************************************/
std::string Choice::get_text(const kvMap & kvs) const {
  return text;
}

/*****************************************************************************
 * method: keyChoice::duplicate()// allocate new memory, do deep copy of self*
 * @return: pointer              // the address of the new object            *
 *****************************************************************************/
Choice * keyChoice::duplicate() {
  return new keyChoice(*this);
}

/*****************************************************************************
 * method: keyChoice::get_dest()// return destination page's number directly *
 * @param: kvs                  // a kvMap to lookup                         *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t keyChoice::get_dest(const kvMap & kvs) const {
  if (kvs[kv_pair.key] == kv_pair.value) {
    return dest_num;
  }
  else {
    throw key_value_mismatch(
        "That choice is not available at this time, please try again");
  }
}

/*****************************************************************************
 * method: keyChoice::get_text() // return the choice's description          *
 * @param: kvs                   // a kvMap to lookup                        *
 * @return: string                                                           *
 *****************************************************************************/
std::string keyChoice::get_text(const kvMap & kvs) const {
  if (kvs[kv_pair.key] == kv_pair.value) {
    return text;
  }
  else {
    return "<UNAVAILABLE>";
  }
}

/*****************************************************************************
 * method: choiceList's copy constructor                                     *
 *****************************************************************************/
choiceList::choiceList(const choiceList & rhs) {
  std::vector<Choice *>::const_iterator it = rhs.choice_vector.begin();
  while (it != rhs.choice_vector.end()) {
    choice_vector.push_back((*it)->duplicate());
    ++it;
  }
}

/*****************************************************************************
 * method: choiceList's copy assignment                                      *
 *****************************************************************************/
choiceList & choiceList::operator=(const choiceList & rhs) {
  if (this != &rhs) {
    choiceList temp(rhs);
    std::swap(choice_vector, temp.choice_vector);
  }
  return *this;
}

/*****************************************************************************
 * method: choicelist's destructor                                           *
 *****************************************************************************/
choiceList::~choiceList() {
  std::vector<Choice *>::iterator it = choice_vector.begin();
  while (it != choice_vector.end()) {
    delete *it;
    ++it;
  }
}

/*****************************************************************************
 * method: choiceList::append_choice()  // add a normal choice into the list *
 * @param: dest_num                     // page's number of the destination  *
 * @param: text                         // choice's description              *
 * @return: reference                                                        *
 *****************************************************************************/
choiceList & choiceList::append_choice(size_t dest_num, const std::string & text) {
  choice_vector.push_back(new Choice(dest_num, text));
  return *this;
}

/*****************************************************************************
 * method: choiceList::append_key_choice()//add a spcial choice into the list*
 * @param: dest_num          // page's number of the destination             *
 * @param: text              // choice's description                         *
 * @param: k                 // a const reference to a string                *
 * @param: v                 // a long int                                   *
 * @return: reference                                                        *
 *****************************************************************************/
choiceList & choiceList::append_key_choice(size_t dest_num,
                                           const std::string & text,
                                           const kvPair & kv) {
  choice_vector.push_back(new keyChoice(dest_num, text, kv));
  return *this;
}

/*****************************************************************************
 * method: choiceList::size()  // calculate how many choices in the list     *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t choiceList::size() const {
  return choice_vector.size();
}

/*****************************************************************************
 * method: choiceList::[]  // return a const reference to the specific choice*
 * @param: idx             // a size_t type index                            * 
 * @return: const reference                                                  *
 *****************************************************************************/
const Choice & choiceList::operator[](size_t idx) const {
  if (idx >= 0 && idx < choice_vector.size()) {
    return *choice_vector[idx];
  }
  else {
    throw std::invalid_argument("choices[]: out of range");
  }
}

/*--------------------------------  EOF  ------------------------------------*/
