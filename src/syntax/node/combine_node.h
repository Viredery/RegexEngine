//  combine_node.h
//  Created by viredery on 17/03/29

#ifndef COMBINE_NODE_H_
#define COMBINE_NODE_H_

#include "branch_node.h"

namespace regex {

class CombineNode : public BranchNode {
 public:
  CombineNode() = default;
  ~CombineNode() override {}

  void Accept(VisitorInterface* visitor) override;
  int GetPri() const override;

 private:
  std::string ConvertString() const override;
};

} // namespace regex

#endif // COMBINE_NODE_H_