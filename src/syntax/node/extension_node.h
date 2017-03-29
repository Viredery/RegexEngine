//  extension_node.h
//  Created by viredery on 17/03/29

#ifndef EXTENSION_NODE_H_
#define EXTENSION_NODE_H_

#include "left_bracket_node.h"

namespace regex {

class ExtensionNode : public LeftBracketNode {
 public:
  ExtensionNode() = default;
  ~ExtensionNode() {}

  void Accept(VisitorInterface* visitor) override;

 private:
  std::string ConvertString() const override;
};

} // namespace regex

#endif // EXTENSION_NODE_H_