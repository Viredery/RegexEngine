#ifndef POSTFIX_EXPRESSION_VISITOR_H_
#define POSTFIX_EXPRESSION_VISITOR_H_

#include <vector>
#include "Visitor.hpp"
#include "Node.hpp"

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

    std::vector<std::shared_ptr<Node>> getPostExpr();
private:
    std::vector<std::shared_ptr<Node>> elementStack;
    std::vector<std::shared_ptr<Node>> operatorStack;
};

void PostfixExpressionVisitor::visit(std::shared_ptr<ElementNode> node) {
    elementStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<OrNode> node) {
	if (operatorStack.empty()) {
		operatorStack.push_back(node);
		return;
	}
    auto top = operatorStack.back();

    while (!operatorStack.empty() && typeid(*top) != typeid(LeftBracket)) {
        elementStack.push_back(top);
        operatorStack.pop_back();
        if (!operatorStack.empty())
            top = operatorStack.back();
    }
    operatorStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<CombineNode> node) {
    if (operatorStack.empty()) {
        operatorStack.push_back(node);
        return;
    }
    auto top = operatorStack.back();
    while (!operatorStack.empty() && typeid(*top) != typeid(LeftBracket) && typeid(*top) != typeid(OrNode)) {
        elementStack.push_back(top);
        operatorStack.pop_back();
        if (!operatorStack.empty())
            top = operatorStack.back();
    }
    operatorStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<ClosureNode> node) {
    elementStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<FunctionNode> node) {
    throw -1;
}

void PostfixExpressionVisitor::visit(std::shared_ptr<LeftBracket> node) {
    operatorStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<RightBracket> node) {
    auto top = operatorStack.back();
    while (typeid(*top) != typeid(LeftBracket)) {
        elementStack.push_back(top);
        operatorStack.pop_back();
        top = operatorStack.back();
    }
    operatorStack.pop_back();
}

std::vector<std::shared_ptr<Node>> PostfixExpressionVisitor::getPostExpr() {
    while (!operatorStack.empty()) {
        auto top = operatorStack.back();
        elementStack.push_back(top);
        operatorStack.pop_back();
    }
    return elementStack;
}
#endif