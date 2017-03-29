//  or_node.cc
//  Created by viredery on 17/03/29

#include "or_node.h"

namespace regex {

void OrNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

int OrNode::GetPri() const {
  return kFour;
}

std::string OrNode::ConvertString() const {
  return "OrNode";
}

} // namespace regex