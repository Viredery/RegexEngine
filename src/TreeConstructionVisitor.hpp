#ifndef TREE_CONSTRUCTION_VISITOR_H_
#define TREE_CONSTRUCTION_VISITOR_H_


#include <stack>
#include "Visitor.hpp"
#include "Node.hpp"

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

#endif