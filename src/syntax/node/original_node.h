//  original_node.h
//  Created by viredery on 17/03/28

#ifndef ORIGINAL_NODE_H_
#define ORIGINAL_NODE_H_

#include <iostream>
#include <string>

#include "../../visitor/visitor_interface.h"

namespace regex {

class Node {
 public:
  Node() = default;
  virtual ~Node() = default;

  virtual void Accept(VisitorInterface* visitor) = 0;
  virtual int GetPri() const = 0;

  void set_left_ptr(Node* left_ptr);
  void set_right_ptr(Node* right_ptr);
  Node* left_ptr() const;
  Node* right_ptr() const;

  friend std::ostream& operator<<(std::ostream& os, const Node* node);

 protected:
  enum {
    kHigh = 0, kOne = 1, kTwo = 2,
    kThree = 3, kFour = 4, kLow = 5
  };
  
  Node* left_ptr_ = nullptr;
  Node* right_ptr_ = nullptr;

 private:
  virtual std::string ConvertString() const = 0;
};

} // namespace regex

#endif // ORIGINAL_NODE_H_