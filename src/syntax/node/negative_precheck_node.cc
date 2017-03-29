//  negative_precheck_node.cc
//  Created by viredery on 17/03/29

#include "negative_precheck_node.h"

namespace regex {

void NegativePrecheckNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

std::string NegativePrecheckNode::ConvertString() const {
  return "NegativePrecheckNode";
}

} // namespace regex