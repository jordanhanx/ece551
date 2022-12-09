//===========================  my_str_tools.hpp  ============================//
#ifndef __MY_TOOLS_HPP__
#define __MY_TOOLS_HPP__

#include <cstdlib>
#include <sstream>
#include <string>
/*****************************************************************************
 * function: my_stost()   //convert the input string to size_t               *
 * @param: number        // input string                                     *
 * @return: size_t                                                           *
 *****************************************************************************/
size_t my_stost(const std::string & number);

/*****************************************************************************
 * function: my_stol()      // convert the input string to long int          *
 * @param: number           // input string                                  *
 * @return: long int                                                         *
 *****************************************************************************/
long int my_stol(const std::string & number);

/*****************************************************************************
 * function template: x2str() // convert everthing to a string               *
 * @typename: T                                                              *
 * @param: x                  // need overloaded "stream << x"               *
 * @return: string                                                           *
 *****************************************************************************/
template<typename T>
std::string x2str(T x) {
  std::stringstream ss;
  ss << x;
  return ss.str();
}

#endif
//================================  EOF  ====================================//
