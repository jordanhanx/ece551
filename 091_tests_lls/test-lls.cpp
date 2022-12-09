#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList lst;
    lst.addFront(2);
    lst.addFront(1);
    assert(lst[0] == 1);
    assert(lst[1] == 2);
    assert(lst.head->prev == NULL);
    assert(lst.tail->next == NULL);
    assert(lst.head->next->next == NULL);
    assert(lst.tail->prev->prev == NULL);
  }
  // many more tester methods

  void testAddBack() {
    IntList lst;
    lst.addBack(1);
    lst.addBack(2);
    assert(lst[0] == 1);
    assert(lst[1] == 2);
    assert(lst.head->prev == NULL);
    assert(lst.tail->next == NULL);
    assert(lst.head->next->next == NULL);
    assert(lst.tail->prev->prev == NULL);
  }

  void testRo3() {
    IntList lst1;
    lst1.addBack(16);
    lst1.addBack(55);
    IntList lst2(lst1);
    lst2.addBack(11);
    lst2.addFront(1);
    lst1 = lst2;
    assert(lst1[0] == 1);
    assert(lst1[1] == 16);
    assert(lst1[2] == 55);
    assert(lst1[3] == 11);
  }

  void testRemove() {
    IntList lst;
    assert(lst.remove(0) == false);
    lst.addBack(0);
    assert(lst.remove(0) == true);
    assert(lst.head == NULL);
    assert(lst.tail == NULL);
    IntList lst1;
    lst1.addBack(1);
    lst1.addBack(2);
    lst1.addBack(1);
    lst1.addBack(3);
    IntList lst2(lst1);
    IntList lst3(lst1);
    IntList lst4(lst1);
    assert(lst1.remove(1) == true);
    assert(lst2.remove(2) == true);
    assert(lst3.remove(3) == true);
    assert(lst4.remove(4) == false);
    assert(lst1[0] == 2);
    assert(lst1[1] == 1);
    assert(lst1[2] == 3);
    assert(lst2[0] == 1);
    assert(lst2[1] == 1);
    assert(lst2[2] == 3);
    assert(lst3[0] == 1);
    assert(lst3[1] == 2);
    assert(lst3[2] == 1);
    assert(lst4[0] == 1);
    assert(lst4[1] == 2);
    assert(lst4[2] == 1);
    assert(lst4[3] == 3);
    assert(lst1.head->prev == NULL);
    assert(lst1.tail->next == NULL);
    assert(lst1.head->next->next == lst1.tail);
    assert(lst1.tail->prev->prev == lst1.head);
    assert(lst2.head->prev == NULL);
    assert(lst2.tail->next == NULL);
    assert(lst2.head->next->next == lst2.tail);
    assert(lst2.tail->prev->prev == lst2.head);
    assert(lst3.head->prev == NULL);
    assert(lst3.tail->next == NULL);
    assert(lst3.head->next->next == lst3.tail);
    assert(lst3.tail->prev->prev == lst3.head);
    assert(lst4.head->prev == NULL);
    assert(lst4.tail->next == NULL);
    assert(lst4.head->next->next->next == lst4.tail);
    assert(lst4.tail->prev->prev->prev == lst4.head);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testRo3();
  t.testRemove();
  return EXIT_SUCCESS;
}
