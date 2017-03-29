//  branch_node.h
//  Created by viredery on 17/03/29

#ifndef BRANCH_NODE_H_
#define BRANCH_NODE_H_

#include "original_node.h"

namespace regex {

class BranchNode : public Node {
 public:
  BranchNode() = default;
  virtual ~BranchNode() = default;

  virtual void Accept(VisitorInterface* visitor) = 0;
  virtual int GetPri() const = 0;

 private:
  virtual std::string ConvertString() const = 0;
};

} // namespace regex

#endif // BRANCH_NODE_H_