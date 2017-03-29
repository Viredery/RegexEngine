//  closure_node.h
//  Created by viredery on 17/03/29

#ifndef CLOSURE_NODE_H_
#define CLOSURE_NODE_H_

#include "branch_node.h"

namespace regex {

class ClosureNode : public BranchNode {
 public:
  ClosureNode(int min_repetition, int max_repetition, bool greedy);
  ~ClosureNode() override {}

  void Accept(VisitorInterface* visitor) override;
  int GetPri() const override;

  int min_repetition() const;
  int max_repetition() const;
  bool greedy() const;

 private:
  std::string ConvertString() const override;

  int min_repetition_;
  int max_repetition_;
  bool greedy_;
};

} // namespace regex

#endif // CLOSURE_NODE_H_