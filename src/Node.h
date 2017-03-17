#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <memory>
#include <bitset>

#include "Visitor.h"

namespace Regex {


class Node {
public:
	Node() = default;
	virtual ~Node() = default;
    inline void setChildNode(std::shared_ptr<Node> leftNode, std::shared_ptr<Node> rightNode);
    inline std::shared_ptr<Node> getLeft();
    inline std::shared_ptr<Node> getRight();
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
    void accept(Visitor* visitor) override;
    std::string toString() override;
    inline void setElement(char character);
    inline void inverse();
    inline std::string getElementString();
	std::bitset<128> elementSet;
};

class OrNode: public BranchNode, public std::enable_shared_from_this<OrNode> {
public:
    OrNode() = default;
    void accept(Visitor* visitor) override;
    std::string toString() override;
};

class CombineNode: public BranchNode, public std::enable_shared_from_this<CombineNode> {
public:
	CombineNode() = default;
    void accept(Visitor* visitor) override;
    std::string toString() override;
};

class ClosureNode: public BranchNode, public std::enable_shared_from_this<ClosureNode> {
public:
	ClosureNode(int minRep, int maxRep);
    void accept(Visitor* visitor) override;
    std::string toString() override;

    inline int getMinRepetition() const;
    inline int getMaxRepetition() const;
    int minRepetition;
    int maxRepetition;
};

class FunctionNode: public BranchNode, public std::enable_shared_from_this<FunctionNode> {
public:
    FunctionNode() = default;
    void accept(Visitor* visitor) override;
    std::string toString() override;
};

class LeftBracket: public Node, public std::enable_shared_from_this<LeftBracket> {
public:
    LeftBracket() = default;
    void accept(Visitor* visitor) override;
    std::string toString() override;
};

class RightBracket: public Node, public std::enable_shared_from_this<RightBracket> {
public:
    RightBracket() = default;
    void accept(Visitor* visitor) override;
    std::string toString() override;
};


} // namespace Regex

#endif // NODE_H_