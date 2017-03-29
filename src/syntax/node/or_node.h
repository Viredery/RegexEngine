//  or_node.h
//  Created by viredery on 17/03/29

#ifndef OR_NODE_H_
#define OR_NODE_H_

#include "branch_node.h"

namespace regex {

class OrNode : public BranchNode {
 public:
  OrNode() = default;
  ~OrNode() override {}

  void Accept(VisitorInterface* visitor) override;
  int GetPri() const override;

 private:
  std::string ConvertString() const override;
};

} // namespace regex

#endif // OR_NODE_H_