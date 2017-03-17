#include "TreeConstructionVisitor.h"

namespace Regex {


std::shared_ptr<Node> TreeConstructionVisitor::getTree() {
    while (!elementStack.empty())
    	elementStack.pop();
    return root;
}

void TreeConstructionVisitor::visit(std::shared_ptr<ElementNode> node) {
    elementStack.push(node);
    root = node;
}

void TreeConstructionVisitor::visit(std::shared_ptr<OrNode> node) {
    constructTwoChildTree(node);
}

void TreeConstructionVisitor::visit(std::shared_ptr<CombineNode> node) {
    constructTwoChildTree(node);
}

void TreeConstructionVisitor::visit(std::shared_ptr<ClosureNode> node) {
    constructLeftChildTree(node);
}

void TreeConstructionVisitor::visit(std::shared_ptr<FunctionNode> node) {
    throw -1;
}

void TreeConstructionVisitor::visit(std::shared_ptr<LeftBracket> node) {
    throw -1;
}

void TreeConstructionVisitor::visit(std::shared_ptr<RightBracket> node) {
    throw -1;
}

void TreeConstructionVisitor::constructTwoChildTree(std::shared_ptr<Node> node) {
	auto right = elementStack.top();
	elementStack.pop();
	auto left = elementStack.top();
	elementStack.pop();
	node->setChildNode(left, right);
	elementStack.push(node);
	root = node;
}

void TreeConstructionVisitor::constructLeftChildTree(std::shared_ptr<Node> node) {
	auto left = elementStack.top();
	elementStack.pop();
	node->setChildNode(left, nullptr);
	elementStack.push(node);
	root = node;
}


} // namespace Regex