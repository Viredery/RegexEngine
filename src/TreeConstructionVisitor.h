#ifndef TREE_CONSTRUCTION_VISITOR_H_
#define TREE_CONSTRUCTION_VISITOR_H_

#include <stack>

#include "Visitor.h"
#include "Node.h"

namespace Regex {


class TreeConstructionVisitor: public Visitor {
public:
    TreeConstructionVisitor() = default;
    ~TreeConstructionVisitor() = default;
    void visit(std::shared_ptr<ElementNode> node) override;
    void visit(std::shared_ptr<OrNode> node) override;
    void visit(std::shared_ptr<CombineNode> node) override;
    void visit(std::shared_ptr<ClosureNode> node) override;
    void visit(std::shared_ptr<FunctionNode> node) override;
    void visit(std::shared_ptr<LeftBracket> node) override;
    void visit(std::shared_ptr<RightBracket> node) override;

    std::shared_ptr<Node> getTree();
private:
    std::stack<std::shared_ptr<Node>> elementStack;
    std::shared_ptr<Node> root = nullptr;

    void constructTwoChildTree(std::shared_ptr<Node> node);
    void constructLeftChildTree(std::shared_ptr<Node> node);
};


} // namespace Regex

#endif // TREE_CONSTRUCTION_VISITOR_H_