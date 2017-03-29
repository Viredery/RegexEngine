//  capture_node.h
//  Created by viredery on 17/03/29

#ifndef CAPTURE_NODE_H_
#define CAPTURE_NODE_H_

#include "left_bracket_node.h"

namespace regex {

class CaptureNode : public LeftBracketNode {
 public:
  CaptureNode() = default;
  ~CaptureNode() override {}

  void Accept(VisitorInterface* visitor) override;

 private:
  std::string ConvertString() const override;
};

} // namespace regex

#endif // CAPTURE_NODE_H_