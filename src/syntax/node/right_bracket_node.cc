//  right_bracket_node.cc
//  Created by viredery on 17/03/29

#include "right_bracket_node.h"

namespace regex {

void RightBracketNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

int RightBracketNode::GetPri() const {
  return kOne;
}

std::string RightBracketNode::ConvertString() const {
  return "RightBracketNode";
}

} // namespace regex