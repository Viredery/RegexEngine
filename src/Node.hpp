#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>
#include <memory>
#include <bitset>
#include "Visitor.hpp"

class Node {
public:
	Node() = default;
	virtual ~Node() = default;
    inline void setChildNode(std::shared_ptr<Node> leftNode, std::shared_ptr<Node> rightNode) {
    	left = leftNode;
    	right = rightNode;
    }
    inline std::shared_ptr<Node> getLeft() {
        return left;
    }
    inline std::shared_ptr<Node> getRight() {
        return right;
    }
    virtual void accept(Visitor* visitor) = 0;
    virtual std::string toString() = 0;
private:
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
};

class LeafNode: public Node {
public:
    LeafNode() = default;
    virtual void accept(Visitor* visitor) = 0;
    virtual std::string toString() = 0;
};

class BranchNode: public Node {
public:
    BranchNode() = default;
    virtual void accept(Visitor* visitor) = 0;
    virtual std::string toString() = 0;
};

class ElementNode: public LeafNode, public std::enable_shared_from_this<ElementNode> {
public:
	ElementNode() = default;
    void accept(Visitor* visitor) override {
        visitor->visit(shared_from_this());
    }
    std::string toString() override {
        return "ElementNode";
    }
    // Decorator/Wrapper Pattern
    void setElement(char character) {
        elementSet.flip(static_cast<std::size_t>(character));
    }
    void inverse() {
        elementSet.flip();
    }
    std::string getElementString() {
        return elementSet.to_string<char>();
    }
	std::bitset<128> elementSet;
};


class OrNode: public BranchNode, public std::enable_shared_from_this<OrNode> {
public:
    OrNode() = default;
    void accept(Visitor* visitor) override {
        visitor->visit(shared_from_this());
    }
    std::string toString() override {
        return "OrNode";
    }
};

class CombineNode: public BranchNode, public std::enable_shared_from_this<CombineNode> {
public:
	CombineNode() = default;
    void accept(Visitor* visitor) override {
        visitor->visit(shared_from_this());
    }
    std::string toString() override {
        return "CombineNode";
    }
};

// Only greedy matches currently.
class ClosureNode: public BranchNode, public std::enable_shared_from_this<ClosureNode> {
public:
	ClosureNode(int minRep, int maxRep):
        minRepetition(minRep), maxRepetition(maxRep) {}
    void accept(Visitor* visitor) override {
        visitor->visit(shared_from_this());
    }
    std::string toString() override {
        std::string res("");
        res = res + "ClosureNode: " + std::to_string(minRepetition) + " " + std::to_string(maxRepetition);
        return res;
    }

    int getMinRepetition() const {
        return minRepetition;
    }
    int getMaxRepetition() const {
        return maxRepetition;
    }
    int minRepetition;
    int maxRepetition;
};

// We will handle this node later.
class FunctionNode: public BranchNode, public std::enable_shared_from_this<FunctionNode> {
public:
    FunctionNode() = default;
    void accept(Visitor* visitor) override {
        visitor->visit(shared_from_this());
    }
    std::string toString() override {
        return "FunctionNode";
    }
};

class LeftBracket: public Node, public std::enable_shared_from_this<LeftBracket> {
public:
    LeftBracket() = default;
    void accept(Visitor* visitor) override {
        visitor->visit(shared_from_this());
    }
    std::string toString() override {
        return "LeftBracket";
    }
};

class RightBracket: public Node, public std::enable_shared_from_this<RightBracket> {
public:
    RightBracket() = default;
    void accept(Visitor* visitor) override {
        visitor->visit(shared_from_this());
    }
    std::string toString() override {
        return "RightBracket";
    }
};

#endif // NODE_H_