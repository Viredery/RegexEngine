//  left_bracket_node.cc
//  Created by viredery on 17/03/29

#include "left_bracket_node.h"

namespace regex {

int LeftBracketNode::GetPri() const {
  return kOne;
}

} // namespace regex