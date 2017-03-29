//  element_node.h
//  Created by viredery on 17/03/28

#ifndef ELEMENT_NODE_H_
#define ELEMENT_NODE_H_

#include <array>

#include "original_node.h"

namespace regex {

class ElementNode : public Node {
 public:
  enum { kArraySize = 128 };

  ElementNode(bool antonymy);
  ~ElementNode() override {}

  void Accept(VisitorInterface* visitor) override;
  int GetPri() const override;
  void AddElement(char character);
  void AddElement(int pos);
  void HandleEscapeCharacter(char escapeCharacter);

  std::array<bool, kArraySize>& element_arr();

 private:
  std::string ConvertString() const override;

  std::array<bool, kArraySize> element_arr_;
  bool antonymy_;
};

} //namespace regex

#endif // ELEMENT_NODE_H_