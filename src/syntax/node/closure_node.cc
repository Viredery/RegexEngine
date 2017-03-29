//  closure_node.cc
//  Created by viredery on 17/03/29

#include "closure_node.h"

namespace regex {

ClosureNode::ClosureNode(int min_repetition, int max_repetition, bool greedy)
    : min_repetition_(min_repetition),
      max_repetition_(max_repetition),
      greedy_(greedy) {}

void ClosureNode::Accept(VisitorInterface* visitor) {
  visitor->Visit(this);
}

int ClosureNode::GetPri() const {
	return kTwo;
}

int ClosureNode::min_repetition() const {
  return min_repetition_;
}

int ClosureNode::max_repetition() const {
  return max_repetition_;
}

bool ClosureNode::greedy() const {
  return greedy_;
}

std::string ClosureNode::ConvertString() const {
  return std::string("ClosureNode(") + std::to_string(min_repetition_) + "," +
         std::to_string(max_repetition_) + "," + (greedy_ ? "G" : "N") + ")";
}

} // namespace regex