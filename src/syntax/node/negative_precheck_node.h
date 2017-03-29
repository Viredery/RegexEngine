//  negative_precheck_node.h
//  Created by viredery on 17/03/29

#ifndef NEGATIVE_PRECHECK_NODE_H_
#define NEGATIVE_PRECHECK_NODE_H_

#include "left_bracket_node.h"

namespace regex {

class NegativePrecheckNode : public LeftBracketNode {
 public:
  NegativePrecheckNode() = default;
  ~NegativePrecheckNode() override {}

  void Accept(VisitorInterface* visitor) override;

 private:
  std::string ConvertString() const override;
};

} // namespace regex

#endif // NEGATIVE_PRECHECK_NODE_H_