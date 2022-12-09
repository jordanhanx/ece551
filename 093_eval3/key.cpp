/*------------------------------  key.cpp  ----------------------------------*/
#include "key.hpp"

/*****************************************************************************
 * method: kvList::append()  // add a key-value pair into the object         *
 * @param: k                 // a const reference to a string                *
 * @param: v                 // a long int                                   *
 * @return: reference                                                        *
 *****************************************************************************/
kvList & kvList::append(const std::string & k, long int v) {
  kv_vector.push_back(kvPair(k, v));
  return *this;
}

/*****************************************************************************
 * method: kvList::size()  // calculate how many pairs in the object         *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t kvList::size() const {
  return kv_vector.size();
}

/*****************************************************************************
 * method: kvList::[]   // return a const reference to the key-value pair    *
 * @param: idx          // a size_t type index                               * 
 * @return: const reference                                                  *
 *****************************************************************************/
const kvPair & kvList::operator[](size_t idx) const {
  if (idx >= 0 && idx < kv_vector.size()) {
    return kv_vector[idx];
  }
  else {
    throw std::invalid_argument("kvs[]: out of range");
  }
}

/*****************************************************************************
 * method: kvMap::insert() // add a value to a specific key                  *
 * @param: k               // a const reference to a string                  *
 * @param: v               // a long int                                     *
 * @return: reference                                                        *
 *****************************************************************************/
kvMap & kvMap::insert(const std::string & k, long int v) {
  kv_map[k] = v;
  return *this;
}

/*****************************************************************************
 * method: kvMap::clear()  // Removes all elements from the map              *
 * @return: reference                                                        *
 *****************************************************************************/
kvMap & kvMap::clear() {
  kv_map.clear();
  return *this;
}

/*****************************************************************************
 * method: kvMap::[]   // lookup value by key                                *
 * @param: k           // a const reference to a string                      *
 * @return: long int                                                         *
 *****************************************************************************/
long int kvMap::operator[](const std::string & k) const {
  // If your story encounters a variable which has not been set
  // it should treat it as having a value of 0.
  if (kv_map.find(k) == kv_map.end()) {
    return 0;
  }
  else {
    return kv_map.find(k)->second;
  }
}

/*****************************************************************************
 * method: kvMap::insert_from__kvList() // insert all kv pairs from a kvList *
 * @param: kv_list                                                           *
 * @return: reference                                                        *
 *****************************************************************************/
kvMap & kvMap::insert_from_kvList(const kvList & kv_list) {
  for (size_t i = 0; i < kv_list.size(); ++i) {
    insert(kv_list[i].key, kv_list[i].value);
  }
  return *this;
}

/*--------------------------------  EOF  ------------------------------------*/
