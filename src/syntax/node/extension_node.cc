//  extension_node.cc
//  Created by viredery on 17/03/29

#include "extension_node.h"

namespace regex {

void ExtensionNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

std::string ExtensionNode::ConvertString() const {
  return "ExtensionNode";
}

} // namespace regex