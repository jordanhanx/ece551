/*------------------------------  key.hpp  ----------------------------------*/
#ifndef __KEY_HPP__
#define __KEY_HPP__

#include <cstdlib>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

/*****************************************************************************
 * Class: key_value_mismatch                                                 *
 * @field: error_msg                                                         *
 * @method: what()                                                           *
 *****************************************************************************/
class key_value_mismatch : public std::exception {
  const char * error_msg;

 public:
  explicit key_value_mismatch(const char * msg) : error_msg(msg) {}
  virtual const char * what() const throw() { return error_msg; }
};

/*****************************************************************************
 * Class: kvPair     // store a pair of key and value                        *
 * @field: key       // a string type key                                    *
 * @field: value     // a long int type value                                *
 *****************************************************************************/
class kvPair {
 public:
  const std::string key;
  const long int value;

  kvPair() : value(-1) {}
  kvPair(const std::string & k, long int v) : key(k), value(v) {}
  ~kvPair() {}
};

/*****************************************************************************
 * Class: kvList       // store a list of key-value pairs                    *
 * @field: kv_vector   // a STL vector                                       *
 * @method: append()   // add a key-value pair into the object               *
 * @method: size()     // calculate how many pairs in the object             *
 * @method: []         // return a reference to the key-value pair           *
 *****************************************************************************/
class kvList {
  std::vector<kvPair> kv_vector;

 public:
  kvList() {}
  ~kvList() {}

  kvList & append(const std::string & k, long int v);
  size_t size() const;
  const kvPair & operator[](size_t idx) const;
};

/*****************************************************************************
 * Class: kvMap      // a lookup table to memorize value for each key        *
 * @field: kv_map    // a STL map                                            *
 * @method: insert() // add a value to a specific key                        *
 * @method: insert_from_kvList()  // add keys&values from kvList             *
 * @method: clear()  // Removes all elements from the map                    *
 * @method: []       // lookup value by key                                  *
 *****************************************************************************/
class kvMap {
  std::map<std::string, long int> kv_map;

 public:
  kvMap() {}
  ~kvMap() {}
  kvMap & insert(const std::string & k, long int v);
  kvMap & insert_from_kvList(const kvList & kvs);
  kvMap & clear();
  long int operator[](const std::string & k) const;
};

#endif
/*--------------------------------  EOF  ------------------------------------*/
