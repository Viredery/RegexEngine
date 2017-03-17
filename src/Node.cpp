#include "Node.h"

#include "SyntacticTree.h"
#include "StateEdgePool.h"

namespace Regex {


void Node::setChildNode(std::shared_ptr<Node> leftNode, std::shared_ptr<Node> rightNode) {
	left = leftNode;
	right = rightNode;
}

std::shared_ptr<Node> Node::getLeft() {
    return left;
}

std::shared_ptr<Node> Node::getRight() {
    return right;
}

void ElementNode::accept(Visitor* visitor) override {
    visitor->visit(shared_from_this());
}

std::string ElementNode::toString() override {
    return "ElementNode";
}

void ElementNode::setElement(char character) {
    elementSet.flip(static_cast<std::size_t>(character));
}

void ElementNode::inverse() {
    elementSet.flip();
}

std::string ElementNode::getElementString() {
    return elementSet.to_string<char>();
}

void OrNode::accept(Visitor* visitor) override {
    visitor->visit(shared_from_this());
}

std::string OrNode::toString() override {
    return "OrNode";
}

void CombineNode::accept(Visitor* visitor) override {
    visitor->visit(shared_from_this()); 
}

std::string CombineNode::toString() override {
    return "CombineNode";
}

ClosureNode::ClosureNode(int minRep, int maxRep):
        minRepetition(minRep), maxRepetition(maxRep) {}

void ClosureNode::accept(Visitor* visitor) override {
    visitor->visit(shared_from_this());
}

std::string ClosureNode::toString() override {
    std::string res("");
    res = res + "ClosureNode: " + std::to_string(minRepetition) + " " + std::to_string(maxRepetition);
    return res;
}

int ClosureNode::getMinRepetition() const {
    return minRepetition;
}

int ClosureNode::getMaxRepetition() const {
    return maxRepetition;
}

void FunctionNode::accept(Visitor* visitor) override {
    visitor->visit(shared_from_this());
}

std::string FunctionNode::toString() override {
    return "FunctionNode";
}

void LeftBracket::accept(Visitor* visitor) override {
    visitor->visit(shared_from_this());
}

std::string LeftBracket::toString() override {
    return "LeftBracket";
}

void RightBracket::accept(Visitor* visitor) override {
    visitor->visit(shared_from_this());
}

std::string RightBracket::toString() override {
    return "RightBracket";
}


} // namespace Regex