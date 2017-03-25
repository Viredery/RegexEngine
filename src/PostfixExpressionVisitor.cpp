#include "PostfixExpressionVisitor.h"

#include <exception>

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
    while (!operatorStack.empty() && nullptr == dynamic_cast<LeftBracket*>(top.get())) {
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
    while (!operatorStack.empty() && nullptr == dynamic_cast<LeftBracket*>(top.get()) && typeid(*top) != typeid(OrNode)) {
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

void PostfixExpressionVisitor::visit(std::shared_ptr<LeftBracket> node) {
    throw std::invalid_argument("ERROR TYPE");;
}

void PostfixExpressionVisitor::visit(std::shared_ptr<CaptureNode> node) {
    operatorStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<ExtensionNode> node) {
    operatorStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<PositivePrecheckNode> node) {
    operatorStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<NegativePrecheckNode> node) {
    operatorStack.push_back(node);
}

void PostfixExpressionVisitor::visit(std::shared_ptr<RightBracket> node) {
    auto top = operatorStack.back();
    while (nullptr == dynamic_cast<LeftBracket*>(top.get())) {
        elementStack.push_back(top);
        operatorStack.pop_back();
        top = operatorStack.back();
    }
    if (typeid(*top) != typeid(ExtensionNode))
        elementStack.push_back(top);
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