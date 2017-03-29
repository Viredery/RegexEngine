//  right_bracket_node.h
//  Created by viredery on 17/03/29

#ifndef RIGHT_RACKET_NODE_H_
#define RIGHT_RACKET_NODE_H_

#include "original_node.h"

namespace regex {

class RightBracketNode : public Node {
 public:
  RightBracketNode() = default;
  ~RightBracketNode() override {}

  void Accept(VisitorInterface* visitor) override;
  int GetPri() const override;

 private:
  std::string ConvertString() const override;
};

} // namespace regex

#endif // RIGHT_RACKET_NODE_H_