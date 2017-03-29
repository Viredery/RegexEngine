//  left_bracket_node.h
//  Created by viredery on 17/03/29

#ifndef LEFT_BRACKET_NODE_H_
#define LEFT_BRACKET_NODE_H_

#include "original_node.h"

namespace regex {

class LeftBracketNode : public Node {
 public:
  LeftBracketNode() = default;
  virtual ~LeftBracketNode() = default;

  virtual void Accept(VisitorInterface* visitor) = 0;
  int GetPri() const override;

 private:
  virtual std::string ConvertString() const = 0;
};

} // namespace regex

#endif // LEFT_BRACKET_NODE_H_