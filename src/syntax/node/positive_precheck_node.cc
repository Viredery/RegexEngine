//  positive_precheck_node.cc
//  Created by viredery on 17/03/29

#include "positive_precheck_node.h"

namespace regex {

void PositivePrecheckNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

std::string PositivePrecheckNode::ConvertString() const {
  return "PositivePrecheckNode";
}

} // namespace regex