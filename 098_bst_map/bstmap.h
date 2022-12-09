#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <algorithm>
#include <cstdlib>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    K key;
    V val;
    Node * left;
    Node * right;
    Node() : key(), val(), left(NULL), right(NULL) {}
    Node(K k, V v, Node * le, Node * ri) : key(k), val(v), left(le), right(ri) {}
  };
  Node * root;

  void deepcopy_bst(const Node * current) {
    if (current != NULL) {
      add(current->key, current->val);
      deepcopy_bst(current->left);
      deepcopy_bst(current->right);
    }
  }
  void destroy_bst(Node * current) {
    if (current != NULL) {
      destroy_bst(current->left);
      destroy_bst(current->right);
      delete current;
    }
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { deepcopy_bst(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap temp_bst(rhs);
      std::swap<Node *>(root, temp_bst.root);
    }
    return *this;
  }
  ~BstMap() { destroy_bst(root); }

  virtual void add(const K & key, const V & value) {
    Node ** ptr = &root;
    while (*ptr != NULL) {
      if (key == (*ptr)->key) {
        (*ptr)->val = value;
        break;
      }
      else if (key < (*ptr)->key) {
        ptr = &(*ptr)->left;
      }
      else {
        ptr = &(*ptr)->right;
      }
    }
    if (*ptr == NULL) {
      *ptr = new Node(key, value, NULL, NULL);
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node const * node_ptr = root;
    while (node_ptr != NULL) {
      if (key == node_ptr->key) {
        return node_ptr->val;
      }
      else if (key < node_ptr->key) {
        node_ptr = node_ptr->left;
      }
      else {
        node_ptr = node_ptr->right;
      }
    }
    throw std::invalid_argument("invalid_argument: the key doesn't exist");
  }

  virtual void remove(const K & key) {
    Node ** ptr = &root;
    while ((*ptr) != NULL) {
      if (key == (*ptr)->key) {
        break;
      }
      else if (key < (*ptr)->key) {
        ptr = &(*ptr)->left;
      }
      else {
        ptr = &(*ptr)->right;
      }
    }
    if ((*ptr) != NULL) {
      Node * temp = *ptr;
      if (temp->left == NULL) {
        *ptr = temp->right;
        delete temp;
      }
      else if (temp->right == NULL) {
        *ptr = temp->left;
        delete temp;
      }
      else {
        // find the right-most left node--stuntman
        Node ** stuntman_ptr = &temp->left;
        while ((*stuntman_ptr)->right != NULL) {
          stuntman_ptr = &(*stuntman_ptr)->right;
        }
        // swap their keys and values
        Node * stuntman = *stuntman_ptr;
        std::swap<K>(temp->key, stuntman->key);
        std::swap<V>(temp->val, stuntman->val);
        // delete the stuntman
        *stuntman_ptr = (*stuntman_ptr)->left;
        delete stuntman;
      }
    }
  }
};
#endif
