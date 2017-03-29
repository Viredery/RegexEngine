//  combine_node.cc
//  Created by viredery on 17/03/29

#include "combine_node.h"

namespace regex {

void CombineNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this); 
}

int CombineNode::GetPri() const {
	return kThree;
}

std::string CombineNode::ConvertString() const {
  return "CombineNode";
}

} // namespace regex