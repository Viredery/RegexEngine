//  original_node.cc
//  Created by viredery on 17/03/28

#include "original_node.h"

namespace regex {

void Node::set_left_ptr(Node* left_ptr) {
  left_ptr_ = left_ptr;
}

void Node::set_right_ptr(Node* right_ptr) {
  right_ptr_ = right_ptr;
}

Node* Node::left_ptr() const {
  return left_ptr_;
}

Node* Node::right_ptr() const {
  return right_ptr_;
}

std::ostream &operator<<(std::ostream& os, const Node* node) {
  os << node->ConvertString();
  return os;
}

} // namespace regex