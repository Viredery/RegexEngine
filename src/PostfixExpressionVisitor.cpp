#include "PostfixExpressionVisitor.h"

namespace Regex {


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

std::vector<std::shared_ptr<Node>>& PostfixExpressionVisitor::getPostExpr() {
    while (!operatorStack.empty()) {
        auto top = operatorStack.back();
        elementStack.push_back(top);
        operatorStack.pop_back();
    }
    return elementStack;
}


} // namespace Regex