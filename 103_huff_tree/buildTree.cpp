#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t p_queue;
  for (unsigned i = 0; i < 257; ++i) {
    if (counts[i] != 0) {
      p_queue.push(new Node(i, counts[i]));
    }
  }
  while (p_queue.size() > 1) {
    Node * le = p_queue.top();
    p_queue.pop();
    Node * ri = p_queue.top();
    p_queue.pop();
    Node * temp_root = new Node(le, ri);
    p_queue.push(temp_root);
  }
  Node * root = p_queue.top();
  p_queue.pop();
  return root;
}
