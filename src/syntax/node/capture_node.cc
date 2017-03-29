//  capture_node.cc
//  Created by viredery on 17/03/29

#include "capture_node.h"

namespace regex {

void CaptureNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

std::string CaptureNode::ConvertString() const {
  return "CaptureNode";
}

} // namespace regex