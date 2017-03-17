#ifndef POSTFIX_EXPRESSION_VISITOR_H_
#define POSTFIX_EXPRESSION_VISITOR_H_

#include <vector>

#include "Visitor.h"
#include "Node.h"

namespace Regex {


class PostfixExpressionVisitor: public Visitor {
public:
    PostfixExpressionVisitor() = default;
    ~PostfixExpressionVisitor() = default;
    void visit(std::shared_ptr<ElementNode> node) override;
    void visit(std::shared_ptr<OrNode> node) override;
    void visit(std::shared_ptr<CombineNode> node) override;
    void visit(std::shared_ptr<ClosureNode> node) override;
    void visit(std::shared_ptr<FunctionNode> node) override;
    void visit(std::shared_ptr<LeftBracket> node) override;
    void visit(std::shared_ptr<RightBracket> node) override;

    std::vector<std::shared_ptr<Node>>& getPostExpr();
private:
    std::vector<std::shared_ptr<Node>> elementStack;
    std::vector<std::shared_ptr<Node>> operatorStack;
};


} // namespace Regex

#endif // POSTFIX_EXPRESSION_VISITOR_H_