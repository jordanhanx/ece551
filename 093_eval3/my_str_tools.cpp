//===========================  my_str_tools.cpp  ============================//
#include "my_str_tools.hpp"

/*****************************************************************************
 * function: my_stoull() //convert the input string to unsigned long long int*
 * @param: number        // input string                                     *
 * @return: unsigned long long int                                           *
 *****************************************************************************/
size_t my_stost(const std::string & number) {
  const char * s = number.c_str();
  char * end_ptr = NULL;
  size_t n = std::strtoull(s, &end_ptr, 10);
  if ((number.size() == 0) || (*end_ptr != '\0')) {
    throw std::invalid_argument("illegal number: " + number);
  }
  return n;
}

/*****************************************************************************
 * function: my_stol()      // convert the input string to long int          *
 * @param: number           // input string                                  *
 * @return: long int                                                         *
 *****************************************************************************/
long int my_stol(const std::string & number) {
  const char * s = number.c_str();
  char * end_ptr = NULL;
  long int n = std::strtol(s, &end_ptr, 10);
  if ((number.size() == 0) || (*end_ptr != '\0')) {
    throw std::invalid_argument("illegal number: " + number);
  }
  return n;
}

//================================  EOF  ====================================//
