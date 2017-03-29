//  positive_precheck_node.h
//  Created by viredery on 17/03/29

#ifndef POSTIVE_PRECHECK_NODE_H_
#define POSTIVE_PRECHECK_NODE_H_

#include "left_bracket_node.h"

namespace regex {

class PositivePrecheckNode : public LeftBracketNode {
 public:
  PositivePrecheckNode() = default;
  ~PositivePrecheckNode() override {}

  void Accept(VisitorInterface* visitor) override;

 private:
  std::string ConvertString() const override;
};

} // namespace regex

#endif // POSTIVE_PRECHECK_NODE_H_