#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
#include <algorithm>

class Tester;

class invalid_index : public std::exception {
 public:
  const char * error_msg;
  invalid_index(const char * msg) : error_msg(msg) {}
  virtual const char * what() const throw() { return error_msg; }
};

template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(), next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
    Node * const * ptr = &(rhs.head);
    while ((*ptr) != NULL) {
      addBack((*ptr)->data);
      ptr = &(*ptr)->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp_lst(rhs);
      //std::swap<LinkedList>(*this, temp_lst); // broken:Stack Overflow...
      std::swap<Node *>(this->head, temp_lst.head);
      std::swap<Node *>(this->tail, temp_lst.tail);
    }
    return *this;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
  }

  bool remove(const T & item) {
    bool ans = false;
    Node ** ptr = &head;
    while (*ptr != NULL) {
      if ((*ptr)->data == item) {
        break;
      }
      else {
        ptr = &(*ptr)->next;
      }
    }
    if (*ptr != NULL) {
      Node * temp = *ptr;
      if (temp->prev == NULL) {
        head = temp->next;
      }
      else {
        temp->prev->next = temp->next;
      }
      if (temp->next == NULL) {
        tail = temp->prev;
      }
      else {
        temp->next->prev = temp->prev;
      }
      delete temp;
      ans = true;
    }
    return ans;
  }

  T & operator[](int index) {
    if (index < 0) {
      throw invalid_index("invalid index!");
    }
    Node ** ptr = &head;
    int i = 0;
    while (*ptr != NULL) {
      if (i == index) {
        return (*ptr)->data;
      }
      else {
        ptr = &(*ptr)->next;
        ++i;
      }
    }
    throw invalid_index("invalid index!");
  }

  const T & operator[](int index) const {
    if (index < 0) {
      throw invalid_index("invalid index!");
    }
    Node * const * ptr = &head;
    int i = 0;
    while (*ptr != NULL) {
      if (i == index) {
        return (*ptr)->data;
      }
      else {
        ptr = &(*ptr)->next;
        ++i;
      }
    }
    throw invalid_index("invalid index!");
  }

  int find(const T & item) {
    Node ** ptr = &head;
    int i = 0;
    while (*ptr != NULL) {
      if ((*ptr)->data == item) {
        return i;
      }
      else {
        ptr = &(*ptr)->next;
        ++i;
      }
    }
    return -1;
  }

  int getSize() const {
    Node * const * ptr = &head;
    int i = 0;
    while (*ptr != NULL) {
      ptr = &(*ptr)->next;
      ++i;
    }
    return i;
  }

  friend class Tester;
};

#endif
