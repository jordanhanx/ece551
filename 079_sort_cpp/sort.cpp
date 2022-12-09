#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void read_cin(std::vector<std::string> & str_arr) {
  std::string line;
  while (std::getline(std::cin, line)) {
    str_arr.push_back(line);
  }
}

void read_file(const char * filename, std::vector<std::string> & str_arr) {
  std::ifstream f(filename);
  if (!f.good()) {
    std::cerr << "Fail to open: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (std::getline(f, line)) {
    str_arr.push_back(line);
  }
  f.close();
}

class str_comp {
 public:
  bool operator()(std::string & s1, std::string & s2) {
    if (s1.compare(s2) < 0) {
      return true;
    }
    else {
      return false;
    }
  }
};

template<typename T>
void print_elements(const T & container) {
  typename T::const_iterator it = container.begin();
  while (it != container.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::vector<std::string> str_arr;
    read_cin(str_arr);
    std::sort(str_arr.begin(), str_arr.end(), str_comp());
    print_elements<std::vector<std::string> >(str_arr);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::vector<std::string> str_arr;
      read_file(argv[i], str_arr);
      std::sort(str_arr.begin(), str_arr.end(), str_comp());
      print_elements<std::vector<std::string> >(str_arr);
    }
  }

  return EXIT_SUCCESS;
}
